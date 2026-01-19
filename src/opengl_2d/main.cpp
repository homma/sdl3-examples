#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <print>

struct AppState {
  SDL_Window *win;
};

auto vec2_from_degree_radius(float degree, float radius) -> glm::vec2 {
  auto radian = glm::radians(degree);
  return glm::vec2{cos(radian) * radius, sin(radian) * radius};
}

auto gl_draw(AppState &app) -> void {
  int w, h;
  SDL_GetWindowSize(app.win, &w, &h);

  glLoadIdentity();

  glViewport(0, 0, w, h);
  glOrtho(0, w, h, 0, 0, 1);

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_TRIANGLES);

  auto radius = 150.0f;
  glm::vec2 p;
  glm::vec2 move{w / 2.0f, h / 2.0f};

  glColor3f(1.0, 0.0, 0.0);
  p = vec2_from_degree_radius(-90.0f, radius);
  p += move;
  glVertex2f(p.x, p.y);

  glColor3f(0.0, 1.0, 0.0);
  p = vec2_from_degree_radius(30.0f, radius);
  p += move;
  glVertex2f(p.x, p.y);

  glColor3f(0.0, 0.0, 1.0);
  p = vec2_from_degree_radius(150.0f, radius);
  p += move;
  glVertex2f(p.x, p.y);

  glEnd();

  SDL_GL_SwapWindow(app.win);
}

auto main() -> int {
  AppState app;

  if (not SDL_Init(SDL_INIT_VIDEO)) {
    std::println(stderr, "failed to init video.");
    std::exit(1);
  }

  // create window
  SDL_Window *win;
  {
    auto title = "SDL3 Window";
    auto width = 640;
    auto height = 480;
    auto flags = SDL_WINDOW_OPENGL;
    win = SDL_CreateWindow(title, width, height, flags);

    if (not win) {
      std::println(stderr, "failed to create window.");
      std::exit(1);
    }

    app.win = win;
  }

  // create OpenGL context
  auto gl_context = SDL_GL_CreateContext(app.win);
  if (not gl_context) {
    std::println(stderr, "failed to create OpenGL context.");
    SDL_DestroyWindow(win);
    SDL_Quit();
    std::exit(1);
  }

  SDL_Event event;
  auto quit = false;

  while (not quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
    gl_draw(app);
  }

  SDL_GL_DestroyContext(gl_context);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
