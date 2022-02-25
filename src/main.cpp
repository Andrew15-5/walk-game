#include <GL/freeglut.h>

void display();
void idle();
void keyboard_event_listener(unsigned char key, int x, int y);
void reshape(GLsizei w, GLsizei h);

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Set up window
  glutInitWindowSize(1600, 900);
  glutCreateWindow("Walk game");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard_event_listener);
  glEnable(GL_DEPTH_TEST);

  glutMainLoop();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glutSwapBuffers();
}

void idle() { glutPostRedisplay(); }

void keyboard_event_listener(unsigned char key, int x, int y) {
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

  // Prepare glOrtho arguments
  GLdouble near = 1.0, far = 0.0;
  GLdouble right = 100.0f;
  GLdouble top = right * 2;
  if (width >= height) {
    right *= (GLfloat)width / height;
  } else {
    top *= (GLfloat)height / width;
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-right, right, 0, top, near, far);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}