#pragma once

#include "misc_constants.h"

class interval
{
    public:
    double min;
    double max;

    interval() : min(+infinity), max(-infinity) {}
    
    interval(double _min, double _max) : min(_min), max(_max) {}

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    static const interval empty, universe;

};

const static interval empty (+infinity, -infinity);
const static interval universe (-infinity, +infinity);
