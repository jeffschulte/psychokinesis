
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <String>
#include "Entity.h"
#include "Hud.h"


//==============================================================================
class CApp {
    private:
        bool Running;

        SDL_Renderer* renderer;
        SDL_Haptic *haptic;
        SDL_Joystick *joystick;

        int screenw, screenh;

        double xcont;

        double targetx, targety;

        Entity player, wallleft, wallright, walltop, wallbottom;

        Hud mainhud;
    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

//==============================================================================

#endif
