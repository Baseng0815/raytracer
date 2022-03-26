#include "raytracer.h"

#include "ray.h"
#include "image.h"
#include "geometry.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void raytracer_render(const struct scene *scene, int iw, int ih, int sw, int sh)
{
        /* image pixel width and height in world coordinates */
        double pw  = sw / (double)iw;
        double ph = sh / (double)ih;

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
                        /* generate ray through pixel center */
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

                        /* find intersection */
                        for (size_t i = 0; i < scene->sphere_count; i++) {
                                struct intersect intersect;
                                const struct sphere *s = &scene->spheres[i];
                                if (ray_intersect_with_sphere(&intersect, &ray, s)) {
                                        double a = fvec3_dot(&light_dir, &intersect.normal);
                                        pix[y * iw + x].r = fmax(255.0 * a, 0.0);
                                } else {
                                        pix[y * iw + x].r = 0;
                                }
                        }
                }
        }

        image_save("image.bmp", pix, iw, ih, BMP);

        free(pix);
}
