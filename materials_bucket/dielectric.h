#pragma once

#include "../hittable.h"
#include "material.h"

class dielectric : public material
{
    public:
        dielectric(double index_of_refraction) : m_index_of_refraction(index_of_refraction) {}

        virtual bool scatter(const ray& r_in, const hit_record& rec_in, vec3& attenuation_out, ray& scattered_out) const override
        {
            attenuation_out = vec3(1.0, 1.0, 1.0);
            double refraction_ratio = rec_in.is_front_face ? (1.0/m_index_of_refraction) : m_index_of_refraction;

            vec3 unit_direction = unit_vector(r_in.direction());
            double cos_theta = fmin(dot(-unit_direction, rec_in.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool it_cannot_refract = refraction_ratio * sin_theta > 1.0;
            vec3 ray_direction;

            if (it_cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
            {
                ray_direction = reflect(unit_direction, rec_in.normal);
            }

            else
            {
                ray_direction = refract(unit_direction, rec_in.normal, refraction_ratio);
            }
            
            scattered_out = ray(rec_in.point, ray_direction, r_in.time());
            return true;
        }


    public:
        double m_index_of_refraction; 
    
    private:
        static double reflectance(double cosine, double ref_idx)
        {
            //Use Schlick's approximation for reflectance
            double R0 = (1-ref_idx) / (1+ref_idx);
            R0 = R0*R0;
            return R0 + (1-R0)*pow((1-cosine), 5);
        }
};