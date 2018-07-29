#include <QApplication>
#include <QDesktopWidget>

#include "main_window.hpp"

#ifdef _WIN32
// Force high performance GPU
extern "C" {
  // NVidia
  __declspec(dllexport) int NvOptimusEnablement = 1;

  // AMD
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

void center(QWidget & widget) {
  int x, y;
  int screenWidth;
  int screenHeight;

  int WIDTH = widget.width();
  int HEIGHT = widget.height();

  QDesktopWidget *desktop = QApplication::desktop();

  screenWidth = desktop->screen()->width();
  screenHeight = desktop->screen()->height();

  x = (screenWidth - WIDTH) / 2;
  y = (screenHeight - HEIGHT) / 2;

  widget.move(x, y);
}

#if defined(_WIN32) && defined(NDEBUG)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd) {
  int argc = 0;
  QApplication app(argc, 0);
#else
int main(int argc, char * argv[]) {
  QApplication app(argc, argv);
#endif

  app.setApplicationName("Fractal");

  MainWindow mainWindow;
  mainWindow.resize(1024, 768);
  center(mainWindow);

#ifdef NDEBUG
  mainWindow.showFullScreen();
#else
  mainWindow.show();
#endif

  return app.exec();
}