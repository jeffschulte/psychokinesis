#include "Application.h"


void Application::OnEvent(SDL_Event* Event) {

    if(Event->type == SDL_QUIT) {
        Running = false;
    }

    if(Event->type == SDL_JOYAXISMOTION) {

        if(Event->jaxis.axis == 0) {
            if(Event->jaxis.value > 5000 || Event->jaxis.value < -5000) {
                astate->xcont = (double) Event->jaxis.value / 32767.0;
            }
            else {
                astate->xcont = 0;
            }
        }


        if(Event->jaxis.axis == 3) {
            astate->targetx = (double) Event->jaxis.value / 32767.0;
        }
        if(Event->jaxis.axis == 4) {
            astate->targety = -(double) Event->jaxis.value / 32767.0;
        }
    }


    if(Event->type == SDL_KEYDOWN) {
        if(Event->key.keysym.sym == SDLK_LEFT) {
            astate->xcont--;
        }
        if(Event->key.keysym.sym == SDLK_RIGHT) {
            astate->xcont++;
        }

        if(astate->xcont > 0) {
            astate->xcont = 1;
        }
        else if (astate->xcont < 0) {
            astate->xcont = -1;
        }

        if(Event->key.keysym.sym == SDLK_ESCAPE) {
            Running = false;
        }

    }

    if(Event->type == SDL_KEYUP) {
        if(Event->key.keysym.sym == SDLK_LEFT) {
            astate->xcont++;
        }
        if(Event->key.keysym.sym == SDLK_RIGHT) {
            astate->xcont--;
        }

        if(astate->xcont > 0) {
            astate->xcont = 1;
        }
        else if (astate->xcont < 0) {
            astate->xcont = -1;
        }
    }

    // ref for below:
    //     jbutton.button 0 = A
    //     jbutton.button 1 = B
    //     jbutton.button 2 = X
    //     jbutton.button 3 = Y
    //     jbutton.button 4 = left bump
    //     jbutton.button 5 = right bump

    if (Event->type == SDL_JOYBUTTONDOWN) {
        if (Event->jbutton.button == 4) {
            astate->pushing = true;

            if (haptic != NULL) {
                SDL_HapticRunEffect(haptic, effect_id, SDL_HAPTIC_INFINITY);
            }
        }
        else if (Event->jbutton.button == 3) {
            entities.push_back(Bullet::Create(&Level::p_level->world, graphics,
                                              4, 20, (Player::player->x-4)*10,
                                              (Player::player->y-20)*10));
        }


        /// \todo Get these controls unconnected

        /*else if (Event->jbutton.button == 2) {
            if (ActionState::p_astate->xcont >= 0.0) {
                Player::player->swing_right = true;
            }
            else {
                Player::player->swing_left = true;
            }
        }
        else if (Event->jbutton.button == 3) {
            if (ActionState::p_astate->xcont >= 0.0) {
                Player::player->Shoot(renderer, 0, 0, true);
                Player::player->shoot_right = true;
            }
            else {
                Player::player->Shoot(renderer, 0, 0, false);
                Player::player->shoot_left = true;
            }
            }*/
    }

    if (Event->type == SDL_JOYBUTTONUP) {
        if (Event->jbutton.button == 4) {

            astate->pushing = false;

            if (haptic != NULL) {
                SDL_HapticStopEffect(haptic, effect_id);
            }
        }
    }
}
