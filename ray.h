#pragma once

#include "vec3.h"

class ray
{
    public:
        ray() {}
        ray(const vec3& origin, const vec3& direction)
            : orig(origin), dir(direction), tm(0)
        {}
        ray(const vec3& origin, const vec3& direction, double time = 0.0)
            :orig(origin), dir(direction), tm(time)
        {}

        vec3 origin() const {return orig;}
        vec3 direction() const {return dir;}
        double time() const {return tm;}

        //gives you the position
        vec3 at(double t) const 
        {
            return orig + t*dir;
        }

    public:
        vec3 orig;
        vec3 dir;
        double tm;
};

