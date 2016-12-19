#include "fractalWidget.hpp"

#include <QMouseEvent>
#include <QWheelEvent>

namespace {

  struct Bounds {
    float x;
    float y;
    float w;
    float h;
  };

  Bounds _bounds = { -1.0f, -1.0f, 1.0f, 1.0f };

  unsigned int mouseX = 0;
  unsigned int mouseY = 0;
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

void FractalWidget::mousePressEvent(QMouseEvent * evt) {
  if (evt->buttons() == Qt::LeftButton) {
    mouseX = evt->x();
    mouseY = evt->y();

    setCursor(Qt::ClosedHandCursor);
  }
}

void FractalWidget::mouseReleaseEvent(QMouseEvent * evt) {
  if (evt->buttons() == Qt::LeftButton) {
    setCursor(Qt::OpenHandCursor);
  }
}

void FractalWidget::mouseMoveEvent(QMouseEvent * evt) {
  if (evt->buttons() == Qt::LeftButton) {

  }
}

void FractalWidget::wheelEvent(QWheelEvent * evt) {

}
  
void FractalWidget::initializeGL() {
  glClearColor(0, 0, 0, 1);
  glDisable(GL_CULL_FACE | GL_DEPTH_TEST | GL_BLEND | GL_STENCIL_TEST);
}

void FractalWidget::paintGL() {
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void FractalWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}
