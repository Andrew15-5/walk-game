#ifndef TEXTURE_FUNCITONS_HPP
#define TEXTURE_FUNCITONS_HPP

#include "include/global_gl.hpp"

#include <string>

void change_current_texture(GLuint *texture_id);
void change_current_texture(GLuint texture_id);
void disable_texture();
void load_textures();

#endif
