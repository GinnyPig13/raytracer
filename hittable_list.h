#pragma once

#include "hittable.h"
#include <memory>
#include <vector>

class hittable_list : public hittable 
{
    public:
        hittable_list() {}
        hittable_list(std::shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;
    
    public:
        std::vector<std::shared_ptr<hittable>> objects;
};

bool  hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    //If the ray hits nothing
    hit_record temp_rec;
    bool is_anything_hit = false;
    double closest_so_far = t_max;

    //If the ray hits something, record hit and set the maximum for the ray to closest so far
    //in order to properly show overlapping objects
    for(const std::shared_ptr<hittable>& object : objects) 
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            is_anything_hit = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        } 
    }

    return is_anything_hit;
}