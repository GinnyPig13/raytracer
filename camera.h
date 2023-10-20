#pragma once

#include "misc_constants.h"

class camera 
{
    public:
        camera (vec3 look_from, vec3 look_at, vec3 view_up, double vertical_field_of_view, double aspect_ratio, double defocus_angle, double focus_distance) 
        {
            //Determine viewport dimensions
            double theta = degrees_to_radians(vertical_field_of_view);
            double h = tan(theta / 2);
            double viewport_height = 2.0 * h * focus_distance;
            double viewport_width = aspect_ratio * viewport_height;

            //Calculate the unit basis vectors for the camera coordinate frame
            vec3 camera_z = unit_vector(look_from - look_at);
            vec3 camera_x = unit_vector(cross(view_up, camera_z));
            vec3 camera_y = cross(camera_z, camera_x);
            
            //Calculate the camera defocus disk
            double defocus_radius = focus_distance * tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_horizontal = camera_x * defocus_radius;
            defocus_disk_vertical = camera_y * defocus_radius; 
            m_defocus_angle = defocus_angle;         

            origin = look_from;
            
            //Calculate vectors across the horizontal and vertical viewport edges
            viewport_horizontal = viewport_width * camera_x;
            viewport_vertical = viewport_height * camera_y;
            lower_left_corner = origin - (focus_distance * camera_z) - viewport_horizontal/2 - viewport_vertical/2;


        }

        vec3 defocus_disk_sample() const 
        {
            vec3 p = random_point_in_unit_disk();
            return origin + (p[0] * defocus_disk_horizontal) + (p[1] * defocus_disk_vertical);
        }

        ray get_ray(double u, double v) const
        {
            vec3 defocus_ray_origin = (m_defocus_angle <= 0) ? origin : defocus_disk_sample();
            return ray(defocus_ray_origin, lower_left_corner + u*viewport_horizontal + v*viewport_vertical - defocus_ray_origin);
        }
    
    private:
        vec3 origin; //Camera center
        vec3 lower_left_corner;
        vec3 viewport_horizontal;
        vec3 viewport_vertical;
        vec3 defocus_disk_horizontal;
        vec3 defocus_disk_vertical;
        double m_defocus_angle;
};