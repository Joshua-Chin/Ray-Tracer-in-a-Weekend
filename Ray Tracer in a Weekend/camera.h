//
//  camera.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera {
public:
    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 lower_left;
    
    camera() : origin(0,0,0), horizontal(4,0,0), vertical(0,2,0), lower_left(-2,-1,-1) {}
    
    ray get_ray(float u, float v) {
        return ray(origin, lower_left + u * horizontal + v * vertical);
    }
};


#endif /* camera_h */
