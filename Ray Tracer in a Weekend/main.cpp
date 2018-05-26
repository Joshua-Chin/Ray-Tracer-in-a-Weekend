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

int main(int argc, const char * argv[]) {
    int nx = 200;
    int ny = 100;
    
    std::vector<std::uint8_t> image;
    image.resize(4 * ny * nx);
    
    for (int i=0; i < ny; i++) {
        for (int j=0; j < nx; j++) {
            float r = float(j) / float(nx);
            float g = float(ny-i) / float(ny);
            float b = 0.2;
            
            image[4 * nx * i + 4 * j + 0] = 255 * r;
            image[4 * nx * i + 4 * j + 1] = 255 * g;
            image[4 * nx * i + 4 * j + 2] = 255 * b;
            image[4 * nx * i + 4 * j + 3] = 255;
        }
    }
    
    lodepng::encode("/Users/joshuachin/Documents/output.png", image, nx, ny);
}
