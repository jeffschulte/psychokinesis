#include "Application.h"
#include <math.h>


void Application::OnEvent(SDL_Event* Event) {

    if(Event->type == SDL_QUIT) {
        Running = false;
    }

    if(Event->type == SDL_JOYAXISMOTION) {

        if(Event->jaxis.axis == 3) {
            if(Event->jaxis.value > 5000 || Event->jaxis.value < -5000) {
                astate.xcont = (double) Event->jaxis.value / 32767.0;
            }
            else {
                astate.xcont = 0;
            }
        }


        if(Event->jaxis.axis == 0) {
            astate.targetx = (double) Event->jaxis.value / 32767.0;
        }
        if(Event->jaxis.axis == 1) {
            astate.targety = -(double) Event->jaxis.value / 32767.0;
        }
    }


    if(Event->type == SDL_KEYDOWN) {
        if(Event->key.keysym.sym == SDLK_LEFT) {
            astate.xcont--;
        }
        if(Event->key.keysym.sym == SDLK_RIGHT) {
            astate.xcont++;
        }

        if(astate.xcont > 0) {
            astate.xcont = 1;
        }
        else if (astate.xcont < 0) {
            astate.xcont = -1;
        }

        if(Event->key.keysym.sym == SDLK_ESCAPE) {
            Running = false;
        }

        if(Event->key.keysym.sym == SDLK_s) {
            if(music == NULL) {
                music = Mix_LoadMUS("sound_assets/bib.ogg");
                Mix_PlayMusic(music, 1);
            }
        }
    }

    if(Event->type == SDL_KEYUP) {
        if(Event->key.keysym.sym == SDLK_LEFT) {
            astate.xcont++;
        }
        if(Event->key.keysym.sym == SDLK_RIGHT) {
            astate.xcont--;
        }

        if(astate.xcont > 0) {
            astate.xcont = 1;
        }
        else if (astate.xcont < 0) {
            astate.xcont = -1;
        }
    }


    if(Event->type == SDL_JOYBUTTONDOWN) {

        astate.pushing = true;

        if (haptic != NULL) {
            SDL_HapticRunEffect(haptic, effect_id, SDL_HAPTIC_INFINITY);
        }

    }

    if(Event->type == SDL_JOYBUTTONUP) {

        astate.pushing = false;

        if (haptic != NULL) {
            SDL_HapticStopEffect(haptic, effect_id);
        }
    }
}
