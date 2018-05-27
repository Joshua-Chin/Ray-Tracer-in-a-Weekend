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

bool refract(const vec3& v, const vec3& n, float ni_nt, vec3& refracted) {
    float cos1 = -v.dot(n); // check sign
    float cos2_squared = 1 - ni_nt * ni_nt * (1 - cos1) * (1 - cos1);
    if (cos2_squared > 0) {
        float cos2 = sqrt(cos2_squared);
        refracted = ni_nt * v + (ni_nt * cos1 - cos2) * n;
        return true;
    } else {
        return false;
    }
}

float schlick(float cos, float ri) {
    float r0 = (1 - ri) / (1 + ri);
    r0 = r0 * r0;
    return r0 + (1-r0) * pow(1-cos, 5);
}

class dielectric : public material {
    float ri;
    vec3 a;
public:
    dielectric(float refraction_index) : ri(refraction_index), a(1,1,1) {}
    dielectric(const vec3& albedo, float refraction_index) : a(albedo), ri(refraction_index) {}
    
    virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 outward_normal;
        float ni_nt;
        attenuation *= a;
        float cos;
        // check if exiting material
        if (r.direction().dot(rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_nt = ri;
            cos = ri * r.direction().dot(rec.normal);
        } else {
            outward_normal = rec.normal;
            ni_nt = 1 / ri;
            cos = -r.direction().dot(rec.normal);
        }
        
        float reflect_prob;
        vec3 refracted;
        if (refract(r.direction(), outward_normal, ni_nt, refracted)) {
            reflect_prob = schlick(cos, ri);
        } else {
            reflect_prob = 1;
        }
        
        std::uniform_real_distribution<float> d(0, 1);
        if (d(engine) <= reflect_prob) {
            scattered = ray(rec.position, reflect(r.direction(), outward_normal));
        } else {
            scattered = ray(rec.position, refracted);
        }
        return true;
    }
};

#endif /* material_h */
