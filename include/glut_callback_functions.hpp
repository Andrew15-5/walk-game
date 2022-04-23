#ifndef GLUT_CALLBACK_FUNCTIONS_HPP
#define GLUT_CALLBACK_FUNCTIONS_HPP

#include <GL/gl.h>

void display();
void idle();
void keyboard_event_listener(GLubyte key, GLint x, GLint y);
void mouse_move_event_listener(GLint x, GLint y);
void reshape(GLsizei w, GLsizei h);

#endif
