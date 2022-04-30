#ifndef GLOBAL_GL_HPP
#define GLOBAL_GL_HPP

#include <GL/gl.h>

extern const GLfloat NEAR;
extern const GLfloat FAR;
extern const GLfloat MESH_SIZE;

extern bool key_pressed[256];

extern struct TextureId {
    GLuint first;
    GLuint floor;
    GLuint wall;
    GLuint ceiling;
    GLuint last;

    TextureId() {
      last = 1;
      first = last;
      // Add variables after this comment.
      // Note: values are assigned starting from 1.
      // Warning: the values are assigned dynamically, so be careful with
      // variables order.
      floor = last++;
      wall = last++;
      ceiling = last++;
      // Don't add variables below.
      last--;
    }
} texture_id;

// Horizontal/vertical
struct HorVerFloat {
    GLfloat horizontal, vertical;
    HorVerFloat(GLfloat horizontal = 0, GLfloat vertical = 0)
        : horizontal(horizontal), vertical(vertical) {}
};

// Horizontal/vertical
struct HorVerInt {
    GLint horizontal, vertical;
    HorVerInt(GLint horizontal = 0, GLint vertical = 0)
        : horizontal(horizontal), vertical(vertical) {}
};

#endif
