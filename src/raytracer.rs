use crate::{vec::Vec3, ray::Ray, scene::Scene};

pub struct Raytracer {
    background: Vec3,
    depth_max: u32
}

impl Raytracer {
    pub fn new(background: Vec3, depth_max: u32) -> Raytracer {
        Raytracer {
            background,
            depth_max
        }
    }

    pub fn background_color(&self, ray: &Ray) -> Vec3 {
        let a = 0.5 * (ray.direction.1 + 1.0);
        Vec3::UNIT * (1.0 - a) + self.background * a
    }

    pub fn ray_color(&self, ray: &Ray, scene: &Scene) -> Vec3 {
        self.ray_color_depth(ray, scene, 0)
    }

    fn ray_color_depth(&self, ray: &Ray, scene: &Scene, depth_cur: u32) -> Vec3 {
        if depth_cur >= self.depth_max {
            return Vec3::ZERO;
        }

        let hit = scene.cast_ray(&ray, 0.001, f64::MAX);

        match hit {
            Some(intersect) => {
                let new_dir = (intersect.normal + Vec3::random_on_unit_sphere()).normalized();
                let new_ray = Ray {
                    origin: intersect.point,
                    direction: new_dir
                };

                self.ray_color_depth(&new_ray, scene, depth_cur + 1) * 0.5
            }

            None => self.background_color(&ray)
        }
    }
}
