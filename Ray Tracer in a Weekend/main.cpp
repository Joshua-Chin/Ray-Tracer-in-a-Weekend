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
    int nx = 1920;
    int ny = 1080;
    int ns = 100;
    int nb = 50;
    float gamma = 1 / 2.2;
    
    std::vector<std::uint8_t> image;
    image.resize(4 * ny * nx);
    
    camera cam(vec3(13,2,3), vec3(0,0,0), vec3(0,1,0), 30, float(nx) / float(ny), 0.1, 10);
    
    std::uniform_real_distribution<float> d(0, 1);
    
    hittable_list hl;
    int l = 11;
    for (int i=-l; i<=l; i++) {
        for (int j=-l; j<l; j++) {
            float mat_choice = d(engine);
            material* mat;
            if (mat_choice <= 0.75) {
                vec3 c = vec3(d(engine), d(engine), d(engine));
                mat = new lambertian(c * c);
            } else if (mat_choice <= 0.9) {
                vec3 c = vec3(d(engine), d(engine), d(engine));
                mat = new metal(0.5 * c + 0.5, 0.5 * d(engine));
            } else {
                mat = new dielectric(1.5);
            }
            vec3 center(i + 0.9 * d(engine), 0.2, j + 0.9 * d(engine));
            hl.hittables.push_back(new sphere(center, 0.2, mat));
        }
    }

    hl.hittables.push_back(new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.8, 0.8, 0.8))));
    hl.hittables.push_back(new sphere(vec3(-4, 1, 0), 1, new lambertian(vec3(0.8, 0.3, 0.3))));
    hl.hittables.push_back(new sphere(vec3(4, 1, 0), 1, new metal(vec3(0.8, 0.6, 0.2), 0)));
    hl.hittables.push_back(new sphere(vec3(0, 1, 0), 1, new dielectric(1.5)));
    
    for (int i=0; i < ny; i++) {
        for (int j=0; j < nx; j++) {
            vec3 c;
            for (int n=0; n < ns; n++) {
                float u = (j + d(engine)) / float(nx);
                float v = 1 - (i + d(engine)) / float(ny);
                ray r = cam.get_ray(u, v);
                c += color(r, hl, nb);
            }
            c /= ns;
            image[4 * nx * i + 4 * j + 0] = 255 * pow(c.r(), gamma);
            image[4 * nx * i + 4 * j + 1] = 255 * pow(c.g(), gamma);
            image[4 * nx * i + 4 * j + 2] = 255 * pow(c.b(), gamma);
            image[4 * nx * i + 4 * j + 3] = 255; // A
        }
        std::cout << "finished row " << i << std::endl;
    }
    
    lodepng::encode("/Users/joshuachin/Documents/output.png", image, nx, ny);
}
