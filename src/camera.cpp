#include "include/camera.hpp"

#include <algorithm>

// ============================================================================
// =============================== Private ====================================
// ============================================================================

// ============================= Converters ===================================
GLfloat Camera::px_to_rad_multiplier() {
  return M_PI * (mouse_sensitivity.horizontal / 100.0f) / 180.0f;
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

void Camera::set_position(const Vector3 &position) {
  this->position = position;
}

void Camera::set_position(GLfloat x, GLfloat y, GLfloat z) {
  position = Vector3(x, y, z);
}

void Camera::set_mouse_sensitivity(const HorVerInt &mouse_sensitivity) {
  this->mouse_sensitivity = mouse_sensitivity;
  normalize_sensitivity();
}

void Camera::set_mouse_sensitivity(GLint horizontal, GLint vertical) {
  set_mouse_sensitivity(HorVerInt(horizontal, vertical));
}

// ============================ Normilizers ===================================
void Camera::normalize_angles() {
  GLfloat &h_angle = angle.horizontal;
  GLfloat &v_angle = angle.vertical;
  while (std::abs(h_angle) > 2 * M_PI) {
    h_angle -= ((h_angle < 0) ? -1 : 1) * 2 * M_PI;
  }
  while (std::abs(v_angle) > 2 * M_PI) {
    v_angle -= ((v_angle < 0) ? -1 : 1) * 2 * M_PI;
  }
}

void Camera::normalize_sensitivity() {
  GLint &h_sensitivity = mouse_sensitivity.horizontal;
  GLint &v_sensitivity = mouse_sensitivity.vertical;
  h_sensitivity = std::max(1, std::min(100, h_sensitivity));
  v_sensitivity = std::max(1, std::min(100, v_sensitivity));
}

// ========================== Everything else =================================

void Camera::change_angle(GLint horizontal_offset, GLint vertical_offset) {
  angle.horizontal += horizontal_offset * px_to_rad_multiplier();
  angle.vertical += vertical_offset * px_to_rad_multiplier();
  normalize_angles();
}

void Camera::change_position(GLfloat x_offset, GLfloat y_offset, GLfloat z_offset) {
  position.x += x_offset;
  position.y += y_offset;
  position.z += z_offset;
}

void Camera::move(GLfloat right, GLfloat up, GLfloat forward, GLfloat speed) {
  Vector3 forward_vector = this->look_vector();
  Vector3 up_vector = this->up();
  Vector3 right_vector = up_vector.cross(forward_vector);
  forward_vector.z *= -1;
  right_vector.z *= -1;
  position += right_vector * right * speed;
  position += up_vector * up * speed;
  position += forward_vector * forward * speed;
}

Vector3 Camera::look_vector() {
  GLfloat horizontal_angle = angle.horizontal;
  return Vector3(sin(horizontal_angle), 0, cos(horizontal_angle));
}

Vector3 Camera::look_at() {
  Vector3 look_vector = this->look_vector();
  return Vector3(position.x + look_vector.x,
                 0,
                 position.z - look_vector.z);
}

Vector3 Camera::up() {
  return Vector3(0, 1, 0);
}
