#include <iostream>

#include "misc_constants.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

//Determines the normal ray when hit with the raytrace and records the hit
vec3 color_of_ray(const ray& r, const hittable& world, int depth) 
{
    hit_record rec;
    
    //If we've exceeded the ray bounce limit, no more light is diffused
    if (depth <= 0)
    {
        return vec3(0, 0, 0);
    }

    if (world.hit(r, 0.001, infinity, rec)) 
    {
        //generating a random point in a unit sphere relative to the hit point
        vec3 diffuse_point = rec.point + rec.normal + random_unit_vector();
        //0.5 shifts the color darker for shadows
        //Simulates light bouncing randomly
        return 0.5 * color_of_ray(ray(rec.point, diffuse_point - rec.point), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main()
{
    //Image parameters
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    //World list and contents
    hittable_list world;
    world.add(std::make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(vec3(0, -100.5, -1), 100));
    
    //Camera parameters
    camera cam;

    // Render process
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            vec3 pixel_color(0, 0, 0);
            //Creates random rays equal to the samples per pixel number within each pixel
            for (int s = 0; s < samples_per_pixel; ++s) 
            {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += color_of_ray(r, world, max_depth);
            }
           //Averages the samples per pixel rays' results to a rasterized color for said pixel
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
