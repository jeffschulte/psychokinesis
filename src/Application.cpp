#include "Application.h"


Application::Application() {
    renderer = NULL;
    haptic = NULL;
    joystick = NULL;

    Running = true;

    oldtime = SDL_GetTicks();
    render_rate = 50; //millisecends

    screenw = 640;
    screenh = 480;

    // Set up the player object

    player.x = 12;       // m
    player.y = 12;       // m
    player.width = 1.5;   // m
    player.height = 1.5;  // m
    player.red = player.green = 0;
    player.blue = 255;
    player.debugname = "Player";

    // Set up the wall objects

    double wallwidth = 25;    // m

    //level.AddLine(wallwidth, wallwidth, screenw - wallwidth, wallwidth);
    //level.AddLine(screenw - wallwidth, wallwidth, screenw - wallwidth, screenh - 2*wallwidth);
    //level.AddLine(screenw - wallwidth, screenh - 2*wallwidth, wallwidth, screenh - wallwidth);
    //level.AddLine(wallwidth, screenh - wallwidth, wallwidth, wallwidth);

    level.AddLine(0, 0, wallwidth, 0);
    level.AddLine(wallwidth, 0, wallwidth, wallwidth);
    level.AddLine(wallwidth, wallwidth, 0, wallwidth);
    level.AddLine(0, wallwidth, 0, 0);

    frametime = 20;        // ms
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
        dt = SDL_GetTicks() - oldtime;
        if(dt > frametime) {
            oldtime = SDL_GetTicks();
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
