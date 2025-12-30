#include <SDL3/SDL.h>
#include <cstdio>
#include <print>

auto main() -> int {
  if (not SDL_Init(SDL_INIT_VIDEO)) {
    std::println(stderr, "failed to init video.");
    std::exit(1);
  }

  SDL_Window *win;
  {
    auto title = "SDL3 Window";
    auto width = 640;
    auto height = 480;
    auto flags = 0;
    win = SDL_CreateWindow(title, width, height, flags);
  }

  SDL_Event event;
  auto quit = false;

  while (not quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
  }

  SDL_DestroyWindow(win);
  SDL_Quit();
}
