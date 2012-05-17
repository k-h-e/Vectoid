//
//  Header.h
//  kxm
//
//  Created by Kai Hergenroether on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_VECTOR_H_
#define KXM_VECTOID_VECTOR_H_


#include <cmath>
#include <string>

/*!
 *  \defgroup Vectoid Vectoid 3D Graphics
 */


namespace kxm {
namespace Vectoid {

//! Vector in 3-space, also used to describe points in 3-space.
/*! 
 *  \ingroup Vectoid
 */ 
class Vector {
  public:
    //! Initializes the vector as <c>0</c>-vector.
    inline Vector();
    inline Vector(float x, float y, float z);
    inline Vector(const Vector &other);
    
    inline bool operator==(const Vector &other) const;
    inline bool operator!=(const Vector &other) const;
    inline Vector operator-() const;
    inline Vector operator+(const Vector &other) const;
    inline Vector &operator+=(const Vector &other);
    inline Vector operator-(const Vector &other) const;
    
    //! Allows to access the vector's <c>x</c>-, <c>y</c>- and <c>z</c>-elements via the
    //! indices <c>0</c>-, <c>1</c>- and <c>2</c> respectively.
    inline float &operator[](int i);
    //! Computes the vector's length.
    inline float Length() const;
    //! Normalizes the vector to unit length (without checking for a division by <c>0</c>!).
    inline void Normalize();
    //! Normalizes the vector to unit length if possible, and returns <c>false</c> without
    //! changing state otherwise.
    inline bool TryNormalize();
    //! Produces a verbose representation of the current vector state.
    inline std::string ToString();
    
    float x, y, z;
};
    
Vector::Vector() {
    x = 0.0f;  y = 0.0f;  z = 0.0f;
}

Vector::Vector(float xCoord, float yCoord, float zCoord) {
    x = xCoord;  y = yCoord;  z = zCoord;
}

Vector::Vector(const Vector &other) {
    x = other.x;  y = other.y;  z = other.z;
}

bool Vector::operator==(const Vector &other) const {
    return (x == other.x) && (y == other.y) && (z == other.z);
}
      
bool Vector::operator!=(const Vector &other) const {
    return (x != other.x) || (y != other.y) || (z != other.z);
}

Vector Vector::operator-() const {
    return Vector(-x, -y, -z);
}
      
Vector Vector::operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector &Vector::operator+=(const Vector &other) {
    x += other.x;  y += other.y;  z += other.z;
    return *this;
}

Vector Vector::operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
}

float &Vector::operator[](int i) {
    switch (i) {
        case 1:
            return y;
        case 2:
            return z;
        case 0:
        default:
            return x;
    }
}

float Vector::Length() const {
    return (float)std::sqrt(x*x + y*y + z*z);
}

void Vector::Normalize() {
    float len = Length();
    x /= len;  y /= len;  z /= len;
}

bool Vector::TryNormalize() {
    float len = Length();
    if (len == 0.0f)
        return false;
    x /= len;  y /= len;  z /= len;
    return true;
}

std::string Vector::ToString() {
    char text[200];
    std::sprintf(text, "(%f,%f,%f)", x, y, z);
    return std::string(text);
}

//! Scaling.
inline Vector operator*(float s, const Vector &v) {
    return Vector(s * v.x, s * v.y, s * v.z);
}

//! Computes the dot product of the two specified vectors.
inline float DotProduct(const Vector &u, const Vector &v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

//! Computes the cross product of the two specified vectors.
inline Vector CrossProduct(const Vector &u, const Vector &v) {
    return Vector(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
}
    
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_VECTOR_H_
