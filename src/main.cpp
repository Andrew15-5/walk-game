#include "include/camera.hpp"
#include "include/global.hpp"
#include "include/global_gl.hpp"
#include "include/glut_callback_functions.hpp"

#include <GL/freeglut.h>
#include <IL/il.h>
#include <IL/ilu.h>

Camera camera;

// Note: Z axis is inverted (-z is forward)

void load_textures();

int main(GLint argc, GLchar **argv) {
  // Initialization
  for (GLint i = 0; i < 256; i++) {
    key_pressed[i] = false;
  }
  camera.set_position(0, 8, 8);
  camera.set_mouse_sensitivity(horizontal_sensetivity, vertical_sensetivity);

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

  // Hide cursor
  glutSetCursor(GLUT_CURSOR_NONE);

  // Don't repeat keyboard_key_down_event_listener call if key is held down
  glutIgnoreKeyRepeat(true);

  load_textures();

  glutMainLoop();
}

void load_textures() {
  ilInit();
  iluInit();

  ilLoadImage("res/textures/floor.png");
  iluFlipImage();

  glGenTextures(1, &floor_texture_id);
  glBindTexture(GL_TEXTURE_2D, floor_texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 174, 174, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

  ilDeleteImage(floor_texture_id);
}
