#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere() {}
        sphere(vec3 cen, double r) : center(cen), radius(r) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec
        ) const override;

    public:
        vec3 center;
        double radius;    
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& record) const{
    vec3 rayOrigin_sphereCenter = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(rayOrigin_sphereCenter, r.direction());
    double c = rayOrigin_sphereCenter.length_squared() - radius*radius;
    
    double discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
        
    }
    
    record.t = root;
    record.point = r.at(record.t);
    vec3 outward_normal = (record.point - center) / radius;
    record.set_face_normal(r, outward_normal);

    return true;
}