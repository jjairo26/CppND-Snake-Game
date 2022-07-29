#include "renderer.h"
#include <iostream>
#include <string>

/**
 *  \brief Constructor which initializes SDL, SDL_Image and SDL_Fonts
 */
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //Initialize PNG Loader
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){ //Bit Logic to see if Bit IMG_INIT_PNG is set
	  std::cerr << "IMG_Init could not be started.\n";
    std::cerr << "IMG_Error: " << IMG_GetError() << "\n";
  }

  //Load gift PNG as texture
  std::string giftPNGpath = "../res/gift.png";
  giftTexture = LoadTexture(giftPNGpath); 

  //Initialize Font Library
  TTF_Init();
  font = TTF_OpenFont("../res/BOMBARD.ttf", 26); // File and FontSize
  if (font == nullptr){
    std::cerr << "TTF Font could not be loaded.\n";
    std::cerr << "TTF_Error: " << SDL_GetError() << "\n";
	}

}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
  TTF_Quit();
}

/**
 *  \brief Renders screen, food, snake, gift, and text
 */
void Renderer::Render(Game const *game, Snake const &snake, SDL_Point const &food, Gift const &gift) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  SDL_Color white = { 255, 255, 255 };
  SDL_Color yellow = {233, 252, 20};

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    //Feedback for gift eating:
    //If gift just eaten or less than 1 second has passed since it was eaten
    if (gift.JustEaten() == true || (SDL_GetTicks() - gift.JustEatenTimePoint()) <= 1000)
      SDL_SetRenderDrawColor(sdl_renderer, 0xE9, 0xFC, 0x14, 0xFF);
  } else { //Game Over
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Texture* gameOverTexture = RenderText("Game Over", white);
    //Needed for rendering in the exact center
    SDL_Rect dst;
    SDL_QueryTexture(gameOverTexture, NULL, NULL, &dst.w, &dst.h);
    RenderTexture(gameOverTexture, screen_width/2 - dst.w/2, screen_height/2 - dst.h/2);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render gift to destination given by arguments 2-3 with dimensions given by arguments 4-5)
  RenderTexture(giftTexture, gift.GetPosition().x * block.w, gift.GetPosition().y * block.h, (screen_width / grid_width), (screen_height / grid_height));

  // Render upper left text
  std::string score_str = "Score: " + std::to_string(game->GetScore());
  SDL_Texture* scoreTextTexture = RenderText(score_str, white);
  RenderTexture(scoreTextTexture, 0, 0);
  
  if (gift.Exists() && snake.alive){
    //Time left in seconds
    int giftTimeLeft = (gift.GetTimeLimitMS() - gift.GetTimeSinceCreation())/1000 + 1; 
    //Render gift countdown
    std::string giftTime_str = "Gift countdown: " + std::to_string(giftTimeLeft);

    SDL_Texture* giftCounterTexture = RenderText(giftTime_str, yellow);
    RenderTexture(giftCounterTexture, 0, grid_height);
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

/**
 *  \brief Updates the text in the window title with the current FPS value
 */
void Renderer::UpdateWindowTitle(int fps) {
  std::string title{"FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

/**
 *  \brief Helper function to load a texture from an image
 */
SDL_Texture* Renderer::LoadTexture(const std::string &file){
	SDL_Texture *texture = IMG_LoadTexture(sdl_renderer, file.c_str());
	if (texture == nullptr){
		std::cerr << "Texture could not be loaded.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
	}
	return texture;
}

/**
 *  \brief Renders a texture with given position and dimensions
 */
void Renderer::RenderTexture(SDL_Texture *texture, int x, int y, int w, int h){
	//Setup the destination rectangle position
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(sdl_renderer, texture, NULL, &dst);
}

/**
 *  \brief Renders a texture with a given position and dimensions intrinsic to the texture itself
 */
void Renderer::RenderTexture(SDL_Texture *tex, int x, int y){
	//Setup the destination rectangle
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(sdl_renderer, tex, NULL, &dst);
}

/**
 *  \brief Renders a string with selected color
 */
SDL_Texture* Renderer::RenderText(const std::string &message,	SDL_Color color)
{
	//TTF_RenderText -> Surface -> Texture
	SDL_Surface *surf = TTF_RenderText_Solid(font, message.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		std::cerr << "Error in TTF_RenderText." << "\n";
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surf);
	if (texture == nullptr){
		  std::cerr << "Error creating Texture from Surface." << "\n";
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	return texture;
}