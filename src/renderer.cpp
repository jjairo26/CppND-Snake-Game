#include "renderer.h"
#include <iostream>
#include <string>

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
  giftTexture = loadTexture(giftPNGpath); 

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

void Renderer::Render(Snake const &snake, SDL_Point const &food, SDL_Point const &gift) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

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
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render gift to destination given by arguments 2-3 with dimensions given by arguments 4-5)
  renderTexture(giftTexture, gift.x * block.w, gift.y * block.h, (screen_width / grid_width), (screen_height / grid_height));

  // Render Text
  SDL_Color color = { 255, 255, 255 };
  SDL_Texture* textTexture = renderText("My C++ Snake Game", color);
  renderTexture(textTexture, 0, 0);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

SDL_Texture* Renderer::loadTexture(const std::string &file){
	SDL_Texture *texture = IMG_LoadTexture(sdl_renderer, file.c_str());
	if (texture == nullptr){
		std::cerr << "Texture could not be loaded.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
	}
	return texture;
}

void Renderer::renderTexture(SDL_Texture *texture, int x, int y, int w, int h){
	//Setup the destination rectangle position
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(sdl_renderer, texture, NULL, &dst);
}

void Renderer::renderTexture(SDL_Texture *tex, int x, int y){
	//Setup the destination rectangle
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(sdl_renderer, tex, NULL, &dst);
}

SDL_Texture* Renderer::renderText(const std::string &message,	SDL_Color color)
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
	//SDL_RenderCopy(sdl_renderer, texture, NULL, NULL);

}