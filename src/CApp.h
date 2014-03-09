
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>

//==============================================================================
class CApp {
    private:
        bool Running;

        SDL_Renderer* renderer;
        SDL_Haptic *haptic;
        SDL_Joystick *joystick;

        double Mainlocx, Mainlocy;

        double xcont;

        double xvel, yvel;

        double targetx, targety;

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
