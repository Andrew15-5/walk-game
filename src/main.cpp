#include "include/camera.hpp"
#include "include/global.hpp"
#include "include/glut_callback_functions.hpp"
#include "include/texture_functions.hpp"

#include <GL/freeglut.h>

Camera camera;

// Note: Z axis is inverted (-z is forward)

void initialize_key_pressed_array();
void initialize_camera();
void set_up_lighting();

int main(GLint argc, GLchar **argv) {
  // Initialization
  initialize_key_pressed_array();
  initialize_camera();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Set up window
  glutInitWindowSize(1600, 900);
  glutCreateWindow("Walk game");

  // Set up callbacks
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard_key_down_event_listener);
  glutKeyboardUpFunc(keyboard_key_up_event_listener);
  glutSpecialFunc(keyboard_special_keys_event_listener);
  glutPassiveMotionFunc(mouse_move_event_listener);
  glutTimerFunc(0, move_camera, 0);

  // Enable capabilities
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  set_up_lighting();

  // Hide cursor
  glutSetCursor(GLUT_CURSOR_NONE);

  // Don't repeat keyboard_key_down_event_listener call if key is held down
  glutIgnoreKeyRepeat(true);

  load_textures();

  glutMainLoop();
}

void initialize_key_pressed_array() {
  for (GLint i = 0; i < 256; i++) {
    key_pressed[i] = false;
  }
}

void initialize_camera() {
  camera.set_position(0, 8, 8);
  camera.set_mouse_sensitivity(horizontal_sensetivity, vertical_sensetivity);
}

void set_up_lighting() {
  // Turn off global ambient light
  GLfloat zero[] = {0.0f, 0.0f, 0.0f, 0.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, zero);

  // Set up "flashlight" light
  GLfloat light_pos[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat light0_direction[] = {0.0f, 0.0f, -1.0f};
  GLfloat light0_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat light0_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat light0_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat cutoff = 90.0f;
  GLfloat light0_exp = 10.0f;
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
  glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
  glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, &light0_exp);
}
