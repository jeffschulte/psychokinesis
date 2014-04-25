#include <stdio.h>
#include <sstream>
#include <string>
#include "Application.h"


bool Application::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    // Set up graphics

    SDL_Window *screen = SDL_CreateWindow("Psychokinesis",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          screenw, screenh,
                          SDL_WINDOW_OPENGL);
    if(screen == NULL) {
        Logger::log("SDL_CreateWindow failure");
        return false;
    }

    if((graphics.renderer = SDL_CreateRenderer(screen, -1, 0)) == NULL) {
        Logger::log("SDL_CreateRenderer failure");
        return false;
    }

    graphics.camera = new Camera();
    entities.push_back(new Entity(new CameraControl(graphics.camera),
                                  new NullPhysicsComponent(),
                                  new NullRenderComponent()));

    // Set up joystick controls

    std::stringstream ss;
    ss << SDL_NumJoysticks() << " joysticks were found";
    Logger::log(ss.str());

    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    // Set up rumble effects

    haptic = SDL_HapticOpen( 0 );
    if (haptic == NULL) {
        Logger::log("SDL_HapticOpen failure");
    }

    if (haptic != NULL && SDL_HapticRumbleInit( haptic ) != 0) {
        Logger::log("SDL_HapticRumbleInit failure: " +
                    std::string(SDL_GetError()));
        haptic = NULL;
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

    Create(Entity::LITTLE_MAN, 26, 25);
    Create(Entity::LITTLE_MAN, 21, 25);
    Create(Entity::BIG_MAN, 17, 25);
    Create(Entity::LITTLE_MAN, 26, 20);
    Create(Entity::LITTLE_MAN, 11, 20);
    Create(Entity::LITTLE_MAN, 7, 20);
    Create(Entity::LITTLE_MAN, 26, 35);
    Create(Entity::LITTLE_MAN, 21, 35);
    Create(Entity::BIG_MAN, 17, 35);
    Create(Entity::LITTLE_MAN, 26, 30);
    Create(Entity::LITTLE_MAN, 11, 30);
    Create(Entity::LITTLE_MAN, 7, 30);

    Project::Create(graphics.renderer, Project::BULLET, 20, 30, 20, 0);

    Logger::log("Creating player");

    Create(Entity::PLAYER, 4, 20);


    mainhud.Hud_Load_Hit_Pts_Texture("art_assets/hit_pts_meter.png",
                                     graphics.renderer,
                                     Player::player->hit_pts);


    if(level.LoadAssets(graphics.renderer, "art_assets/sky2.png",
                        "art_assets/grass.png") == NULL) {
        Logger::log("Level loading failure: " + std::string(SDL_GetError()));
    }

    Level::p_level->world.SetContactListener(&contactListen);

    oldtime = SDL_GetTicks();
    return true;
}
