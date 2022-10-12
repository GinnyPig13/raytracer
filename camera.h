#pragma once

#include "misc_constants.h"

class camera 
{
    public:
        camera (vec3 look_from, vec3 look_at, vec3 view_up, double vertical_field_of_view, double aspect_ratio) 
        {
            double theta = degrees_to_radians(vertical_field_of_view);
            double h = tan(theta / 2);
            double viewport_height = 2.0 * h;
            double viewport_width = aspect_ratio * viewport_height;

            vec3 camera_z = unit_vector(look_from - look_at);
            vec3 camera_x = unit_vector(cross(view_up, camera_z));
            vec3 camera_y = cross(camera_z, camera_x);

            origin = look_from;
            horizontal = viewport_width * camera_x;
            vertical = viewport_height * camera_y;
            lower_left_corner = origin - horizontal/2 - vertical/2 - camera_z;
        }

        ray get_ray(double u, double v) const
        {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }
    
    private:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};