#pragma once

#include <cmath>
#include <iostream>

//using std::sqrt;

class vec3 {
    public:
        double comp[3];
    
    public:
        vec3() : comp{0,0,0} {}
        vec3(double comp0, double comp1, double comp2) : comp{comp0, comp1, comp2} {}

        double x() const 
        { 
            return comp[0];
        }
        
        double y() const 
        { 
            return comp[1];
        }
        
        double z() const 
        { 
            return comp[2];
        }
        
    //     vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]);}
};

using point3 = vec3;
