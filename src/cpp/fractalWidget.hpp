#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_1_Core>

class FractalWidget : public QOpenGLWidget, public QOpenGLFunctions_4_1_Core {
  Q_OBJECT

public:
  explicit FractalWidget(QWidget * parent = 0);
  ~FractalWidget();

protected:
  void initializeGL() Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void resizeGL(int width, int height) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent * evt) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent * evt) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent * evt) Q_DECL_OVERRIDE;
  void wheelEvent(QWheelEvent * evt) Q_DECL_OVERRIDE;
};