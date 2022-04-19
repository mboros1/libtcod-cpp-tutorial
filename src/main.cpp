
#include <SDL.h>
#include <libtcod.hpp>

#include <cstdlib>

int main(int argc, char** argv) {
  auto params = TCOD_ContextParams{};
  params.tcod_version = TCOD_COMPILEDVERSION;
  params.argc = argc;
  params.argv = argv;
  params.renderer_type = TCOD_RENDERER_SDL2;
  params.vsync = 1;
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.window_title = "Libtcod CPP Tutorial";

  auto tileset = tcod::load_tilesheet("../data/dejavu16x16_gs_tc.png", {32, 8}, tcod::CHARMAP_TCOD);
  params.tileset = tileset.get();

  auto console = tcod::Console{80, 40};
  params.console = console.get();

  auto context = tcod::new_context(params);

  int playerx=4, playery=4;
  // Game loop.
  while (true) {
    // Rendering.
    console.clear();
    auto& player = console.at(playerx, playery);
    player.ch = '@';
    player.fg.b = 0x0;
    player.fg.g = 0xFF;
    player.fg.r = 0x0;
    context->present(console);

    // Handle input.
    SDL_Event event;
    SDL_WaitEvent(nullptr);
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          std::exit(EXIT_SUCCESS);
        case SDL_KEYDOWN: {
          auto keyPress = event.key.keysym.sym;
          switch (keyPress) {
            case SDLK_UP:
              playery--;
              break;
            case SDLK_DOWN:
              playery++;
              break;
            case SDLK_LEFT:
              playerx--;
              break;
            case SDLK_RIGHT:
              playerx++;
              break;
            default:
              break;
          }
        }
      }
    }
  }
}
