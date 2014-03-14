#include "Application.h"


void Application::OnLoop() {

    if(astate.pushing) {

        player.yvel -= 2 * 9.8 * astate.targety * dt / 1000.0;
        player.xvel -= 2 * 9.8 * astate.targetx * dt / 1000.0;

        for (int i=0;i<things.size();i++) {
            if(things[i].collideline(player.x, player.y,
                                     astate.targetx, astate.targety)) {
                things[i].xvel += 2 * 9.8 * astate.targetx * dt / 1000.0;
                things[i].yvel += 2 * 9.8 * astate.targety * dt / 1000.0;
            }
        }
        //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0) {
        //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
        //}
    }

    player.calcMotion(screenw, screenh, astate.xcont, level, dt);
    camera.x = player.x;
    camera.y = player.y;

    // TODO: The code below also needs to be generalized
    for (int i=0;i<things.size();i++) {
        things[i].yvel -= 9.8 * dt / 1000.0;
        things[i].y += things[i].yvel * dt / 1000.0;
        things[i].x += things[i].xvel * dt / 1000.0;

        if(things[i].y > 25 - things[i].height / 2) {
            things[i].y = 25 - things[i].height / 2;
            things[i].yvel *= -0.8;

            things[i].xvel -= 0.01 * things[i].xvel;
        }
        if(things[i].x < things[i].width / 2) {
            things[i].x = things[i].width / 2;
            things[i].xvel *= -.8;
        }
        if(things[i].x > 25 - things[i].width / 2) {
            things[i].x = 25 - things[i].width / 2;
            things[i].xvel *= -.8;
        }
        if(things[i].y < things[i].height / 2) {
            things[i].y = things[i].height / 2;
            things[i].yvel *= -.8;
        }
    }
}
