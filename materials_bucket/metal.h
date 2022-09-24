#pragma once

#include "../hittable.h"
#include "material.h"

class metal : public material
{
    public:
        metal(const vec3& color) : albedo(color) {}

        virtual bool scatter (const ray& r_in, const hit_record& rec_in, vec3& attenuation_out, ray& scattered_out) const override
        {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec_in.normal);
            scattered_out = ray(rec_in.point, reflected);
            attenuation_out = albedo;
            return (dot(scattered_out.direction(), rec_in.normal) > 0);
        }
    
    public:
        vec3 albedo;
};