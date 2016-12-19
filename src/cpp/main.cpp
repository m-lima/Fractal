#include "renderer.hpp"

#ifdef _WIN32
// Force high performance GPU
extern "C" {
  // NVidia
  __declspec(dllexport) int NvOptimusEnablement = 1;

  // AMD
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

using namespace fractal;

int main() {

  RendererPtr renderer = fractal::Renderer::instance();
  renderer->test = 4;

  RendererPtr renderer2 = fractal::Renderer::instance();
  renderer->test = 5;
  renderer2->test = 5;
  RendererPtr renderer3 = fractal::Renderer::instance();

  return 0;
}