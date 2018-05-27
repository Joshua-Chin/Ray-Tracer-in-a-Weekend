//
//  material.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/27/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hittable.h"
#include "rng.h"

class material {
public:
    virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

vec3 random_in_unit_sphere() {
    std::uniform_real_distribution<float> dist(-1, 1);
    vec3 p;
    do {
        p = vec3(dist(engine), dist(engine), dist(engine));
    } while (p.dot(p) > 1);
    return p;
}

class lambertian : public material {
    vec3 a;
public:
    lambertian(const vec3& albedo) : a(albedo) {}
    virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.position + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.position, target - rec.position);
        attenuation *= a;
        return true;
    }
};

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * v.dot(n) * n;
}

class metal : public material {
    vec3 a;
    float f;
public:
    metal(const vec3& albedo) : a(albedo), f(0) {}
    metal(const vec3& albedo, float fuzz): a(albedo), f(fuzz) {}
    virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(r.direction(), rec.normal);
        scattered = ray(rec.position, reflected + f * random_in_unit_sphere());
        attenuation *= a;
        return scattered.direction().dot(rec.normal) > 0;
    }
};

#endif /* material_h */
