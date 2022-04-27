#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "include/global_gl.hpp"
#include "include/vector3.hpp"

#include <cmath>

class Camera {
    HorVerFloat angle; // Unit: rad [-2π;2π]
    HorVerInt mouse_sensitivity; // Unit: % [1;100]
    Vector3 position; // Unit: px

    // ========================== Normilizers =================================
    void normalize_angles();
    void normalize_sensitivity();

    // =========================== Converters =================================
    HorVerFloat px_to_rad_multiplier();

  public:
    // ========================== Constructors ================================
    Camera(const Vector3 &position = {0, 0, 0},
           const HorVerFloat &angle = {0, 0},
           const HorVerInt &mouse_sensitivity = {100, 100});

    // ============================ Getters ===================================
    HorVerFloat get_angle_rad() const;
    Vector3 get_position() const;
    HorVerInt get_sensitivity() const;

    // ============================ Setters ===================================
    void set_angle(const HorVerFloat &angle);
    void set_angle(GLfloat horizontal, GLint vertical);

    void set_mouse_sensitivity(const HorVerInt &mouse_sensitivity);
    void set_mouse_sensitivity(GLint horizontal, GLint vertical);

    void set_position(const Vector3 &position);
    void set_position(GLfloat x, GLfloat y, GLfloat z);

    // ======================= Calculate vector ===============================
    Vector3 forward_vector();
    Vector3 look_vector();
    Vector3 look_at();
    Vector3 right_vector();
    Vector3 up_vector();

    // ========================== Convenience =================================
    void call_gluLookAt();

    // ======================== Everything else ===============================
    void change_angle(GLint horizontal_offset, GLint vertical_offset);
    // Absolute position
    void change_position(GLfloat x_offset, GLfloat y_offset, GLfloat z_offset);
    // Relative to the camera view (negative number means opposite direction)
    void move(GLfloat right, GLfloat up, GLfloat forward, GLfloat speed);
};

#endif
