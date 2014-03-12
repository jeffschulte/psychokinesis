#include "Application.h"

Application::Application() {
    renderer = NULL;
    haptic = NULL;
    joystick = NULL;

    Running = true;

    oldtime = SDL_GetTicks();
    render_rate = 50; //millisecends

    xcont = 0;
    pushing = false;

    targetx = 0;
    targety = 0;

    screenw = 640;
    screenh = 480;

    // Set up the player object

    player.x = 200;
    player.y = 200;
    player.width = 26;
    player.height = 26;
    player.red = player.green = 0;
    player.blue = 255;
    player.debugname = "Player";

    // Set up the wall objects

    int wallwidth = 50;

    level.AddLine(wallwidth, wallwidth, screenw - wallwidth, wallwidth);
    level.AddLine(screenw - wallwidth, wallwidth, screenw - wallwidth, screenh - 2*wallwidth);
    level.AddLine(screenw - wallwidth, screenh - 2*wallwidth, wallwidth, screenh - wallwidth);
    level.AddLine(wallwidth, screenh - wallwidth, wallwidth, wallwidth);
}


int Application::OnExecute() {

    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
        if (SDL_GetTicks() - oldtime > render_rate) {
            OnLoop();
            OnRender();
        }
    }
    OnCleanup();

    return 0;
}


int main(int argc, char* argv[]) {

    Application app;
    return app.OnExecute();
}
