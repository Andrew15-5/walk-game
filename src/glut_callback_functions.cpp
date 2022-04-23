#include "include/glut_callback_functions.hpp"

#include "include/camera.hpp"
#include "include/draw_functions.hpp"
#include "include/global.hpp"
#include "include/global_gl.hpp"
#include "include/vector2.hpp"

#include <cmath>

#include <GL/freeglut.h>

extern Camera camera;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  const Vector3 &cam_look_at = camera.look_at();
  const Vector3 &cam_pos = camera.get_position();
  const Vector3 &cam_up = camera.up();

  gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z,
            cam_look_at.x, cam_look_at.y, cam_look_at.z,
            cam_up.x, cam_up.y, cam_up.z);

  // Front/right/back/left/bottom/top
  // green/red/blue/orange/yellow/white
  GLfloat color[6][3] = {
      {0.0f, 0.5f, 0.0f},
      {0.5f, 0.0f, 0.0f},
      {0.0f, 0.0f, 0.5f},
      {0.5f, 0.3f, 0.0f},
      {0.5f, 0.5f, 0.0f},
      {0.5f, 0.5f, 0.5f}};

  auto cube_size = 5;
  glPushMatrix();
  glRotatef(45, 1, -1, 0);
  draw_cube(cube_size, color);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(cube_size * 2, 0, 0);
  glRotatef(-45, 1, -1, 0);
  draw_cube(cube_size, color);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-cube_size * 2, 0, -cube_size);
  glRotatef(10, 1, -1, 0);
  draw_cube(cube_size, color);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2 * cube_size, 0, cube_size);
  glRotatef(180, 0, 1, 0);
  draw_cube(cube_size, color);
  glPopMatrix();

  // Move cursor to the center of window every drawn frame
  glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

  glutSwapBuffers();
}

void idle() {
  glutPostRedisplay();
}

void keyboard_event_listener(GLubyte key, GLint x, GLint y) {
  GLint modifiers = glutGetModifiers();
  switch (key) {
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

void mouse_move_event_listener(GLint x, GLint y) {
  Vector2 cursor_move_offset;
  cursor_move_offset.x = x - int(glutGet(GLUT_WINDOW_WIDTH) / 2);
  cursor_move_offset.y = y - int(glutGet(GLUT_WINDOW_HEIGHT) / 2);
  camera.change_angle(cursor_move_offset.x, cursor_move_offset.y);
}

void reshape(GLsizei width, GLsizei height) {
  width = width ? width : 1;
  height = height ? height : 1;
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOV, (GLfloat)width / height, NEAR, FAR);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
