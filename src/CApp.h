//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>

//==============================================================================
class CApp {
    private:
        bool Running;

        SDL_Renderer* renderer;
        SDL_Haptic *haptic;

        int Mainlocx, Mainlocy;

        bool movingright, movingleft;

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
