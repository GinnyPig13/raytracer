#pragma once

#include "ray.h"

struct hit_record
{
    vec3 point;
    vec3 normal;
    double t;
    bool is_front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) 
    {
        is_front_face = dot(r.direction(), outward_normal) < 0;
        normal = is_front_face ? outward_normal : -outward_normal; 
    }
};

class hittable 
{
    //Uses the ray within a set min and max time value to record whether an object was hit
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const = 0;
};