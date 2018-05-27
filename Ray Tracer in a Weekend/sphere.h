//
//  sphere.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere: public hittable {
    const vec3 center;
    const float radius;
public:
    sphere(const vec3 c, float r) : center(c), radius(r) {}
    bool hit_by(const ray& r, float t_min, float t_max, hit_record& record) const;
};

bool sphere::hit_by(const ray& r, float t_min, float t_max, hit_record& record) const {
    vec3 oc = r.origin() - center;
    
    float a = r.direction() * r.direction();
    float b = oc * r.direction();
    float c = oc * oc - radius * radius;
    
    float discriminant = b * b - a * c;
    
    if (discriminant >= 0) {
        float t = (-b - sqrt(discriminant)) / a;
        if (t_min < t && t < t_max) {
            record.t = t;
            record.position = r.point_at(t);
            record.normal = (record.position - center) / radius;
            return true;
        }
        
        t = (-b + sqrt(discriminant)) / a;
        if (t_min < t && t < t_max) {
            record.t = t;
            record.position = r.point_at(t);
            record.normal = (record.position - center) / radius;
            return true;
        }
    }
    return false;
}


#endif /* sphere_h */
