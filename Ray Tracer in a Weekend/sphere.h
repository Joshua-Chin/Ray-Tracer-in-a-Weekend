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
    material* mat;
public:
    sphere(const vec3 c, float r, material* m) : center(c), radius(r) {
        mat = m;
    }
    bool hit_by(const ray& r, float t_min, float t_max, hit_record& record) const;
};

bool sphere::hit_by(const ray& r, float t_min, float t_max, hit_record& record) const {
    vec3 oc = r.origin() - center;
    
    float a = r.direction().dot(r.direction());
    float b = oc.dot(r.direction());
    float c = oc.dot(oc) - radius * radius;
    
    float discriminant = b * b - a * c;
    
    if (discriminant >= 0) {
        float t = (-b - sqrt(discriminant)) / a;
        if (t_min < t && t < t_max) {
            record.t = t;
            record.position = r.point_at(t);
            record.normal = (record.position - center) / radius;
            record.mat = mat;
            return true;
        }
        
        t = (-b + sqrt(discriminant)) / a;
        if (t_min < t && t < t_max) {
            record.t = t;
            record.position = r.point_at(t);
            record.normal = (record.position - center) / radius;
            record.mat = mat;
            return true;
        }
    }
    return false;
}


#endif /* sphere_h */
