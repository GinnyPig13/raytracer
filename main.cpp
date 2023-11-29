#include <iostream>

#include "misc_constants.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "materials_bucket/material.h"
#include "materials_bucket/lambertian.h"
#include "materials_bucket/metal.h"
#include "materials_bucket/dielectric.h"

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
        ray scattered;
        vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color_of_ray(scattered, world, depth-1);
        }
        return vec3(0, 0, 0);
        
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

    //Ground material
    auto material_ground = std::make_shared<lambertian>(vec3(0.08, 0.33, 0.08));
    world.add(std::make_shared<sphere>(vec3(0.0, -1000.0, -1.0), 1000.0, material_ground));

    //Object material
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double choose_material = random_double();
            vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - vec3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<material> sphere_material;

                if (choose_material < 0.8)
                {
                    //diffuse
                    vec3 albedo = vec3::random() * vec3::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    vec3 center2 = center + vec3(0, random_double(0, 0.5), 0);
                    world.add(std::make_shared<sphere>(center, center2, 0.2, sphere_material));
                }

                else if (choose_material < 0.95)
                {
                    //metal
                    vec3 albedo = vec3::random(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }

                else
                {
                    //glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }               
                
            }
            
        }
        
    }
    
    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(vec3(0.0, 1.0, 0.0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(vec3(0.0, 0.36, 0.72));
    world.add(std::make_shared<sphere>(vec3(-4.0, 1.0, 0.0), 1.0, material2));

    auto material3 = std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0); 
    world.add(std::make_shared<sphere>(vec3(4.0, 1.0, 0.0), 1.0, material3));

    //Camera parameters
    const vec3 look_from = vec3(13, 2, 3);
    const vec3 look_at = vec3(0, 0, 0);
    const vec3 view_up = vec3(0, 1, 0);
    const int field_of_view = 20;
    const double defocus_angle = 0.6;
    const double focus_distance = 10.0;

    camera cam(look_from, look_at, view_up, field_of_view, aspect_ratio, defocus_angle, focus_distance);

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
