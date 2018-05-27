//
//  hittables.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef HITTABLLES_H
#define HITTABLLES_H

#include <vector>

#include "hittable.h"

class hittable_list : public hittable {
public:
    std::vector<hittable*> hittables;
    bool hit_by(const ray& r, float t_min, float t_max, hit_record& record) const;
};

bool hittable_list::hit_by(const ray& r, float t_min, float t_max, hit_record& record) const {
    bool any_hit = false;
    double closest = t_max;
    for (const hittable* h : hittables) {
        if(h->hit_by(r, t_min, closest, record)) {
            any_hit = true;
            closest = record.t;
        }
    }
    return any_hit;
}

#endif /* hittables_h */
