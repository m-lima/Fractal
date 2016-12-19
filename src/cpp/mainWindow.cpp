#include "mainWindow.hpp"
#include "fractalWidget.hpp"

MainWindow::MainWindow()
{
  setCentralWidget(new FractalWidget(this));
}
