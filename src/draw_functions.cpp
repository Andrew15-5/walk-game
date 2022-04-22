#include "include/draw_functions.hpp"

void draw_rectangle(GLfloat width, GLfloat height, GLfloat color[3], GLfloat z) {
  if (color) {
    glColor3fv(color);
  }
  glBegin(GL_QUADS);
  glVertex3d(-width / 2, -height / 2, z);
  glVertex3d(width / 2, -height / 2, z);
  glVertex3d(width / 2, height / 2, z);
  glVertex3d(-width / 2, height / 2, z);
  glEnd();
}

void draw_square(GLfloat size, GLfloat color[3], GLfloat z) {
  draw_rectangle(size, size, color, z);
}

void draw_parallelepiped(GLfloat width, GLfloat height, GLfloat depth, GLfloat color[3]) {
  if (color) glColor3fv(color);

  // Front/right/back/left
  for (GLchar i = 0; i < 4; i++) {
    draw_rectangle(width, height, color, depth / 2);
    glRotatef(90, 0, 1, 0);
  }

  // Bottom
  glRotatef(90, 1, 0, 0);
  draw_rectangle(width, height, color, depth / 2);

  // Top
  glRotatef(180, 1, 0, 0);
  draw_rectangle(width, height, color, depth / 2);

  glRotatef(90, 1, 0, 0);
}

void draw_parallelepiped(GLfloat width, GLfloat height, GLfloat depth, GLfloat color[6][3]) {
  int color_index = 0;

  // Front/right/back/left
  for (GLchar i = 0; i < 4; i++) {
    if (color) glColor3fv(color[color_index++]);
    draw_rectangle(width, height, nullptr, depth / 2);
    glRotatef(90, 0, 1, 0);
  }

  // Bottom
  glRotatef(90, 1, 0, 0);
  if (color) glColor3fv(color[color_index++]);
  draw_rectangle(width, height, nullptr, depth / 2);

  // Top
  glRotatef(180, 1, 0, 0);
  if (color) glColor3fv(color[color_index++]);
  draw_rectangle(width, height, nullptr, depth / 2);

  glRotatef(90, 1, 0, 0);
}

void draw_cube(GLfloat size, GLfloat color[3]) {
  draw_parallelepiped(size, size, size, color);
}

void draw_cube(GLfloat size, GLfloat color[6][3]) {
  draw_parallelepiped(size, size, size, color);
}
