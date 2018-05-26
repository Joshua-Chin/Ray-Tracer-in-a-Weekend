//
//  vec3.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef VEC3_H
#define VEC3_H

# include <math.h>

class vec3 {
    const float d[3];
    
public:
    vec3(float x, float y, float z) : d{x, y, z} {}
    // Accessor Methods
    inline float x() const {return d[0];}
    inline float y() const {return d[1];}
    inline float z() const {return d[2];}
    inline float r() const {return d[0];}
    inline float g() const {return d[1];}
    inline float b() const {return d[2];}
    inline float operator[](int i) const {return d[i];}
    
    inline float length() const {
        return sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    }
};

// vector addition
inline vec3 operator+(const vec3 v1, const vec3 v2) {
    return vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

// element-wise multiplication
inline vec3 operator*(float f, const vec3 v) {
    return vec3(f * v[0], f * v[1], f * v[2]);
}

// dot product
inline float operator*(const vec3 v1, const vec3 v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

// element-wise division
inline vec3 operator/(const vec3 v, float f) {
    return vec3(v[0] / f, v[1] / f, v[2] / f);
}

inline vec3 normalized(const vec3 v) {
    return v / v.length();
}

#endif /* vec3_h */
