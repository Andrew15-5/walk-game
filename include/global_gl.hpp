#ifndef GLOBAL_GL_HPP
#define GLOBAL_GL_HPP

#include <GL/gl.h>

extern const GLfloat FOV;
extern const GLfloat NEAR;
extern const GLfloat FAR;

extern bool key_pressed[256];

// Horizontal/vertical
struct HorVerFloat {
    GLfloat horizontal, vertical;
    HorVerFloat(GLfloat horizontal = 0, GLfloat vertical = 0)
        : horizontal(horizontal), vertical(vertical) {}
};

// Horizontal/vertical
struct HorVerInt {
    GLint horizontal, vertical;
    HorVerInt(GLint horizontal = 0, GLint vertical = 0)
        : horizontal(horizontal), vertical(vertical) {}
};

#endif
