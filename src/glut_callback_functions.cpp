#include "include/glut_callback_functions.hpp"

#include "include/draw_functions.hpp"
#include "include/global_gl.hpp"

#include <cmath>

#include <GL/freeglut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

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
  glTranslatef(0, 0, -8);
  glRotatef(45, 1, -1, 0);
  draw_cube(5, color);
  glPopMatrix();

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
