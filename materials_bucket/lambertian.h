#pragma once

#include "../hittable.h"
#include "material.h"

class lambertian : public material
{
    public:
        lambertian(const vec3& color) : albedo(color) {}

        virtual bool scatter
        (
            const ray& r_in, const hit_record& rec_in, vec3& attenuation_out, ray& scattered_out
        ) 
        const override
        {
            vec3 scatter_direction = rec_in.normal + random_unit_vector();
            
            //Catch degenerate scatter direction
            if (scatter_direction.is_near_zero())
            {
                scatter_direction = rec_in.normal;
            }
            
            scattered_out = ray(rec_in.point, scatter_direction);
            attenuation_out = albedo;
            return true;
        }

    public:
        vec3 albedo;  
};