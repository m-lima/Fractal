#pragma once

#include <QOpenGLFunctions_4_1_Core>
#include <string>

class Shader {
public:
  Shader(QOpenGLFunctions_4_1_Core * gl, const std::string & file);
  ~Shader();

  void use();
};