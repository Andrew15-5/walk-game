#include "include/glut_callback_functions.hpp"

#include "include/camera.hpp"
#include "include/draw_functions.hpp"
#include "include/global.hpp"
#include "include/global_gl.hpp"

#include <cmath>

#include <GL/freeglut.h>

extern Camera camera;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  const Vector3 &cam_look_at = camera.look_at();
  const Vector3 &cam_pos = camera.position;
  const Vector3 &cam_up = camera.up;

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

  glPushMatrix();
  glRotatef(45, 1, -1, 0);
  draw_cube(5, color);
  glPopMatrix();

  // Move cursor to the center of window every drawn frame
  glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

  glutSwapBuffers();
}

void idle() {
  glutPostRedisplay();
}

void keyboard_event_listener(GLubyte key, GLint x, GLint y) {
  switch (key) {
    case '': // Ctrl+w
    case '': // Ctrl+q
      if (!(glutGetModifiers() & (GLUT_ACTIVE_ALT | GLUT_ACTIVE_SHIFT))) {
        glutLeaveMainLoop();
      }
      break;
  }
}

void mouse_move_event_listener(GLint x, GLint y) {
  Vector2 cursor_move_offset;
  cursor_move_offset.x = x - int(glutGet(GLUT_WINDOW_WIDTH) / 2);
  cursor_move_offset.y = y - int(glutGet(GLUT_WINDOW_HEIGHT) / 2);
  camera.angle.horizontal += cursor_move_offset.x;
  camera.angle.vertical += cursor_move_offset.y;
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
