#include "include/glut_callback_functions.hpp"

#include <GL/freeglut.h>


int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Set up window
  glutInitWindowSize(1600, 900);
  glutCreateWindow("Walk game");

  // Set up callbacks
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard_event_listener);

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();
}
