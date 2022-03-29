#include "raytracer.h"

#include "ray.h"
#include "image.h"
#include "geometry.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

static void solve_rendering_equation(struct spectrum*,
                                     const struct ray*,
                                     const struct scene*);

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
                        pix[y * iw + x].r = spectrum_get_intensity(&ray_color, 700.0);
                        pix[y * iw + x].g = spectrum_get_intensity(&ray_color, 540.0);
                        pix[y * iw + x].b = spectrum_get_intensity(&ray_color, 460.0);
                }
        }

        image_save("image.bmp", pix, iw, ih, BMP);

        free(pix);
}

static void solve_rendering_equation(struct spectrum *ray_color,
                                     const struct ray *ray,
                                     const struct scene *scene)
{
        spectrum_set_intensity(ray_color, 700.0, 0.2);
        return;

        double closest_distance = DBL_MAX;
        struct intersect closest_intersect;
        const struct sphere *closest_sphere = NULL;

        // find closest intersection point
        for (size_t i = 0; i < scene->sphere_count; i++) {
                struct intersect intersect;
                const struct sphere *s = &scene->spheres[i];
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
                *ray_color = scene->background;
                return;
        }

        // shadow rays to light sources
        for (size_t i = 0; i < scene->light_count; i++) {
                struct ray ray;
                fvec3_mult(&ray.origin, &closest_intersect.normal, 0.0001);
                fvec3_add(&ray.origin, &ray.origin, &closest_intersect.point);
        }
}
