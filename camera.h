#pragma once

#include "misc_constants.h"

class camera {
    public:
        camera () {
            const double aspect_ratio = 16.0 / 9.0;
            const double viewport_height = 2.0;
            const double viewport_width = aspect_ratio * viewport_height;
            const double focal_length = 1.0;
            
            origin = vec3(0, 0, 0);
            horizontal = vec3(viewport_width, 0.0, 0.0);
            vertical = vec3(0.0, viewport_height, 0.0);
            lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
        }

        ray get_ray(double u, double v) const{
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }
    
    private:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};