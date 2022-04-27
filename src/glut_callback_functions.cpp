#include "include/glut_callback_functions.hpp"

#include "include/camera.hpp"
#include "include/draw_functions.hpp"
#include "include/global.hpp"
#include "include/global_gl.hpp"
#include "include/vector2.hpp"

#include <cmath>

#include <GL/freeglut.h>

extern Camera camera;

void move_camera(int) {
  GLfloat speed = 0.3;
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

  glColor3f(1.0f, 1.0f, 1.0f);
  draw_floor({-100, 0, 100}, {100, 0, -100}, &floor_texture_id);

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
  gluPerspective(FOV, (GLfloat)width / height, NEAR, FAR);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
