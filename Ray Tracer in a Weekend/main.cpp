//
//  main.cpp
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#include <iostream>
#include <random>
#include <vector>

#include "lodepng.h"

#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

vec3 color(const ray& r, hittable& h) {
    hit_record record;
    if (h.hit_by(r, 0, MAXFLOAT, record)) {
        vec3 N = record.normal;
        return 0.5 * vec3(N[0]+1, N[1]+1, N[2]+1);
    }
    vec3 d = r.direction();
    float t = 0.5 * (d.y() + 1);
    return (1 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1);
}

int main(int argc, const char * argv[]) {
    int nx = 600;
    int ny = 300;
    int ns = 100;
    
    std::vector<std::uint8_t> image;
    image.resize(4 * ny * nx);
    
    camera cam;
    
    hittable_list hl;
    hl.hittables.push_back(new sphere(vec3(0, 0, -1), 0.5));
    hl.hittables.push_back(new sphere(vec3(0, -100.5, -1), 100));
    
    std::default_random_engine rng;
    std::uniform_real_distribution<float> dist(0, 1);
    
    for (int i=0; i < ny; i++) {
        for (int j=0; j < nx; j++) {
            vec3 c;
            for (int n=0; n < ns; n++) {
                float u = (j + dist(rng)) / float(nx);
                float v = 1 - (i + dist(rng)) / float(ny);
                ray r = cam.get_ray(u, v);
                c += color(r, hl);
            }
            c /= ns;
            image[4 * nx * i + 4 * j + 0] = 255 * c.r();
            image[4 * nx * i + 4 * j + 1] = 255 * c.g();
            image[4 * nx * i + 4 * j + 2] = 255 * c.b();
            image[4 * nx * i + 4 * j + 3] = 255; // A
        }
    }
    
    lodepng::encode("/Users/joshuachin/Documents/output.png", image, nx, ny);
}
