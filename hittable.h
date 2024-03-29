#pragma once

#include "ray.h"
#include "interval.h"
#include "misc_constants.h"

class material;

struct hit_record
{
    vec3 point;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
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
        virtual bool hit(const ray& r, interval ray_t, hit_record& record) const = 0;
};