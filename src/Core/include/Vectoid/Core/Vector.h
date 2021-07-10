#ifndef VECTOID_CORE_VECTOR_H_
#define VECTOID_CORE_VECTOR_H_

#include <cmath>
#include <string>
#include <K/Core/NumberTools.h>

using K::Core::NumberTools;

//! 3D graphics and data processing.
namespace Vectoid {
//! 3D core functionality.
namespace Core {

//! Vector in 3-space, also used to describe points in 3-space.
template<typename T>
class Vector {
  public:
    struct HashFunction;

    //! Initializes the vector as <c>0</c>-vector.
    inline Vector();
    inline Vector(T xCoord, T yCoord, T zCoord);
    Vector(const Vector<T> &other)            = default;
    Vector &operator=(const Vector<T> &other) = default;
    Vector(Vector<T> &&other)                 = default;
    Vector &operator=(Vector<T> &&other)      = default;

    //! Computes and returns a hash value for the vector.
    std::size_t Hash() const;
    inline bool operator==(const Vector<T> &other) const;
    inline bool operator!=(const Vector<T> &other) const;
    inline Vector<T> operator-() const;
    inline Vector<T> operator+(const Vector<T> &other) const;
    inline Vector<T> &operator+=(const Vector<T> &other);
    inline Vector<T> operator-(const Vector<T> &other) const;
    
    //! Allows to access the vector's <c>x</c>-, <c>y</c>- and <c>z</c>-elements via the indices <c>0</c>, <c>1</c> and
    //! <c>2</c> respectively.
    inline T &operator[](int i);
    //! Sets the vector as specified.
    inline void Set(T xCoord, T yCoord, T zCoord);
    //! Computes the vector's length.
    inline T Length() const;
    //! Computes the length of the vector's projection into the <c>x/y</c> plane.
    inline T LengthXY() const;
    //! Normalizes the vector to unit length.
    /*!
     *  The resulting normal might not be a <c>Valid()</c> vector.
     */
    inline void Normalize();
    //! Tells whether all components are still finite numbers.
    inline bool Valid() const;
    //! Clamps the vector's components to the specified range.
    inline void ClampComponents(T min, T max);
    //! Produces a verbose representation of the current vector state.
    std::string ToString() const;
    
    T x;
    T y;
    T z;
};

template<typename T>
Vector<T>::Vector() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

template<typename T>
Vector<T>::Vector(T xCoord, T yCoord, T zCoord) {
    x = xCoord;
    y = yCoord;
    z = zCoord;
}

template<typename T>
std::size_t Vector<T>::Hash() const {
    std::size_t hash = 17u;
    hash = hash*31u + std::hash<T>()(x);
    hash = hash*31u + std::hash<T>()(y);
    hash = hash*31u + std::hash<T>()(z);
    return hash;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> &other) const {
    return (x == other.x) && (y == other.y) && (z == other.z);
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T> &other) const {
    return (x != other.x) || (y != other.y) || (z != other.z);
}

template<typename T>
Vector<T> Vector<T>::operator-() const {
    return Vector<T>(-x, -y, -z);
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &other) const {
    return Vector<T>(x + other.x, y + other.y, z + other.z);
}

template<typename T>
Vector<T> &Vector<T>::operator+=(const Vector<T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &other) const {
    return Vector<T>(x - other.x, y - other.y, z - other.z);
}

template<typename T>
T &Vector<T>::operator[](int i) {
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

template<typename T>
void Vector<T>::Set(T xCoord, T yCoord, T zCoord) {
    x = xCoord;
    y = yCoord;
    z = zCoord;
}

template<typename T>
T Vector<T>::Length() const {
    return std::sqrt(x*x + y*y + z*z);
}

template<typename T>
T Vector<T>::LengthXY() const {
    return std::sqrt(x*x + y*y);
}

template<typename T>
void Vector<T>::Normalize() {
    T len = Length();
    x /= len;
    y /= len;
    z /= len;
}

template<typename T>
bool Vector<T>::Valid() const {
    return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
}

template<typename T>
void Vector<T>::ClampComponents(T min, T max) {
    NumberTools::Clamp(&x, min, max);
    NumberTools::Clamp(&y, min, max);
    NumberTools::Clamp(&z, min, max);
}

template<typename T>
std::string Vector<T>::ToString() const {
    char text[200];
    std::sprintf(text, "(%f, %f, %f)", x, y, z);
    return std::string(text);
}

//! Scaling.
template<typename T>
inline Vector<T> operator*(T s, const Vector<T> &v) {
    return Vector<T>(s * v.x, s * v.y, s * v.z);
}

//! Computes the dot product of the two specified vectors.
template<typename T>
inline T DotProduct(const Vector<T> &u, const Vector<T> &v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

//! Computes the cross product of the two specified vectors.
template<typename T>
inline Vector<T> CrossProduct(const Vector<T> &u, const Vector<T> &v) {
    return Vector<T>(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
}

//! Generates the affine combination of two given points for an arbitrary <c>t</c>. Note that if
//! <c>t</c> in <c>[0, 1]</c> then the result is a convex combination.
template<typename T>
inline Vector<T> CombineAffine(T t, const Vector<T> &u, const Vector<T> &v) {
    return (1.0f - t)*u + t*v;
}

//! Generates the convex combination of two given points at <c>t = a/(a + b)</c>, with <c>a</c> and <c>b</c>
//! non-negative and at least one of them positive.
/*!
 *  Input parameters are not checked.
 */
template<typename T>
inline Vector<T> CombineConvex(T a, T b, const Vector<T> &point0, const Vector<T> &point1) {
    T t = a / (a + b);
    NumberTools::Clamp(&t, 0.0f, 1.0f);
    return CombineAffine(t, point0, point1);
}

template<typename T>
struct Vector<T>::HashFunction {
    std::size_t operator()(const Vector<T> &aVector) const {
        return aVector.Hash();
    }
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_VECTOR_H_
