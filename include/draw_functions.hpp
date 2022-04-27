#ifndef DRAW_FUNCTIONS_HPP
#define DRAW_FUNCTIONS_HPP

#include "include/vector3.hpp"

#include <GL/gl.h>

// High-level functions

// Y-axis must be the same in both vectors.
void draw_floor(Vector3 corner, Vector3 diagonally_opposite_corner, GLuint *texture_id);

// Basic functions
void draw_rectangle(GLfloat width, GLfloat height, GLfloat color[3] = nullptr, GLfloat z = 0);
void draw_square(GLfloat size, GLfloat color[3] = nullptr, GLfloat z = 0);
void draw_parallelepiped(GLfloat width, GLfloat height, GLfloat depth, GLfloat color[3]);
void draw_parallelepiped(GLfloat width, GLfloat height, GLfloat depth, GLfloat color[6][3]);
void draw_cube(GLfloat size, GLfloat color[3]);
void draw_cube(GLfloat size, GLfloat color[6][3]);

#endif
