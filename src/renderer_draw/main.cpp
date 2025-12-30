#include <SDL3/SDL.h>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <print>

auto point_from_angle_distance(float angle, float radius) -> SDL_FPoint {
  auto radian = angle * std::numbers::pi / 180.0f;

  float x = std::cos(radian) * radius;
  float y = std::sin(radian) * radius;

  return SDL_FPoint{x, y};
}

auto translate_point(SDL_FPoint point, float x, float y) -> SDL_FPoint {
  point.x += x;
  point.y += y;

  return point;
}

auto draw_triangle(SDL_Renderer *ren, float x, float y, float radius) -> void {
  SDL_FPoint points[4];

  points[0] = translate_point(point_from_angle_distance(-90, radius), x, y);
  points[1] = translate_point(point_from_angle_distance(30, radius), x, y);
  points[2] = translate_point(point_from_angle_distance(150, radius), x, y);
  points[3] = points[0];

  SDL_RenderLines(ren, points, 4);
}

auto draw(SDL_Renderer *ren) -> void {
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderClear(ren);

  SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
  draw_triangle(ren, 320, 240, 100);

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
