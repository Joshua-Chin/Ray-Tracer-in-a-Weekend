//
//  camera.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "ray.h"
#include "rng.h"

vec3 random_in_unit_disk() {
    vec3 p;
    std::uniform_real_distribution<float> d(-1, 1);
    do {
        p = vec3(d(engine), d(engine), 0);
    } while (p.dot(p) > 1);
    return p;
}

class camera {
    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 lower_left;
    vec3 u, v;
    float lens_radius;
public:
    camera(const vec3& pos, const vec3& lookat, const vec3& up, float hfov, float aspect, float aperture) {
        float theta = hfov * M_PI / 180;
        float half_width = tan(theta/2);
        float half_height = half_width / aspect;
        
        vec3 w = normalized(pos-lookat);
        u = normalized(up.cross(w));
        v = w.cross(u);
        
        float focus = (pos-lookat).length();
        lens_radius = aperture / 2;
        
        origin = pos;
        horizontal = 2 * half_width * focus * u;
        vertical = 2 * half_height * focus * v;
        lower_left = origin - horizontal / 2 - vertical / 2 - focus * w;
    }
    
    ray get_ray(float s, float t) {
        vec3 p = lens_radius * random_in_unit_disk();
        vec3 offset = u * p.x() + v * p.y();
        return ray(origin + offset, lower_left + s * horizontal + t * vertical - origin - offset);
    }
};


#endif /* camera_h */
