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

class material;

class hit_record {
public:
    float t;
    vec3 position;
    vec3 normal;
    material* mat;
    hit_record() {}
    hit_record(float t0, const vec3& p, const vec3& n, material* m) : t(t0), position(p), normal(normalized(n)), mat(m) {}
};

class hittable {
public:
    virtual bool hit_by(const ray& r, float t_min, float t_max, hit_record& record) const = 0;
};

#endif /* hittable_h */
