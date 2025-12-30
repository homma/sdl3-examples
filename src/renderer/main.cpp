#include <SDL3/SDL.h>
#include <cstdio>
#include <print>

auto draw(SDL_Renderer *ren) -> void {
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderClear(ren);

  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  auto text = "TEST";
  SDL_RenderDebugText(ren, 30, 30, text);

  SDL_RenderPresent(ren);
}

auto main() -> int {
  if (not SDL_Init(SDL_INIT_VIDEO)) {
    std::println(stderr, "failed to init video.");
    std::exit(1);
  }

  SDL_Window *win;
  SDL_Renderer *ren;
  {
    auto title = "SDL3 Window and Renderer";
    auto width = 640;
    auto height = 480;
    auto flags = 0;
    auto success =
        SDL_CreateWindowAndRenderer(title, width, height, flags, &win, &ren);
    if (not success) {
      std::println(stderr, "failed to create window and renderer.");
      std::exit(1);
    }
  }

  SDL_Event event;
  auto quit = false;

  while (not quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        quit = true;
        break;
      }
    }
    draw(ren);
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
