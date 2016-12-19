#include "shader.hpp"

#include "istream"

namespace {
  QOpenGLFunctions_4_1_Core * _gl = nullptr;
}

Shader::Shader(QOpenGLFunctions_4_1_Core * gl, const std::string & file) {
  _gl = gl;
}
