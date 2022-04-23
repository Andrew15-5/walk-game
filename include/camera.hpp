#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "include/global_gl.hpp"
#include "include/vector3.hpp"

#include <cmath>

struct Camera {
    HorVer angle, sensitivity;
    Vector3 position, up{0, 1, 0};

    Camera(Vector3 position = {0, 0, 0}, HorVer angle = {0, 0}, HorVer sensitivity = {100, 100})
        : angle(angle), sensitivity(sensitivity), position(position) {}

    HorVer normalize_angles() {
      GLfloat horizontal_angle = this->angle.horizontal / 180.0f * M_PI *
                                 (sensitivity.horizontal / 100.0f);
      GLfloat vertical_angle = 0;
      return HorVer(horizontal_angle, vertical_angle);
    }

    Vector3 look_at() {
      GLfloat horizontal_angle = normalize_angles().horizontal;
      return Vector3(position.x + sin(horizontal_angle),
                     0,
                     position.z - cos(horizontal_angle));
    }

    void change_angle(GLfloat horizontal_offset, GLfloat vertical_offset) {
      angle.horizontal = horizontal_offset;
      if (std::abs(normalize_angles().horizontal) > 2 * M_PI) {
        angle.horizontal = 0;
      }
    }

    void set_angle(GLfloat horizontal, GLfloat vertical) {
      angle.horizontal += horizontal;
      if (std::abs(normalize_angles().horizontal) > 2 * M_PI) {
        // angle.horizontal = 0;
        angle.horizontal = angle.horizontal - ((angle.horizontal < 0) * -2 + 1) * M_PI;
      }
    }
};

#endif
