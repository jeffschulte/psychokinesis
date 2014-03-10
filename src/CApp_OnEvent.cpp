//==============================================================================
#include "CApp.h"
#include <math.h>

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
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

        if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0) {
            printf("RumblePlay Fail: %s\n", SDL_GetError());
        }

        player.xvel -= 5 * targetx;
        player.yvel += 5 * targety;

        if(walltop.collideline(player.x, player.y, targetx, targety)) {
            printf("Collision detected with walltop.\n");
        }
        if(wallleft.collideline(player.x, player.y, targetx, targety)) {
            printf("Collision detected with wallleft.\n");
        }
        if(wallright.collideline(player.x, player.y, targetx, targety)) {
            printf("Collision detected with wallright.\n");
        }
        if(wallbottom.collideline(player.x, player.y, targetx, targety)) {
            printf("Collision detected with wallbottom.\n");
        }
        if(block.collideline(player.x, player.y, targetx, targety)) {
            printf("Collision detected with block.\n");
            block.xvel += 5 * targetx;
            block.yvel -= 5 * targety;
        }

        printf("\n");
    }
}

//==============================================================================
