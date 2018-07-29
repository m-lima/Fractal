#include "fractal_widget.hpp"

#include <memory>

#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLFramebufferObject>

#include "fmt/ostream.h"
#include "shader.hpp"

namespace {

  struct Bounds {
    float x;
    float y;
    float w;
    float h;
  };

  Bounds _bounds = { -2.0f, -2.0f, 4.0f, 4.0f };

  float _mouseX;
  float _mouseY;
  float _zoom = 2.0f;

  std::unique_ptr<Shader> _shader;

  QCursor * _zoomFallbackCursor = nullptr;

  GLuint _vao = 0;
}

FractalWidget::FractalWidget(QWidget *parent) :
  QOpenGLWidget(parent)
{
  QSurfaceFormat surfaceFormat;
  surfaceFormat.setDepthBufferSize(24);
  surfaceFormat.setStencilBufferSize(8);
  surfaceFormat.setVersion(4, 1);
  surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(surfaceFormat);

  setFormat(surfaceFormat);
  setCursor(Qt::OpenHandCursor);
}

FractalWidget::~FractalWidget()
{
  if (_shader != nullptr) {
    _shader.reset();
  }
}

void FractalWidget::mousePressEvent(QMouseEvent * evt) {
  if (evt->button() == Qt::LeftButton) {
    _mouseX = evt->x();
    _mouseY = evt->y();

    setCursor(Qt::ClosedHandCursor);
  }
}

void FractalWidget::mouseReleaseEvent(QMouseEvent * evt) {
  if (evt->button() == Qt::LeftButton) {
    setCursor(Qt::OpenHandCursor);
  }
}

void FractalWidget::mouseMoveEvent(QMouseEvent * evt) {
  if (evt->buttons() == Qt::LeftButton) {
    _bounds.x += (_mouseX - evt->x()) * _zoom / width();
    _bounds.y -= (_mouseY - evt->y()) * _zoom / height();

    _shader->uniform(
      "uBounds",
      _bounds.x,
      _bounds.y,
      _bounds.w / width(),
      _bounds.h / height());

    _mouseX = evt->x();
    _mouseY = evt->y();

    update();
  }
}

void FractalWidget::wheelEvent(QWheelEvent * evt) {
//  _zoomFallbackCursor = &cursor();
  setCursor(Qt::CrossCursor);

  if (evt->delta() > 0) {
    _zoom /= 2.0f;
    _bounds.w /= 2.0f;
    _bounds.h /= 2.0f;
    _bounds.x += _bounds.w / 2.0f;
    _bounds.y += _bounds.h / 2.0f;
  } else {
    _zoom *= 2.0f;
    _bounds.x -= _bounds.w / 2.0f;
    _bounds.y -= _bounds.h / 2.0f;
    _bounds.w *= 2.0f;
    _bounds.h *= 2.0f;
  }

  _shader->uniform(
    "uBounds",
    _bounds.x,
    _bounds.y,
    _bounds.w / width(),
    _bounds.h / height());

  update();
}
  
void FractalWidget::initializeGL() {
  initializeOpenGLFunctions();

  glGenVertexArrays(1, &_vao);

  _shader = std::make_unique<Shader>(this, "fractal");

  glClearColor(0, 0, 0, 1);
  glDisable(GL_CULL_FACE | GL_DEPTH_TEST | GL_BLEND | GL_STENCIL_TEST);
}

void FractalWidget::paintGL() {
  QOpenGLFramebufferObject::bindDefault();
  glBindVertexArray(_vao);
  _shader->use();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glUseProgram(0);

//  if (_zoomFallbackCursor != nullptr) {
//    setCursor(*_zoomFallbackCursor);
//    _zoomFallbackCursor = nullptr;
//  }
}

void FractalWidget::resizeGL(int width, int height) {
  if (_shader != nullptr) {
    _shader->uniform(
      "uBounds", _bounds.x, _bounds.y, _bounds.w / width, _bounds.h / height);
  }

  glViewport(0, 0, width, height);
}