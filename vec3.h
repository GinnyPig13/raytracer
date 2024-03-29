#pragma once

#include <cmath>
#include <iostream>

class vec3 
{
    public:
        double comp[3];
    
    public:
        vec3() : comp{0,0,0} {}
        vec3(double comp0, double comp1, double comp2) : comp{comp0, comp1, comp2} {}

        double x() const {return comp[0];}
        double y() const {return comp[1];}
        double z() const {return comp[2];}

      //vector operators  
        vec3 operator-() const { return vec3(-comp[0], -comp[1], -comp[2]);}
        double operator[](int i) const {return comp[i];}
        double& operator[](int i) {return comp[i];}

        vec3& operator+=(const vec3 &v) 
        {
            comp[0] += v.comp[0];
            comp[1] += v.comp[1];
            comp[2] += v.comp[2];
            return *this;
        }

        vec3& operator*= (const double t) 
        {
            comp[0] *= t;
            comp[1] *= t;
            comp[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) 
        {
            return *this *= 1/t;
        }

        double length() const 
        {
            return sqrt(length_squared());
        }
        
        double length_squared() const
        {
            return comp[0]*comp[0] + comp[1]*comp[1] + comp[2]*comp[2];
        }

        inline static vec3 random() 
        {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max)
        {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        bool is_near_zero() const
        {
            //Return true if the vector is close to zero in all dimensions.
            const double smallest_allowed = 1e-8;
            return (fabs(comp[0]) < smallest_allowed) && (fabs(comp[1]) < smallest_allowed) && (fabs(comp[2]) < smallest_allowed);
        }

};

//utility functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) 
{
    return out << v.comp[0] << ' ' << v.comp[1] << ' ' << v.comp[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) 
{
    return vec3(u.comp[0] + v.comp[0], u.comp[1] + v.comp[1], u.comp[2] + v.comp[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) 
{
    return vec3(u.comp[0] - v.comp[0], u.comp[1] - v.comp[1], u.comp[2] - v.comp[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) 
{
    return vec3(u.comp[0]*v.comp[0], u.comp[1]*v.comp[1], u.comp[2]*v.comp[2]);
}

inline vec3 operator*(double t, const vec3 &v) 
{
    return vec3(t*v.comp[0], t*v.comp[1], t*v.comp[2]);
}

inline vec3 operator*(const vec3 &v, double t) 
{
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t) 
{
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) 
{
    return u.comp[0] * v.comp[0]
         + u.comp[1] * v.comp[1]
         + u.comp[2] * v.comp[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) 
{
    return vec3(u.comp[1] * v.comp[2] - u.comp[2] * v.comp[1],
                u.comp[2] * v.comp[0] - u.comp[0] * v.comp[2],
                u.comp[0] * v.comp[1] - u.comp[1] * v.comp[0]);
}

inline vec3 unit_vector(const vec3 &v) 
{
    return v / v.length();
}

inline vec3 random_point_in_unit_sphere()
{
    while (true)
    {
        vec3 p = vec3::random(-1, 1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector()
{
    return unit_vector(random_point_in_unit_sphere());
}

inline vec3 random_point_in_unit_disk()
{
    while (true)
    {
        vec3 p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;        
    }
    
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2*dot(v, n)*n;
}

vec3 refract(const vec3& incidentRay, const vec3& normal, double initialIndex_over_materialIndex) 
{
    double cos_theta = fmin(dot(-incidentRay, normal), 1.0);
    vec3 refracted_ray_perpendicular = initialIndex_over_materialIndex * (incidentRay + cos_theta * normal);
    vec3 refracted_ray_parallel = -sqrt(fabs(1.0 - refracted_ray_perpendicular.length_squared())) * normal;
    return refracted_ray_perpendicular + refracted_ray_parallel;
}