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
#include "material.h"

vec3 color(const ray& r, const hittable& h, int depth, vec3& attenuation) {
    if (depth == 0) {
        return vec3();
    }
    hit_record record;
    if (h.hit_by(r, 0.001, MAXFLOAT, record)) {
        ray scattered;
        if (record.mat->scatter(r, record, attenuation, scattered)) {
            return color(scattered, h, depth-1, attenuation);
        } else {
            return vec3();
        }
    }
    // background color
    vec3 d = r.direction();
    float t = 0.5 * (d.y() + 1);
    vec3 c = (1 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1);
    return attenuation * c;
}

vec3 color(const ray& r, const hittable& h, int depth) {
    vec3 attenuation = vec3(1);
    return color(r, h, depth, attenuation);
}

int main(int argc, const char * argv[]) {
    int nx = 200;
    int ny = 100;
    int ns = 50;
    int nb = 20;
    
    float gamma = 1 / 2.2;
    
    std::vector<std::uint8_t> image;
    image.resize(4 * ny * nx);
    
    camera cam(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0), 120, float(nx) / float(ny), 2);
    
    hittable_list hl;
    hl.hittables.push_back(new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3))));
    hl.hittables.push_back(new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.2)));
    hl.hittables.push_back(new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5)));
    hl.hittables.push_back(new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0))));

    std::uniform_real_distribution<float> dist(0, 1);
    
    for (int i=0; i < ny; i++) {
        for (int j=0; j < nx; j++) {
            vec3 c;
            for (int n=0; n < ns; n++) {
                float u = (j + dist(engine)) / float(nx);
                float v = 1 - (i + dist(engine)) / float(ny);
                ray r = cam.get_ray(u, v);
                c += color(r, hl, nb);
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
