#ifndef DRAW_FUNCTIONS_HPP
#define DRAW_FUNCTIONS_HPP

#include "include/vector3.hpp"

#include <GL/gl.h>

// =========================== Complex shapes ===================================
void draw_3d_axis();
void draw_floor(Vector3 left_front, Vector3 right_back, GLuint texture_id);
void draw_wall(Vector3 left_bottom, Vector3 right_top, GLuint texture_id);
void draw_4_wall_room(Vector3 left_bottom_front, Vector3 right_top_back, GLuint texture_id);
void draw_ceiling(Vector3 left_front, Vector3 right_back, GLuint texture_id);

// what_to_draw must contain [floor, front, right, back, left, ceiling] or
// equal to nullptr if everything has to be drawn.
// texture_ids must contain [floor, wall, ceiling].
void draw_room(
    Vector3 left_bottom_front,
    Vector3 right_top_back,
    bool what_to_draw[6],
    GLuint texture_ids[3]);

// ============================ Mesh shapes ===================================
void draw_rectangle_mesh_xy(
    Vector3 left_bottom,
    Vector3 right_top,
    bool flip = false,
    GLuint *texture_id = nullptr);
void draw_rectangle_mesh_xz(
    Vector3 left_back,
    Vector3 right_front,
    bool flip = false,
    GLuint *texture_id = nullptr);
void draw_rectangle_mesh_yz(
    Vector3 bottom_front,
    Vector3 top_back,
    bool flip = false,
    GLuint *texture_id = nullptr);

void draw_ceiling_mesh(
    Vector3 left_bottom_front,
    Vector3 right_top_back,
    GLuint *texture_id = nullptr);

// what_to_draw must contain [floor, front, right, back, left, ceiling] or
// equal to nullptr if everything has to be drawn.
// texture_ids must contain [&floor, &wall, &ceiling].
void draw_room_mesh(
    Vector3 left_bottom_front,
    Vector3 right_top_back,
    bool what_to_draw[6],
    GLuint *texture_ids[3]);

// =========================== Basic shapes ===================================
void draw_rectangle(GLfloat width, GLfloat height, GLfloat color[3] = nullptr, GLfloat z = 0);
void draw_square(GLfloat size, GLfloat color[3] = nullptr, GLfloat z = 0);
void draw_parallelepiped(GLfloat width, GLfloat height, GLfloat depth, GLfloat color[3]);
void draw_parallelepiped(GLfloat width, GLfloat height, GLfloat depth, GLfloat color[6][3]);
void draw_cube(GLfloat size, GLfloat color[3]);
void draw_cube(GLfloat size, GLfloat color[6][3]);

#endif
