//
//  hittable.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
public:
    float t;
    vec3 position;
    vec3 normal;
};

class hittable {
public:
    virtual bool hit_by(const ray& r, float t_min, float t_max, hit_record& record) const {return false;}
};

#endif /* hittable_h */
