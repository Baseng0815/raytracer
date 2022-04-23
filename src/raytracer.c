#include "raytracer.h"

#include "ray.h"
#include "image.h"
#include "geometry.h"
#include "color.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

static void solve_rendering_equation(struct spectrum*,
                                     const struct ray*,
                                     const struct scene*);

void raytracer_build_tables(void)
{
        color_build_tables();
}

void raytracer_render(const struct scene *scene, int iw, int ih)
{
        /* image pixel width and height in world coordinates */
        double pw  = scene->sw / (double)iw;
        double ph = scene->sh / (double)ih;

        struct image_pixel *pix = malloc(sizeof(struct image_pixel) * iw * ih);
        memset(pix, 0, sizeof(struct image_pixel) * iw * ih);

        struct fvec3 light_dir = {
                .x = -1.0,
                .y = -1.0,
                .z = -1.0
        };

        fvec3_normalize(&light_dir, &light_dir);

        for (int y = 0; y < ih; y++) {
                for (int x = 0; x < iw; x++) {
                        /* generate initial ray through pixel center */
                        double wx = ((x - iw / 2.0) + 0.5) * pw;
                        double wy = ((y - ih / 2.0) + 0.5) * ph;

                        struct ray ray;
                        ray.direction.x = wx;
                        ray.direction.y = wy;
                        ray.direction.z = 1.0;
                        fvec3_normalize(&ray.direction, &ray.direction);

                        ray.origin.x = 0.0;
                        ray.origin.y = 0.0;
                        ray.origin.z = 0.0;

                        struct spectrum ray_color;
                        solve_rendering_equation(&ray_color, &ray, scene);
                        struct fvec3 rgb;
                        spectrum_to_xyz(&rgb, &ray_color);
                        xyz_to_rgb(&rgb, &rgb);
                        pix[y * iw + x].r = rgb.x * 255;
                        pix[y * iw + x].g = rgb.y * 255;
                        pix[y * iw + x].b = rgb.z * 255;
                }
        }

        image_save("image.bmp", pix, iw, ih, BMP);

        free(pix);
}

static void solve_rendering_equation(struct spectrum *ray_color,
                                     const struct ray *ray,
                                     const struct scene *scene)
{
        double closest_distance = DBL_MAX;
        struct intersect closest_intersect;
        const struct sphere *closest_sphere = NULL;

        // find closest intersection point
        for (size_t spherei = 0; spherei < scene->sphere_count; spherei++) {
                struct intersect intersect;
                const struct sphere *s = &scene->spheres[spherei];
                if (ray_intersect_with_sphere(&intersect, ray, s)) {
                        struct fvec3 d;
                        fvec3_sub(&d, &intersect.point, &ray->origin);
                        double dl = fvec3_len_squared(&d);
                        if (dl < closest_distance) {
                                closest_distance = dl;
                                closest_intersect = intersect;
                                closest_sphere = s;
                        }
                }
        }

        if (!closest_sphere) {
                // no intersection detected - color with background
                *ray_color = *scene->background;
                return;
        }

        // color from illumination sources
        struct ray light_ray;
        fvec3_mult(&light_ray.origin, &closest_intersect.normal, 0.0001);
        fvec3_add(&light_ray.origin, &light_ray.origin,
                  &closest_intersect.point);

        // diffuse reflection
        struct spectrum idr = { .values = { 0.0 } };
        for (size_t lighti = 0; lighti < scene->light_count; lighti++) {
                const struct light *light = &scene->lights[lighti];
                fvec3_sub(&light_ray.direction, &light->position,
                          &light_ray.origin);
                double len_squared = fvec3_len_squared(&light_ray.direction);
                fvec3_normalize(&light_ray.direction, &light_ray.direction);

                bool is_visible = true;
                for (size_t spherei = 0;
                     spherei < scene->sphere_count;
                     spherei++) {
                        struct intersect intersect;
                        const struct sphere *sphere = &scene->spheres[spherei];
                        if (ray_intersect_with_sphere(&intersect, &light_ray,
                                                      sphere)) {
                                if (intersect.distance * intersect.distance < len_squared) {
                                        is_visible = false;
                                        break;
                                }
                        }
                }

                if (is_visible) {
                        double factor = fmax(fvec3_dot(&closest_intersect.normal,
                                                       &light_ray.direction), 0.0);
                        struct spectrum color;
                        spectrum_multiply(&color, light->spectrum,
                                          closest_sphere->material->fdr);
                        spectrum_fmultiply(&color, &color, factor);
                        spectrum_add(&idr, &idr, &color);
                }
        }

        *ray_color = idr;
}
