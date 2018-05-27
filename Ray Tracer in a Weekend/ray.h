//
//  ray.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    vec3 o;
    vec3 d;
public:
    ray() {}
    ray(const vec3& origin, const vec3& direction) : o(origin), d(normalized(direction)) {}
    vec3 origin() const {return o;}
    vec3 direction() const {return d;}
    vec3 point_at(float t) const {return o + t * d;}
};

#endif /* ray_h */
