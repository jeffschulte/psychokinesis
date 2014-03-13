#include <stdio.h>
#include <sstream>

#include "Application.h"


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
        haptic = NULL;
        // return false;
    }

    SDL_HapticEffect effect;
    memset(&effect, 0, sizeof(SDL_HapticEffect));
    effect.type = SDL_HAPTIC_SINE;
    effect.periodic.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
    effect.periodic.direction.dir[0] = 18000; // Force comes from south
    effect.periodic.period = 1000; // 1000 ms
    effect.periodic.magnitude = 20000; // 20000/32767 strength
    effect.periodic.length = 1000; // .1 seconds long
    effect.periodic.attack_length = 0; // Takes 0 seconds to get max strength
    effect.periodic.fade_length = 0; // Takes 0 seconds to fade away

    effect_id = SDL_HapticNewEffect(haptic, &effect);

    // Test blocks to shove around
    things.push_back(Entity());
    things.push_back(Entity());
    things.push_back(Entity());
    //below variables = renderer, pointer to ent, ent type, x pos, ypos
    Get_Ent_Specs(renderer, &things[0], LITTLE_MAN, 21, 20);
    Get_Ent_Specs(renderer, &things[1], BIG_MAN, 16, 16);
    Get_Ent_Specs(renderer, &things[2], BIG_MAN, 4, 20);
    if (&things[2] == NULL){
        printf("null pointer\n");
        exit(1);
    }


    oldtime = SDL_GetTicks();

    return true;
}
