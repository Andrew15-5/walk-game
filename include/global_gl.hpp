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

#endif
