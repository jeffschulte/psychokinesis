#include "Application.h"
#include <stdio.h>
#include <sstream>


bool Application::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    SDL_Window *screen = SDL_CreateWindow("Psychokinesis",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          screenw, screenh,
                          SDL_WINDOW_OPENGL);
    if(screen == NULL) {
        Logger::log("SDL_CreateWindow failure");
        return false;
    }

    if((renderer = SDL_CreateRenderer(screen, -1, 0)) == NULL) {
        Logger::log("SDL_CreateRenderer failure");
        return false;
    }

    std::stringstream ss;
    ss << SDL_NumJoysticks() << " joysticks were found";
    Logger::log(ss.str());

    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    // Open the device

    haptic = SDL_HapticOpen( 0 );
    if (haptic == NULL) {
        Logger::log("SDL_HapticOpen failure");
        // return false;
    }

    // Initialize simple rumble

    if (haptic != NULL && SDL_HapticRumbleInit( haptic ) != 0) {

        Logger::log("SDL_HapticRumbleInit failure: " + std::string(SDL_GetError()));
        // return false;
    }

    return true;
}
