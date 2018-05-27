//
//  main.cpp
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>

#include "lodepng.h"

#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "rng.h"

vec3 random_in_unit_sphere() {
    std::uniform_real_distribution<float> dist(-1, 1);
    vec3 p;
    do {
        p = vec3(dist(engine), dist(engine), dist(engine));
    } while (p * p > 1);
    return p;
}

vec3 color(const ray& r, hittable& h, float mul=1) {
    hit_record record;
    if (mul < 0.001) {
        return vec3();
    }
    if (h.hit_by(r, 0.001, MAXFLOAT, record)) {
        vec3 target = record.position + record.normal + random_in_unit_sphere();
        return color(ray(record.position, target - record.position), h, 0.5 * mul);
    }
    vec3 d = r.direction();
    float t = 0.5 * (d.y() + 1);
    return mul * ((1 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1));
}

int main(int argc, const char * argv[]) {
    int nx = 600;
    int ny = 300;
    int ns = 100;
    float gamma = 1 / 2.2;
    
    std::vector<std::uint8_t> image;
    image.resize(4 * ny * nx);
    
    camera cam;
    
    hittable_list hl;
    hl.hittables.push_back(new sphere(vec3(0, 0, -1), 0.5));
    hl.hittables.push_back(new sphere(vec3(0, -100.5, -1), 100));

    std::uniform_real_distribution<float> dist(0, 1);
    
    for (int i=0; i < ny; i++) {
        for (int j=0; j < nx; j++) {
            vec3 c;
            for (int n=0; n < ns; n++) {
                float u = (j + dist(engine)) / float(nx);
                float v = 1 - (i + dist(engine)) / float(ny);
                ray r = cam.get_ray(u, v);
                c += color(r, hl);
            }
            c /= ns;
            image[4 * nx * i + 4 * j + 0] = 255 * pow(c.r(), gamma);
            image[4 * nx * i + 4 * j + 1] = 255 * pow(c.g(), gamma);
            image[4 * nx * i + 4 * j + 2] = 255 * pow(c.b(), gamma);
            image[4 * nx * i + 4 * j + 3] = 255; // A
        }
    }
    
    lodepng::encode("/Users/joshuachin/Documents/output.png", image, nx, ny);
}
