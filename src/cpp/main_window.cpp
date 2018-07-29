#include "main_window.hpp"
#include "fractal_widget.hpp"

MainWindow::MainWindow()
{
  setCentralWidget(new FractalWidget(this));
}
