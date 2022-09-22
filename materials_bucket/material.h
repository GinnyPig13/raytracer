#pragma once

#include "misc_constants.h"

struct hit_record;

class material
{
    public:
        virtual bool scatter
        (
            const ray& r_in, const hit_record& rec_in, vec3& attenuation_out, ray& scattered_out
        ) const = 0;
};

