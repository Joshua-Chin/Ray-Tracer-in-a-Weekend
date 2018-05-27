//
//  vec3.h
//  Ray Tracer in a Weekend
//
//  Created by Joshua Chin on 5/26/18.
//  Copyright © 2018 Joshua Chin. All rights reserved.
//

#ifndef VEC3_H
#define VEC3_H

#include <math.h>

class vec3 {
    float d[3];
    
public:
    vec3() : d{0,0,0} {}
    vec3(float d0) :d{d0, d0, d0} {}
    vec3(float d0, float d1, float d2) : d{d0, d1, d2} {}
    // Accessor Methods
    inline float x() const {return d[0];}
    inline float y() const {return d[1];}
    inline float z() const {return d[2];}
    inline float r() const {return d[0];}
    inline float g() const {return d[1];}
    inline float b() const {return d[2];}
    inline float operator[](int i) const {return d[i];}
    inline float& operator[](int i) {return d[i];}
    
    inline float length() const {
        return sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    }
    
    inline float dot(const vec3& v) const {
        return d[0] * v[0] + d[1] * v[1] + d[2] * v[2];
    }
};

// element-wise addition
inline vec3 operator+(const vec3& v1, const vec3& v2) {
    return vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline vec3& operator+=(vec3& v1, const vec3& v2) {
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
    return v1;
}

// element-wise subtraction
inline vec3 operator-(const vec3& v1, const vec3& v2) {
    return vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

// vectorized multiplication
inline vec3 operator*(float f, const vec3& v) {
    return vec3(f * v[0], f * v[1], f * v[2]);
}

// element-wise multiplication
inline vec3 operator*(const vec3& v1, const vec3& v2) {
    return vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline vec3& operator*=(vec3& v1, const vec3& v2) {
    v1[0] *= v2[0];
    v1[1] *= v2[1];
    v1[2] *= v2[2];
    return v1;
}

// dot product

// vectorized division
inline vec3 operator/(const vec3& v, float f) {
    return vec3(v[0] / f, v[1] / f, v[2] / f);
}

inline vec3& operator/=(vec3& v, float f) {
    v[0] /= f;
    v[1] /= f;
    v[2] /= f;
    return v;
}

inline vec3 normalized(const vec3& v) {
    return v / v.length();
}

#endif /* vec3_h */
