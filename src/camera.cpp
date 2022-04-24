#include "include/camera.hpp"

#include <algorithm>

#include <GL/glu.h>

// ============================================================================
// =============================== Private ====================================
// ============================================================================

// ============================= Converters ===================================
HorVerFloat Camera::px_to_rad_multiplier() {
  return HorVerFloat(M_PI * (mouse_sensitivity.horizontal / 100.0f) / 180.0f,
                     M_PI * (mouse_sensitivity.vertical / 100.0f) / 180.0f);
}

// ============================================================================
// =============================== Public ====================================
// ============================================================================

// ============================ Constructors ==================================
Camera::Camera(const Vector3 &position, const HorVerFloat &angle, const HorVerInt &mouse_sensitivity) {
  set_position(position);
  set_angle(angle);
  set_mouse_sensitivity(mouse_sensitivity);
}

// ============================== Getters =====================================
HorVerFloat Camera::get_angle_rad() const {
  return angle;
}

Vector3 Camera::get_position() const {
  return position;
}

HorVerInt Camera::get_sensitivity() const {
  return mouse_sensitivity;
}

// ============================== Setters =====================================
void Camera::set_angle(const HorVerFloat &angle) {
  this->angle = angle;
  normalize_angles();
}

void Camera::set_angle(GLfloat horizontal, GLint vertical) {
  set_angle(HorVerFloat(horizontal, vertical));
}

void Camera::set_mouse_sensitivity(const HorVerInt &mouse_sensitivity) {
  this->mouse_sensitivity = mouse_sensitivity;
  normalize_sensitivity();
}

void Camera::set_mouse_sensitivity(GLint horizontal, GLint vertical) {
  set_mouse_sensitivity(HorVerInt(horizontal, vertical));
}

void Camera::set_position(const Vector3 &position) {
  this->position = position;
}

void Camera::set_position(GLfloat x, GLfloat y, GLfloat z) {
  position = Vector3(x, y, z);
}

// ============================ Normilizers ===================================
void Camera::normalize_angles() {
  GLfloat &h_angle = angle.horizontal;
  GLfloat &v_angle = angle.vertical;
  while (std::abs(h_angle) > 2 * M_PI) {
    h_angle -= ((h_angle < 0) ? -1 : 1) * 2 * M_PI;
  }
  while (std::abs(v_angle) > M_PI_2) {
    v_angle -= ((v_angle < 0) ? -1 : 1) * M_PI_2;
  }
}

void Camera::normalize_sensitivity() {
  GLint &h_sensitivity = mouse_sensitivity.horizontal;
  GLint &v_sensitivity = mouse_sensitivity.vertical;
  h_sensitivity = std::max(1, std::min(100, h_sensitivity));
  v_sensitivity = std::max(1, std::min(100, v_sensitivity));
}

// ========================= Calculate vector =================================
Vector3 Camera::look_vector() {
  return Vector3(sin(angle.horizontal) * cos(angle.vertical),
                 sin(angle.vertical),
                 -cos(angle.horizontal) * cos(angle.vertical));
}

Vector3 Camera::look_at() {
  Vector3 look_vector = this->look_vector();
  return Vector3(position.x + look_vector.x,
                 position.y + look_vector.y,
                 position.z + look_vector.z);
}

Vector3 Camera::right_vector() {
  // The easiest and safest way to calculate right vector is to get a cross
  // product of camera's forward vector (without vertical angle) and absolute
  // up vector. That way if camera's look vector equals to absolute up vector
  // we won't get a zero vector.
  const Vector3 absolute_up = Vector3(0, 1, 0);
  Vector3 forward_vector = Vector3(sin(angle.horizontal),
                                   0,
                                   -cos(angle.horizontal));
  return forward_vector.cross(absolute_up);
}

Vector3 Camera::up_vector() {
  return right_vector().cross(look_vector());
}

// ============================ Convenience ===================================
void Camera::call_gluLookAt() {
  Vector3 center = look_at();
  Vector3 up = up_vector();
  gluLookAt(position.x, position.y, position.z,
            center.x, center.y, center.z,
            up.x, up.y, up.z);
}

// ========================== Everything else =================================
void Camera::change_angle(GLint horizontal_offset, GLint vertical_offset) {
  angle.horizontal += horizontal_offset * px_to_rad_multiplier().horizontal;
  angle.vertical += vertical_offset * px_to_rad_multiplier().vertical;
  const GLfloat ALMOST_PI_2 = 1.57; // Almost M_PI_2 (Pi / 2)
  if (std::abs(angle.vertical) > ALMOST_PI_2) {
    angle.vertical = ((angle.vertical < 0) ? -1 : 1) * ALMOST_PI_2;
  }
  normalize_angles();
}

void Camera::change_position(GLfloat x_offset, GLfloat y_offset, GLfloat z_offset) {
  position.x += x_offset;
  position.y += y_offset;
  position.z += z_offset;
}

void Camera::move(GLfloat right, GLfloat up, GLfloat forward, GLfloat speed) {
  position += right_vector() * right * speed;
  position += up_vector() * up * speed;
  position += look_vector() * forward * speed;
}
