#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "SDL_image.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "gift.h"

class Renderer; 

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  Gift gift;
  int foodCount{0}; 
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_foodcount; //if reaches randomCount: gift appearance
  int randomCount; //Values between 5 and 7, for gift appearance, see constructor
  int score{0};

  void PlaceFood();
  void Update();
  void PlaceGift();
  void EraseGift();
};

#endif