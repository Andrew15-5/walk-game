#ifndef GLOBAL_GL_HPP
#define GLOBAL_GL_HPP

#include <GL/gl.h>

extern const GLfloat FOV;
extern const GLfloat NEAR;
extern const GLfloat FAR;

// Horizontal/vertical
struct HorVer {
    GLfloat horizontal, vertical;
    HorVer(GLfloat horizontal = 0, GLfloat vertical = 0)
        : horizontal(horizontal), vertical(vertical) {}
};

struct Vector2 {
    GLfloat x, y;
    Vector2(GLfloat x = 0, GLfloat y = 0)
        : x(x), y(y) {}
};

struct Vector3 {
    GLfloat x = 0, y = 0, z = 0;
    Vector3(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0)
        : x(x), y(y), z(z) {}
};

#endif
