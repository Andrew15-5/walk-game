#include "include/glut_callback_functions.hpp"

#include "include/camera.hpp"
#include "include/draw_functions.hpp"
#include "include/global_gl.hpp"
#include "include/picture.hpp"
#include "include/piramid.hpp"
#include "include/vector2.hpp"

#include <algorithm>
#include <cmath>

#include <GL/freeglut.h>

extern Camera camera;
extern Picture *Wither;
extern Piramid *piramid;

bool light0_enabled = true;

void switch_light0() {
  if (light0_enabled) {
    glDisable(GL_LIGHT0);
  }
  else {
    glEnable(GL_LIGHT0);
  }
  light0_enabled = !light0_enabled;
}

void move_camera(int) {
  GLfloat speed = 0.3f;
  Vector3 move_vector;
  if (key_pressed[GLint('d')] or key_pressed[GLint('D')]) {
    move_vector.x += 1;
  }
  if (key_pressed[GLint('a')] or key_pressed[GLint('A')]) {
    move_vector.x -= 1;
  }
  if (key_pressed[GLint('w')] or key_pressed[GLint('W')]) {
    move_vector.z += 1;
  }
  if (key_pressed[GLint('s')] or key_pressed[GLint('S')]) {
    move_vector.z -= 1;
  }
  move_vector.normalize();
  camera.move(move_vector.x, 0, move_vector.z, speed);

  // Check for keys state every 1 ms
  glutTimerFunc(1, move_camera, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  camera.call_gluLookAt();

  GLfloat room_length = 100.0f;
  GLfloat room_width = 40.0f;
  GLfloat room_height = 20.0f;

  // Section 1
  {
    const Vector3 left_bottom_front = Vector3(-room_width * 0.5f,
                                              0,
                                              -room_length * 0.5f);
    const Vector3 right_top_back = Vector3(room_width * 0.5f,
                                           room_height,
                                           room_length * 0.5f);

    glDisable(GL_LIGHTING);
    Wither->set_position(right_top_back.x - 0.5f, room_height * 0.5f, 0);
    Wither->draw();
    glEnable(GL_LIGHTING);

    bool what_to_draw[6] = {
        true, // Floor
        true, // Front wall
        true, // Right wall
        false, // Back wall
        true, // Left wall
        false}; // Ceiling
    GLuint *texture_ids[3] = {
        &texture_id.floor,
        &texture_id.wall,
        &texture_id.ceiling};
    draw_room_mesh(left_bottom_front, right_top_back, what_to_draw, texture_ids);
    glDisable(GL_LIGHTING);
    glColor3f(0.7f, 0.7f, 0.7f);
    draw_ceiling_mesh(left_bottom_front, right_top_back, texture_ids[2]);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);

    // Set up "room" light
    GLfloat room_x_center = (left_bottom_front.x + right_top_back.x) * 0.5f;
    GLfloat room_z_min = std::min(left_bottom_front.z, right_top_back.z);
    GLfloat room_z_max = std::max(left_bottom_front.z, right_top_back.z);
    GLfloat room_z_1 = (room_z_max - room_z_min) / 3 + room_z_min;
    GLfloat room_z_2 = (room_z_max - room_z_min) / 3 * 2 + room_z_min;

    GLfloat room_light_direction[] = {0.0f, -1.0f, 0.0f};
    GLfloat room_light_ambient[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat room_light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat room_light_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat room_light_cutoff = 90.0f;
    GLfloat room_light_exp = 1.0f;

    GLfloat light1_pos[4] = {room_x_center, right_top_back.y, room_z_1, 1.0f};
    GLfloat light2_pos[4] = {room_x_center, right_top_back.y, room_z_2, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);

    for (int i = 0; i < 2; i++) {
      glLightfv(GL_LIGHT1 + i, GL_SPOT_DIRECTION, room_light_direction);
      glLightfv(GL_LIGHT1 + i, GL_AMBIENT, room_light_ambient);
      glLightfv(GL_LIGHT1 + i, GL_DIFFUSE, room_light_diffuse);
      glLightfv(GL_LIGHT1 + i, GL_SPECULAR, room_light_specular);
      glLightfv(GL_LIGHT1 + i, GL_SPOT_CUTOFF, &room_light_cutoff);
      glLightfv(GL_LIGHT1 + i, GL_SPOT_EXPONENT, &room_light_exp);
    }
  }

  // Section 2
  {
    const Vector3 left_bottom_front = Vector3(-room_width * 0.5f,
                                              0,
                                              room_length * 0.5f);
    const Vector3 right_top_back = Vector3(room_width * 0.5f,
                                           room_height,
                                           room_length * 0.5f + room_width);
    bool what_to_draw[6] = {
        true, // Floor
        false, // Front wall
        false, // Right wall
        true, // Back wall
        true, // Left wall
        true}; // Ceiling
    GLuint *texture_ids[3] = {
        &texture_id.floor,
        &texture_id.wall,
        &texture_id.ceiling};
    draw_room_mesh(left_bottom_front, right_top_back, what_to_draw, texture_ids);

    if (not piramid) {
      piramid = new Piramid(room_width * 0.25f, room_height * 0.5f);
      piramid->set_position(0, room_height * 0.43f, -10.0f);
      piramid->set_primary_color(0.5f, 0.5f, 0.5f);
      piramid->set_outline_color(0.0f, 0.0f, 0.0f);
    }
    piramid->draw();
  }

  // Section 3
  {
    const Vector3 left_bottom_front = Vector3(room_width * 0.5f,
                                              0,
                                              room_length * 0.5f);
    const Vector3 right_top_back = Vector3(room_width * 0.5f + (room_length - room_width),
                                           room_height,
                                           room_length * 0.5f + room_width);
    bool what_to_draw[6] = {
        true, // Floor
        true, // Front wall
        true, // Right wall
        true, // Back wall
        false, // Left wall
        true}; // Ceiling
    GLuint *texture_ids[3] = {
        &texture_id.floor,
        &texture_id.wall,
        &texture_id.ceiling};
    draw_room_mesh(left_bottom_front, right_top_back, what_to_draw, texture_ids);
  }

  // Move cursor to the center of window every drawn frame
  glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

  glutSwapBuffers();
}

void idle() {
  glutPostRedisplay();
}

void keyboard_key_down_event_listener(GLubyte key, GLint x, GLint y) {
  GLint modifiers = glutGetModifiers();
  key_pressed[key] = true;
  switch (key) {
    case 't':
    case 'T':
      switch_light0();
      break;
    case '': // Ctrl+w
    case '': // Ctrl+q
      if (modifiers == GLUT_ACTIVE_CTRL) {
        glutLeaveMainLoop();
      }
      break;
    case 13: // Alt+Enter
      if (modifiers == GLUT_ACTIVE_ALT) {
        glutFullScreenToggle();
      }
      break;
  }
}

void keyboard_key_up_event_listener(GLubyte key, GLint x, GLint y) {
  key_pressed[key] = false;
}

void keyboard_special_keys_event_listener(GLint key, GLint x, GLint y) {
  GLint modifiers = glutGetModifiers();
  switch (key) {
    case GLUT_KEY_F11: // Ctrl+F11 / Ctrl+Shift+F11
      if (modifiers == GLUT_ACTIVE_CTRL or
          modifiers == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_SHIFT)) {
        glutFullScreenToggle();
      }
      break;
  }
}

void mouse_click_event_listener(GLint button, GLint state, GLint x, GLint y) {
  if (state == GLUT_LEFT_BUTTON) {
    switch_light0();
  }
}

void mouse_move_event_listener(GLint x, GLint y) {
  Vector2 cursor_move_offset;
  cursor_move_offset.x = x - int(glutGet(GLUT_WINDOW_WIDTH) / 2);
  cursor_move_offset.y = int(glutGet(GLUT_WINDOW_HEIGHT) / 2) - y;
  camera.change_angle(cursor_move_offset.x, cursor_move_offset.y);
}

void reshape(GLsizei width, GLsizei height) {
  width = width ? width : 1;
  height = height ? height : 1;
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(camera.get_FOV(), (GLfloat)width / height, NEAR, FAR);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
