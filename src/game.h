#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "SDL_image.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  //SDL_Texture* getGiftTexture(){ return gift_tex; };
  //SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *sdl_renderer);


 private:
  Snake snake;
  SDL_Point food;

  //SDL_Texture* gift_tex;

  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif