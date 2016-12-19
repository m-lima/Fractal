#ifndef FRACTAL_RENDERER_HPP
#define FRACTAL_RENDERER_HPP

#include <memory>

namespace fractal {
  class Renderer {
  public:
    static const std::shared_ptr<Renderer> instance();

    Renderer(const Renderer & renderer) = delete;
    Renderer(const Renderer && renderer) = delete;
    void operator=(const Renderer & renderer) = delete;
    void operator=(const Renderer && renderer) = delete;

  private:
    Renderer();
  };
};

using RendererPtr = std::shared_ptr<fractal::Renderer>;

#endif // !FRACTAL_RENDERER_HPP
