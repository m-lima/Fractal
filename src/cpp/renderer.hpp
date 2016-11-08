#ifndef FRACTAL_RENDERER_HPP
#define FRACTAL_RENDERER_HPP

namespace Fractal {
  class Renderer {
  public:
    static Renderer & instance() {
      static Renderer _instance;
      return _instance;
    }

    //static const std::shared_ptr<Renderer> instancePtr() {
    //  static const std::shared_ptr<Renderer> _instancePtr = std::make_shared<Renderer>(instance());
    //  return _instancePtr;
    //}

    Renderer(const Renderer & renderer) = delete;
    Renderer(const Renderer && renderer) = delete;
    void operator=(const Renderer & renderer) = delete;
    void operator=(const Renderer && renderer) = delete;

    void initialize();
  private:
    Renderer() {}

  };
};

#endif // !FRACTAL_RENDERER_HPP
