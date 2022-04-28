#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>

#include <GL/gl.h>

struct Vector2 {
    GLfloat x, y;

    Vector2(GLfloat x = 0.0f, GLfloat y = 0.0f)
        : x(x), y(y) {}

    Vector2 abs() const {
      return Vector2(std::abs(x), std::abs(y));
    }

    GLfloat cross(const Vector2 &v) const {
      return x * v.y - y * v.x;
    }

    GLfloat dot(const Vector2 &v) const {
      return x * v.x + y * v.y;
    }

    bool operator==(const Vector2 &v) const {
      return (x == v.x and y == v.y);
    }
};

#endif
