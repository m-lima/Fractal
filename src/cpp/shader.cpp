#include "shader.hpp"

#include <fmt/ostream.h>

#include "fstream"

namespace {
  QOpenGLFunctions_4_1_Core * _gl = nullptr;

  GLuint _program;

  GLuint readAndCompileShader(const std::string & file, GLenum shaderType) {
    std::ifstream in(fmt::format("opengl/{}", file));

    if (!in.is_open()) {
      fmt::print(stderr, "Could not open {}\n", file);
      std::terminate();
    }

    in.seekg(0, in.end);
    int length = in.tellg();
    in.seekg(0, in.beg);

    std::string buffer;
    buffer.reserve(length);
    buffer.assign(
      std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()
    );
    auto bufferPtr = buffer.c_str();
    in.close();

    fmt::print("Loading {}:\n{}\n", file, buffer);

    auto shader = _gl->glCreateShader(shaderType);
    _gl->glShaderSource(shader, 1, &bufferPtr, &length);

    _gl->glCompileShader(shader);

    GLint isCompiled = 0;
    _gl->glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      _gl->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

      char * log = new char[maxLength];

      _gl->glGetShaderInfoLog(shader, maxLength, &maxLength, log);
      _gl->glDeleteShader(shader);

      fmt::print(stderr, "Failed to compile {}\nLOG: {}", file, log);
      delete[] log;
      return 0;
    }

    return shader;
  }
}

Shader::Shader(QOpenGLFunctions_4_1_Core * gl, const std::string & file) {
  _gl = gl;

  auto vertexShader =
    readAndCompileShader(fmt::format("{}.vs", file), GL_VERTEX_SHADER);
  if (vertexShader == 0) {
    std::terminate();
  }

  auto fragmentShader =
    readAndCompileShader(fmt::format("{}.fs", file), GL_FRAGMENT_SHADER);
  if (fragmentShader == 0) {
    _gl->glDeleteShader(vertexShader);
    std::terminate();
  }

  _program = _gl->glCreateProgram();
  _gl->glAttachShader(_program, vertexShader);
  _gl->glAttachShader(_program, fragmentShader);

  _gl->glLinkProgram(_program);

  GLint isLinked = 0;
  _gl->glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    _gl->glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);

    char * log = new char[maxLength];

    _gl->glGetProgramInfoLog(_program, maxLength, &maxLength, log);
    _gl->glDeleteProgram(_program);
    _gl->glDeleteShader(vertexShader);
    _gl->glDeleteShader(fragmentShader);

    fmt::print(stderr, "Failed to link {}\nLOG: {}", file, log);
    std::terminate();
  }

  _gl->glDetachShader(_program, vertexShader);
  _gl->glDetachShader(_program, fragmentShader);
  _gl->glDeleteShader(vertexShader);
  _gl->glDeleteShader(fragmentShader);

  _gl->glBindFragDataLocation(_program, 0, "FragColor");
}

void Shader::uniform(
  const std::string & uniform,
  float f1, float f2, float f3, float f4
) {
  use();
  auto location = _gl->glGetUniformLocation(_program, uniform.data());
  _gl->glUniform4f(location, f1, f2, f3, f4);
}

void Shader::use() {
  _gl->glUseProgram(_program);
}
