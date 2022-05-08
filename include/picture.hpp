#ifndef PICTURE_HPP
#define PICTURE_HPP

#include "include/texture_functions.hpp"
#include "include/vector2.hpp"
#include "include/vector3.hpp"

#include <IL/il.h>
#include <IL/ilu.h>

class Picture {
    GLuint texture_id;
    Vector2 size;
    Vector3 position;
    GLfloat angle;
    const std::string texture_path = "res/textures";

    void load_texture(const std::string &path) {
      ilLoadImage(path.c_str());
      ILinfo image_info;
      iluGetImageInfo(&image_info);
      iluFlipImage();

      size.x = image_info.Width;
      size.y = image_info.Height;

      glGenTextures(1, &texture_id);
      glBindTexture(GL_TEXTURE_2D, texture_id);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,
                   size.x,
                   size.y,
                   0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

      ilDeleteImage(texture_id);
    }

  public:
    Picture(std::string texture_file_name, GLfloat x = 0, GLfloat y = 0, GLfloat z = 0) {
      texture_id = ::texture_id.last + 1;
      position = Vector3(x, y, z);
      angle = M_PI / 2;
      load_texture(texture_path + '/' + texture_file_name);
    }

    Vector3 get_position() { return position; }
    GLuint get_texture_id() { return texture_id; }
    Vector2 get_size() { return size; }

    void set_angle_rad(GLfloat angle) {
      this->angle = angle;
    }

    void set_angle_deg(GLfloat angle) {
      this->angle = angle / 180 * M_PI;
    }

    void set_position(GLfloat x, GLfloat y, GLfloat z) {
      position = Vector3(x, y, z);
    }

    void set_size(GLfloat width, GLfloat height) {
      size = Vector2(width, height);
    }

    void draw() {
      change_current_texture(texture_id);

      glNormal3f(0.0f, 0.0f, 1.0f);

      Vector3 look_vector(sin(angle),
                          0,
                          -cos(angle));
      Vector3 up_vector = Vector3(0, 1, 0);
      Vector3 right_vector = look_vector.cross(up_vector);

      GLfloat half_length = size.x * 0.5f;
      GLfloat half_height = size.y * 0.5f;

      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(position.x - right_vector.x * half_length,
                 position.y - half_height,
                 position.z - right_vector.z * half_length);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(position.x + right_vector.x * half_length,
                 position.y - half_height,
                 position.z + right_vector.z * half_length);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(position.x + right_vector.x * half_length,
                 position.y + half_height,
                 position.z + right_vector.z * half_length);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(position.x - right_vector.x * half_length,
                 position.y + half_height,
                 position.z - right_vector.z * half_length);
      glEnd();

      if (texture_id) disable_texture();
    }
};

#endif
