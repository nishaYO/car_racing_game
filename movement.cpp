#include "movement.h" 

void handleMovement(SDL_Event event, SDL_Rect &carProp, int speed) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) {
        carProp.y -= speed; // Move up
    }
    if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) {
        carProp.y += speed; // Move down
    }
    if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) {
        carProp.x -= speed; // Move left
    }
    if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) {
        carProp.x += speed; // Move right
    }
}

