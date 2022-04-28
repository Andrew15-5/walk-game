#include "include/draw_functions.hpp"

#include "include/global_gl.hpp"

void draw_floor(Vector3 corner, Vector3 diagonally_opposite_corner, GLuint texture_id) {
  const Vector3 &v1 = corner;
  const Vector3 &v2 = diagonally_opposite_corner;
  if (texture_id) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }

  GLfloat x_length = std::abs(v1.x - v2.x) / 4;
  GLfloat z_length = std::abs(v1.z - v2.z) / 4;

  glBegin(GL_QUADS);
  if (texture_id) glTexCoord2f(0.0f, 0.0f);
  glVertex3f(v1.x, v1.y, v1.z);
  if (texture_id) glTexCoord2f(x_length, 0.0f);
  glVertex3f(v2.x, v2.y, v1.z);
  if (texture_id) glTexCoord2f(x_length, z_length);
  glVertex3f(v2.x, v2.y, v2.z);
  if (texture_id) glTexCoord2f(0.0f, z_length);
  glVertex3f(v1.x, v1.y, v2.z);
  glEnd();

  if (texture_id) glDisable(GL_TEXTURE_2D);
}

void draw_rectangle(GLfloat width, GLfloat height, GLfloat color[3], GLfloat z) {
  if (color) {
    glColor3fv(color);
  }
  glBegin(GL_QUADS);
  glVertex3f(-width / 2, -height / 2, z);
  glVertex3f(width / 2, -height / 2, z);
  glVertex3f(width / 2, height / 2, z);
  glVertex3f(-width / 2, height / 2, z);
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
