#include "include/texture_functions.hpp"

#include "include/global_gl.hpp"

#include <GL/gl.h>
#include <IL/il.h>
#include <IL/ilu.h>

const std::string texture_path = "res/textures";

void change_current_texture(GLuint *texture_id) {
  if (texture_id) change_current_texture(*texture_id);
}

void change_current_texture(GLuint texture_id) {
  if (texture_id) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
}

void disable_texture() {
  glDisable(GL_TEXTURE_2D);
}

void init_DevIL_library() {
  ilInit();
  iluInit();
}

void load_texture(const std::string &path, GLuint texture_id) {
  ilLoadImage(path.c_str());
  ILinfo image_info;
  iluGetImageInfo(&image_info);
  iluFlipImage();

  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
               image_info.Width,
               image_info.Height,
               0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

  ilDeleteImage(texture_id);
}

void load_textures() {
  init_DevIL_library();

  // Warning: the order of files in array must be exactly the same as
  // the corresponding variable names in TextureId constructor.
  std::string files[] = {
      "floor.png",
      "wall.png",
      "ceiling.png",
  };
  GLuint first_texture = texture_id.first;
  GLuint number_of_textures = texture_id.last;
  for (int i = 0; i < (int)number_of_textures; i++) {
    load_texture(texture_path + '/' + files[i], first_texture + i);
  }
}
