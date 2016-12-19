#include <fmt/ostream.h>

#include "renderer.hpp"

namespace {
  RendererPtr _instancePtr = nullptr;
}

namespace fractal {

  const RendererPtr Renderer::instance() {
    if (_instancePtr == nullptr) {
      _instancePtr = RendererPtr(new Renderer());
    }
    return _instancePtr;
  }

  Renderer::Renderer() {

    // Initialize SDL subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
      throw std::runtime_error("Could not initialize SDL");
    }

    // Set up context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetSwapInterval(0);
  }

}
