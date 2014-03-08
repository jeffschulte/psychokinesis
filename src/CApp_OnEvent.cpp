//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }

    if(Event->type == SDL_JOYAXISMOTION) {
        if((Event->jaxis.value < -3200 ) || (Event->jaxis.value > 3200)) {
            if(Event->jaxis.axis == 0) {
                Mainlocy++;
            }
            if(Event->jaxis.axis == 1) {
                Mainlocx++;
            }
        }
    }


    if(Event->type == SDL_KEYDOWN) {
        if(Event->key.keysym.sym == SDLK_LEFT) {
            movingleft = true;
        }
        if(Event->key.keysym.sym == SDLK_RIGHT) {
            movingright = true;
        }
    }

    if(Event->type == SDL_KEYUP) {
        if(Event->key.keysym.sym == SDLK_LEFT) {
            movingleft = false;
        }
        if(Event->key.keysym.sym == SDLK_RIGHT) {
            movingright = false;
        }
    }


    if(Event->type == SDL_JOYBUTTONDOWN) {

        if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0) {
            printf("RumblePlay Fail: %s\n", SDL_GetError());
        }
    }
}

//==============================================================================
