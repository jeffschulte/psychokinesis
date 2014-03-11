#include "Application.h"
#include <math.h>


void Application::OnEvent(SDL_Event* Event) {

    if(Event->type == SDL_QUIT) {
        Running = false;
    }

    if(Event->type == SDL_JOYAXISMOTION) {

        if(Event->jaxis.axis == 0) {
            if(Event->jaxis.value > 5000 || Event->jaxis.value < -5000) {
                xcont = (double) Event->jaxis.value / 32767.0;
            }
            else {
                xcont = 0;
            }
        }


        if(Event->jaxis.axis == 3) {
            targetx = (double) Event->jaxis.value / 32767.0;
        }
        if(Event->jaxis.axis == 4) {
            targety = (double) Event->jaxis.value / 32767.0;
        }
    }


    if(Event->type == SDL_KEYDOWN) {
        if(Event->key.keysym.sym == SDLK_LEFT) {
            xcont--;
        }
        if(Event->key.keysym.sym == SDLK_RIGHT) {
            xcont++;
        }

        if(xcont > 0) {
            xcont = 1;
        }
        else if (xcont < 0) {
            xcont = -1;
        }

        if(Event->key.keysym.sym == SDLK_UP) {
            player.yvel += 5;
        }
    }

    if(Event->type == SDL_KEYUP) {
        if(Event->key.keysym.sym == SDLK_LEFT) {
            xcont++;
        }
        if(Event->key.keysym.sym == SDLK_RIGHT) {
            xcont--;
        }

        if(xcont > 0) {
            xcont = 1;
        }
        else if (xcont < 0) {
            xcont = -1;
        }
    }


    if(Event->type == SDL_JOYBUTTONDOWN) {

        pushing = true;

        if (haptic != NULL) {
            SDL_HapticRunEffect(haptic, effect_id, SDL_HAPTIC_INFINITY);
        }
        
        //player.xvel -= 5 * targetx;
        //player.yvel += 5 * targety;

        if(walltop.collideline(player.x, player.y, targetx, targety)) {
            Logger::log("Collision detected with walltop.");
        }
        if(wallleft.collideline(player.x, player.y, targetx, targety)) {
            Logger::log("Collision detected with wallleft.");
        }
        if(wallright.collideline(player.x, player.y, targetx, targety)) {
            Logger::log("Collision detected with wallright.");
        }
        if(wallbottom.collideline(player.x, player.y, targetx, targety)) {
            Logger::log("Collision detected with wallbottom.");
        }
        if(block.collideline(player.x, player.y, targetx, targety)) {
            Logger::log("Collision detected with block.");
        }
    }

    if(Event->type == SDL_JOYBUTTONUP) {

        pushing = false;

        if (haptic != NULL) {
            SDL_HapticStopEffect(haptic, effect_id);
        }
    }
}
