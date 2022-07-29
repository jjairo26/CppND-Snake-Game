#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "snake.h"
#include "game.h"
#include "gift.h"
#include <string>

class Game;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Game const *game, Snake const &snake, SDL_Point const &food, Gift const &gift);
  void UpdateWindowTitle(int score, int fps);

  //Further SDL Helper functions
  SDL_Texture* LoadTexture(const std::string &file);
  void RenderTexture(SDL_Texture *texture, int x, int y, int w, int h);
  void RenderTexture(SDL_Texture *tex, int x, int y);
  SDL_Texture* RenderText(const std::string &message,	SDL_Color color);


 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  SDL_Texture* giftTexture;
  TTF_Font* font;


  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif