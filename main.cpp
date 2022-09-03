#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

//Determines if ray intersects sphere through positive discriminant
bool hit_sphere(const vec3& center, double radius, const ray& r) {
    vec3 rayOrigin_sphereCenter = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(rayOrigin_sphereCenter, r.direction());
    double c = dot(rayOrigin_sphereCenter, rayOrigin_sphereCenter) - radius*radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

vec3 ray_color(const ray &r) {
    if (hit_sphere(vec3(0,0,-1),0.5, r))
    {
        return vec3(0,0,1);
    }
    
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(){
    // Image

    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    vec3 origin = vec3(0, 0, 0);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    
    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            vec3 pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
