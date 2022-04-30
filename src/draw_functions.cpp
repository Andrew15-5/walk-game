#include "include/draw_functions.hpp"

#include "include/global_gl.hpp"
#include "include/texture_functions.hpp"

#include <algorithm>

const GLfloat texture_size_ratio = 0.25f;

void draw_3d_axis() {
  // Save last color
  GLfloat last_color[4];
  glGetFloatv(GL_CURRENT_COLOR, last_color);

  glLineWidth(2);
  glBegin(GL_LINES);
  // X axis: Red
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0, 0, 0);
  glVertex3f(1000, 0, 0);

  // Y axis: Green
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1000, 0);

  // Z axis: Blue
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1000);
  glEnd();

  // Restore last color
  glColor3fv(last_color);
}

void draw_floor(Vector3 left_front, Vector3 right_back, GLuint texture_id) {
  change_current_texture(texture_id);

  GLfloat x_length = std::abs(left_front.x - right_back.x) * texture_size_ratio;
  GLfloat z_length = std::abs(left_front.z - right_back.z) * texture_size_ratio;

  glBegin(GL_QUADS);
  if (texture_id) glTexCoord2f(0.0f, z_length);
  glVertex3f(left_front.x,
             left_front.y,
             left_front.z);
  if (texture_id) glTexCoord2f(0.0f, 0.0f);
  glVertex3f(left_front.x,
             left_front.y,
             right_back.z);
  if (texture_id) glTexCoord2f(x_length, 0.0f);
  glVertex3f(right_back.x,
             right_back.y,
             right_back.z);
  if (texture_id) glTexCoord2f(x_length, z_length);
  glVertex3f(right_back.x,
             right_back.y,
             left_front.z);
  glEnd();

  if (texture_id) disable_texture();
}

void draw_wall(Vector3 left_bottom, Vector3 right_top, GLuint texture_id) {
  change_current_texture(texture_id);

  GLfloat x_length = std::abs(left_bottom.x - right_top.x) * texture_size_ratio;
  GLfloat y_length = std::abs(left_bottom.y - right_top.y) * texture_size_ratio;
  GLfloat z_length = std::abs(left_bottom.z - right_top.z) * texture_size_ratio;

  GLfloat horizontal_length = std::max(x_length, z_length);

  glBegin(GL_QUADS);
  if (texture_id) glTexCoord2f(0.0f, 0.0f);
  glVertex3f(left_bottom.x, left_bottom.y, left_bottom.z);
  if (texture_id) glTexCoord2f(horizontal_length, 0.0f);
  glVertex3f(right_top.x, left_bottom.y, right_top.z);
  if (texture_id) glTexCoord2f(horizontal_length, y_length);
  glVertex3f(right_top.x, right_top.y, right_top.z);
  if (texture_id) glTexCoord2f(0.0f, y_length);
  glVertex3f(left_bottom.x, right_top.y, left_bottom.z);
  glEnd();

  if (texture_id) disable_texture();
}

void draw_4_wall_room(Vector3 left_bottom_front, Vector3 right_top_back, GLuint texture_id) {
  Vector3 right_bottom_front = Vector3(right_top_back.x,
                                       left_bottom_front.y,
                                       left_bottom_front.z);
  Vector3 right_bottom_back = Vector3(right_top_back.x,
                                      left_bottom_front.y,
                                      right_top_back.z);
  Vector3 right_top_front = Vector3(right_top_back.x,
                                    right_top_back.y,
                                    left_bottom_front.z);
  Vector3 left_bottom_back = Vector3(left_bottom_front.x,
                                     left_bottom_front.y,
                                     right_top_back.z);
  Vector3 left_top_front = Vector3(left_bottom_front.x,
                                   right_top_back.y,
                                   left_bottom_front.z);
  Vector3 left_top_back = Vector3(left_bottom_front.x,
                                  right_top_back.y,
                                  right_top_back.z);
  draw_wall(left_bottom_front, right_top_front, texture_id); // Front wall
  draw_wall(right_bottom_front, right_top_back, texture_id); // Right wall
  draw_wall(right_bottom_back, left_top_back, texture_id); // Back wall
  draw_wall(left_bottom_back, left_top_front, texture_id); // Left wall
}

void draw_ceiling(Vector3 left_front, Vector3 right_back, GLuint texture_id) {
  change_current_texture(texture_id);

  GLfloat x_length = std::abs(left_front.x - right_back.x) * texture_size_ratio;
  GLfloat z_length = std::abs(left_front.z - right_back.z) * texture_size_ratio;

  glBegin(GL_QUADS);
  if (texture_id) glTexCoord2f(x_length, z_length);
  glVertex3f(left_front.x,
             left_front.y,
             left_front.z);
  if (texture_id) glTexCoord2f(0.0f, z_length);
  glVertex3f(right_back.x,
             right_back.y,
             left_front.z);
  if (texture_id) glTexCoord2f(0.0f, 0.0f);
  glVertex3f(right_back.x,
             right_back.y,
             right_back.z);
  if (texture_id) glTexCoord2f(x_length, 0.0f);
  glVertex3f(left_front.x,
             left_front.y,
             right_back.z);
  glEnd();

  if (texture_id) disable_texture();
}

void draw_room(
    Vector3 left_bottom_front,
    Vector3 right_top_back,
    bool what_to_draw[6],
    GLuint texture_ids[3]) {
  const Vector3 &v1 = left_bottom_front;
  const Vector3 &v2 = right_top_back;

  // Composite points
  const Vector3 left_top_front = Vector3(v1.x, v2.y, v1.z);
  const Vector3 right_bottom_back = Vector3(v2.x, v1.y, v2.z);

  int what_to_draw_index = 0;
  if (!what_to_draw or what_to_draw[what_to_draw_index++]) {
    glNormal3f(0.0f, 1.0f, 0.0f);
    draw_floor(left_bottom_front, right_bottom_back, texture_ids[0]);
  }
  if (!what_to_draw or what_to_draw[what_to_draw_index++]) {
    glNormal3f(0.0f, 0.0f, 1.0f);
    draw_wall({v1.x, v1.y, v1.z}, {v2.x, v2.y, v1.z}, texture_ids[1]);
  }
  if (!what_to_draw or what_to_draw[what_to_draw_index++]) {
    glNormal3f(-1.0f, 0.0f, 0.0f);
    draw_wall({v2.x, v1.y, v1.z}, {v2.x, v2.y, v2.z}, texture_ids[1]);
  }
  if (!what_to_draw or what_to_draw[what_to_draw_index++]) {
    glNormal3f(0.0f, 0.0f, -1.0f);
    draw_wall({v2.x, v1.y, v2.z}, {v1.x, v2.y, v2.z}, texture_ids[1]);
  }
  if (!what_to_draw or what_to_draw[what_to_draw_index++]) {
    glNormal3f(1.0f, 0.0f, 0.0f);
    draw_wall({v1.x, v1.y, v2.z}, {v1.x, v2.y, v1.z}, texture_ids[1]);
  }
  if (!what_to_draw or what_to_draw[what_to_draw_index++]) {
    glNormal3f(0.0f, -1.0f, 0.0f);
    draw_ceiling(left_top_front, right_top_back, texture_ids[2]);
  }
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
