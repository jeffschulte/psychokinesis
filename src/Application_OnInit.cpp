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


    if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096) < 0) {
        return false;
    }

    // Test blocks to shove around
    //below variables = renderer, entype, xpos, ypos
    Entity::Create(renderer, Entity::LITTLE_MAN, 21, 20);
    Entity::Create(renderer, Entity::BIG_MAN, 16, 16);
    Entity::Create(renderer, Entity::LITTLE_MAN, 9, 20);
    Entity::Create(renderer, Entity::PLAYER, 4, 20);

    //After all Entities are loaded:
    bool there_is_a_player = false;
    for (int i =0; i< Entity::entities.size(); i++){
        if (Entity::entities[i]->ent_type == Entity::PLAYER) {
            there_is_a_player = true;
        }
    }
    if (!there_is_a_player) {
        Logger::log("There is not player initialized!!!\n");
    }

    if(level.LoadAssets(renderer, "art_assets/sky2.png",
                        "art_assets/grass.png") == NULL) {
        Logger::log("Level loading failure: " + std::string(SDL_GetError()));
    }


    oldtime = SDL_GetTicks();
    return true;
}
