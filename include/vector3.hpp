#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>

#include <GL/gl.h>

struct Vector3 {
    GLfloat x, y, z;

    Vector3(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f)
        : x(x), y(y), z(z) {}

    Vector3 abs() const {
      return Vector3(std::abs(x), std::abs(y), std::abs(z));
    }

    Vector3 cross(const Vector3 &v) const {
      return Vector3(y * v.z - v.y * z,
                     v.x * z - x * v.z,
                     x * v.y - v.x * y);
    }

    GLfloat dot(const Vector3 &v) const {
      return x * v.x + y * v.y + z * v.z;
    }

    Vector3 operator*(GLfloat value) const {
      return Vector3(x * value, y * value, z * value);
    }

    Vector3 operator+(const Vector3 &v) const {
      return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator+=(const Vector3 &v) {
      return *this = *this + v;
    }

    bool operator==(const Vector3 &v) const {
      return (x == v.x and y == v.y and z == v.z);
    }
};

#endif
