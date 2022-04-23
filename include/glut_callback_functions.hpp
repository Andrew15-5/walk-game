#ifndef GLUT_CALLBACK_FUNCTIONS_HPP
#define GLUT_CALLBACK_FUNCTIONS_HPP

#include <GL/gl.h>

// Timer functions
void move_camera(int);

void display();
void idle();
void keyboard_key_down_event_listener(GLubyte key, GLint x, GLint y);
void keyboard_key_up_event_listener(GLubyte key, GLint x, GLint y);
void keyboard_special_keys_event_listener(GLint key, GLint x, GLint y);
void mouse_move_event_listener(GLint x, GLint y);
void reshape(GLsizei w, GLsizei h);

#endif
