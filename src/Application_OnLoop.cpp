#include "Application.h"


void Application::OnLoop() {
    dt = SDL_GetTicks() - oldtime;
    oldtime = SDL_GetTicks();

    if(pushing) {

        player.yvel -= 2 * 9.8 * targety * dt / 1000.0;
        player.xvel -= 2 * 9.8 * targetx * dt / 1000.0;

        if(block.collideline(player.x, player.y, targetx, targety)) {
            block.xvel += 2 * 9.8 * targetx * dt / 1000.0;
            block.yvel += 2 * 9.8 * targety * dt / 1000.0;
        }
        //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0) {
        //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
        //}
    }

    player.calcMotion(screenw, screenh, xcont, level, dt);

    // TODO: The code below also needs to be generalized

    block.yvel -= 9.8 * dt / 1000.0;
    block.y += block.yvel * dt / 1000.0;
    block.x += block.xvel * dt / 1000.0;

    if(block.y > 25 - block.height / 2) {
        block.y = 25 - block.height / 2;
        block.yvel *= -0.8;

        block.xvel -= 0.01 * block.xvel;
    }
    if(block.x < block.width / 2) {
        block.x = block.width / 2;
        block.xvel *= -.8;
    }
    if(block.x > 25 - block.width / 2) {
        block.x = 25 - block.width / 2;
        block.xvel *= -.8;
    }

    if(block.y < block.height / 2) {
        block.y = block.height / 2;
        block.yvel *= -.8;
    }
}
