#include "include/camera.hpp"
#include "include/global.hpp"
#include "include/glut_callback_functions.hpp"

#include <GL/freeglut.h>

Camera camera;

int main(int argc, char **argv) {
  camera.position.z = 8;
  camera.sensitivity.horizontal = horizontal_sensetivity;
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
  glutSpecialFunc(keyboard_special_keys_event_listener);
  glutPassiveMotionFunc(mouse_move_event_listener);

  glEnable(GL_DEPTH_TEST);
  glutSetCursor(GLUT_CURSOR_NONE);
  glEnable(GL_CULL_FACE);

  glutMainLoop();
}
