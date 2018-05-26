//
//  main.cpp
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#include <iostream>
#include <vector>

#include "lodepng.h"
#include "ray.h"

bool hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = r.direction() * r.direction();
    float b = 2 * oc * r.direction();
    float c = oc * oc - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return discriminant > 0;
}

vec3 color(const ray& r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
        return vec3(1, 0, 0);
    }
    vec3 d = r.direction();
    float t = 0.5 * (d.y() + 1);
    return (1 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1);
}

int main(int argc, const char * argv[]) {
    int nx = 200;
    int ny = 100;
    
    std::vector<std::uint8_t> image;
    image.resize(4 * ny * nx);
    
    vec3 origin(0.0, 0.0, 0.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 lower_left(-2.0, -1.0, -1.0);
    
    for (int i=0; i < ny; i++) {
        for (int j=0; j < nx; j++) {
            float u = float(j) / float(nx);
            float v = float(i) / float(ny);
            ray r(origin, lower_left + u * horizontal + v * vertical);
            vec3 c = color(r);
            image[4 * nx * i + 4 * j + 0] = 255 * c.r();
            image[4 * nx * i + 4 * j + 1] = 255 * c.g();
            image[4 * nx * i + 4 * j + 2] = 255 * c.b();
            image[4 * nx * i + 4 * j + 3] = 255; // A
        }
    }
    
    lodepng::encode("/Users/joshuachin/Documents/output.png", image, nx, ny);
}
