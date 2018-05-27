//
//  rng.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/27/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef RNG_H
#define RNG_H

#include <random>

std::random_device rd;
std::mt19937 engine(rd());


#endif /* rng_h */
