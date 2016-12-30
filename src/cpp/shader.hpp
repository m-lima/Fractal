#pragma once

#include <QOpenGLFunctions_4_1_Core>
#include <string>

class Shader {
public:
  Shader(QOpenGLFunctions_4_1_Core * gl, const std::string & file);
  ~Shader() = default;

  void use();
  void uniform(
    const std::string & uniform,
    float f1, float f2, float f3, float f4
  );
};