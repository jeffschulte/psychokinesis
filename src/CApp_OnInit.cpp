//==============================================================================
#include "CApp.h"
#include <stdio.h>

//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    SDL_Window *screen = SDL_CreateWindow("Psychokinesis",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_OPENGL);
    if(screen == NULL) {
        return false;
    }


    if((renderer = SDL_CreateRenderer(screen, -1, 0)) == NULL) {
        return false;
    }

    printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );


    SDL_Joystick *joystick;

    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    // Open the device
    haptic = SDL_HapticOpen( 0 );
    if (haptic == NULL) {
        printf("HapticOpen Fail\n");
        // return false;
    }

    // Initialize simple rumble
    if (haptic != NULL && SDL_HapticRumbleInit( haptic ) != 0) {

        printf("RumbleInit Fail: %s\n", SDL_GetError());
        // return false;
    }

    return true;
}

//==============================================================================
