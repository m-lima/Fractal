#include <SDL.h>
#include <fmt/ostream.h>

#include "renderer.hpp"

namespace Fractal {
  void Renderer::initialize() {

    // Initialize SDL subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 10) {
      throw std::runtime_error("Could not initialize SDL");
    }

    // Set VSync true
    SDL_GL_SetSwapInterval(1);
  }
}
