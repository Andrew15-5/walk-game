#ifndef PIRAMID_HPP
#define PIRAMID_HPP

#include "include/texture_functions.hpp"
#include "include/vector3.hpp"

class Piramid {
  private:
    GLfloat width;
    GLfloat height;
    Vector3 position;
    GLfloat last_color[4];
    GLint last_lighting;
    GLfloat last_line_width;
    GLfloat *outline_color;
    GLfloat *primary_color;
    bool lighting;

    bool lighting_is_on() {
      GLint lighting;
      glGetIntegerv(GL_LIGHTING, &lighting);
      return lighting;
    }

    void push_color() {
      glGetFloatv(GL_CURRENT_COLOR, last_color);
    }

    void push_lighting() {
      glGetIntegerv(GL_LIGHTING, &last_lighting);
    }

    void push_line_width() {
      glGetFloatv(GL_LINE_WIDTH, &last_line_width);
    }

    void pop_color() {
      glColor4fv(last_color);
    }

    void pop_lighting() {
      if (last_lighting) {
        glEnable(GL_LIGHTING);
      }
      else {
        glDisable(GL_LIGHTING);
      }
    }

    void pop_line_width() {
      glLineWidth(last_line_width);
    }

  public:
    Piramid(GLfloat width, GLfloat height)
        : width(width), height(height), outline_color(nullptr), primary_color(nullptr), lighting(false) {}

    ~Piramid() {
      delete[] primary_color;
      delete[] outline_color;
    }

    GLfloat get_width() const { return width; }
    GLfloat get_height() const { return height; }
    Vector3 get_position() const { return position; }

    void set_width(GLfloat width) {
      this->width = width;
    }

    void set_height(GLfloat height) {
      this->height = height;
    }

    void set_lighting(bool enable) {
      lighting = enable;
    }

    void set_outline_color(GLfloat red, GLfloat green, GLfloat blue) {
      if (outline_color) delete[] outline_color;
      outline_color = new GLfloat[4]{red, green, blue, 1.0f};
    }

    void set_outline_color(GLfloat color[4]) {
      for (int i = 0; i < 4; i++) {
        outline_color[i] = color[i];
      }
    }

    void set_primary_color(GLfloat red, GLfloat green, GLfloat blue) {
      if (primary_color) delete[] primary_color;
      primary_color = new GLfloat[4]{red, green, blue, 1.0f};
    }

    void set_primary_color(GLfloat color[4]) {
      for (int i = 0; i < 4; i++) {
        primary_color[i] = color[i];
      }
    }

    void set_position(GLfloat x, GLfloat y, GLfloat z) {
      position = Vector3(x, y, z);
    }

    void draw(GLfloat x, GLfloat y, GLfloat z) {
      position = Vector3(x, y, z);
      draw();
    }

    void draw() {
      push_color();
      push_lighting();
      push_line_width();
      glPushMatrix();
      glTranslatef(position.x, position.y, position.z);
      if (lighting) {
        glEnable(GL_LIGHTING);
      }
      else {
        glDisable(GL_LIGHTING);
      }

      // Draw 4 faces
      if (primary_color) glColor4fv(primary_color);
      glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0, height, 0);
      glVertex3f(-width * 0.5f, 0, width * 0.5f);
      glVertex3f(width * 0.5f, 0, width * 0.5f);
      glVertex3f(width * 0.5f, 0, -width * 0.5f);
      glVertex3f(-width * 0.5f, 0, -width * 0.5f);
      glVertex3f(-width * 0.5f, 0, width * 0.5f);
      glEnd();

      // Draw bottom
      glBegin(GL_QUADS);
      glVertex3f(-width * 0.5f, 0, width * 0.5f);
      glVertex3f(-width * 0.5f, 0, -width * 0.5f);
      glVertex3f(width * 0.5f, 0, -width * 0.5f);
      glVertex3f(width * 0.5f, 0, width * 0.5f);
      glEnd();

      glLineWidth(5);
      if (outline_color) glColor4fv(outline_color);

      // Draw 4 bottom lines
      glBegin(GL_LINE_STRIP);
      glVertex3f(-width * 0.5f, 0, width * 0.5f);
      glVertex3f(width * 0.5f, 0, width * 0.5f);
      glVertex3f(width * 0.5f, 0, -width * 0.5f);
      glVertex3f(-width * 0.5f, 0, -width * 0.5f);
      glVertex3f(-width * 0.5f, 0, width * 0.5f);
      glEnd();

      // Draw 2 front lines
      glBegin(GL_LINE_STRIP);
      glVertex3f(-width * 0.5f, 0, width * 0.5f);
      glVertex3f(0, height, 0);
      glVertex3f(width * 0.5f, 0, width * 0.5f);
      glEnd();

      // Draw 2 back lines
      glBegin(GL_LINE_STRIP);
      glVertex3f(width * 0.5f, 0, -width * 0.5f);
      glVertex3f(0, height, 0);
      glVertex3f(-width * 0.5f, 0, -width * 0.5f);
      glEnd();

      glPopMatrix();
      pop_line_width();
      pop_lighting();
      pop_color();
    }
};

#endif
