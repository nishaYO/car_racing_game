#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "movement.h"

const int SCREEN_WIDTH = 2000;
const int SCREEN_HEIGHT = 1500;

SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer) {

  SDL_Surface *tempSurface = IMG_Load(path);
  if (!tempSurface) {
    std::cerr << "Failed to load image! SDL_Error: " << SDL_GetError()
              << std::endl;
    return nullptr;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_FreeSurface(tempSurface);
  return texture;
}

int main(int argc, char *argv[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // Initialize SDL_image
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "SDL_image could not initialize! SDL_image Error: "
              << IMG_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
      "Car Racing Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // Load car image (top-down view)
  const char *path = "/home/nisha/Desktop/projects/game/assets/car.png";
  SDL_Texture *carTexture = loadTexture(path, renderer);
  if (!carTexture) {
    std::cerr << "Failed to load car image! SDL_Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // Car properties
  SDL_Rect carProp = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 120, 250};
  // Event loop
  bool quit = false;
  SDL_Event event;

  while (!quit) {
    // Handle events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
  
    // Call the new function for movement
    handleMovement(event, carProp, 10);
    
    // Clear screen
    SDL_RenderClear(renderer);

    // Render car texture
    SDL_RenderCopy(renderer, carTexture, NULL, &carProp);

    // Update screen
    SDL_RenderPresent(renderer);

    // Delay to limit frame rate
    SDL_Delay(16); // ~60 FPS
  }

  // Cleanup
  SDL_DestroyTexture(carTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
