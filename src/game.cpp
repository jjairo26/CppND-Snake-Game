#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)), gift{-1,-1}, random_foodcount(5,7){
        // gift.x = -1, gift.y = -1 encode a non-available gift
        // random_foodcount: every 5 to 7 foods: gift
  PlaceFood();
  randomCount = random_foodcount(engine);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, gift);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}


void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if snake has reached the food
  if (food.x == new_x && food.y == new_y) {
    score++;
    foodCount++;
    // new food position
    PlaceFood(); 
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  
  //std::cout << "RandomCount: " << randomCount << "\n";
  if ((foodCount%randomCount == 0) && foodCount != 0 && !GiftExists()){
    // new gift position
     PlaceGift();
     giftTimeCounter = SDL_GetTicks();
  }
  // Check if snake has reached the gift
  if (gift.x == new_x && gift.y == new_y){
     score += 5;
     EraseGift();
     foodCount = 0;
     randomCount = random_foodcount(engine); // Generate new random value for count for gift
     snake.speed += 0.02;
  }

  if (GiftExists()){
      int giftPassed = SDL_GetTicks() - giftTimeCounter;
    // Make gift disappear after some time 
      if (giftPassed >= 5000){ //milliseconds
        EraseGift();
        foodCount = 0;
    }
  }
}

void Game::PlaceGift() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // Gift.
    if (!snake.SnakeCell(x, y)) {
      gift.x = x;
      gift.y = y;
      return;
    }
  }
}

void Game::EraseGift(){
    gift.x = -1;
    gift.y = -1;
}

bool Game::GiftExists(){
    return (gift.x != -1 && gift.y != -1);
}
int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

