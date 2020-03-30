#ifndef VECTOID_CORE_VECTOR_H_
#define VECTOID_CORE_VECTOR_H_

#include <cmath>
#include <string>

/*!
 *  \defgroup Vectoid Vectoid
 *  \brief 3D graphics.
 */

namespace Vectoid {
namespace Core {

//! Vector in 3-space, also used to describe points in 3-space.
/*! 
 *  \ingroup Vectoid
 */
template<typename T>
class Vector {
  public:
    //! Initializes the vector as <c>0</c>-vector.
    inline Vector();
    inline Vector(T xCoord, T yCoord, T zCoord);
    inline Vector(const Vector<T> &other);
    // Default copy and move, ok.

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
    //! Normalizes the vector to unit length.
    /*!
     *  The resulting normal might not be a <c>Valid()</c> vector.
     */
    inline void Normalize();
    //! Tells whether all components are still finite numbers.
    inline bool Valid();
    //! Produces a verbose representation of the current vector state.
    inline std::string ToString();
    
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
Vector<T>::Vector(const Vector<T> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
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
void Vector<T>::Normalize() {
    T len = Length();
    x /= len;
    y /= len;
    z /= len;
}

template<typename T>
bool Vector<T>::Valid() {
    return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
}

template<typename T>
std::string Vector<T>::ToString() {
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
    
}    // Namespace Core.
}    // Namespace Vectoid.


#endif    // VECTOID_CORE_VECTOR_H_
