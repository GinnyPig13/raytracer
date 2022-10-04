#pragma once

#include "../hittable.h"
#include "material.h"

class dielectric : public material
{
    public:
        dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(const ray& r_in, const hit_record& rec_in, vec3& attenuation_out, ray& scattered_out) const override
        {
            attenuation_out = vec3(1.0, 1.0, 1.0);
            double refraction_ratio = rec_in.is_front_face ? (1.0/ir) : ir;

            vec3 unit_direction = unit_vector(r_in.direction());
            vec3 refracted = refract(unit_direction, rec_in.normal, refraction_ratio);

            scattered_out = ray(rec_in.point, refracted);
            return true;
        }


    public:
        double ir; //Index of Refraction
};