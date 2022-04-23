#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>

#include <GL/gl.h>

struct Vector3 {
    GLfloat x = 0, y = 0, z = 0;

    Vector3(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0)
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

    bool operator==(const Vector3 &v) const {
      return (x == v.x and y == v.y and z == v.z);
    }
};

#endif
