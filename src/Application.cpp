#include "Application.h"


Application::Application() {
    renderer = NULL;
    haptic = NULL;
    joystick = NULL;

    music = NULL;

    Running = true;

    oldtime = SDL_GetTicks();
    render_rate = 50; //millisecends

    screenw = 1280;
    screenh = 720;

    // Set up the wall objects

    double wallwidth = 60;    // m
    double bump_x = wallwidth/2.0;
    double bump_width = wallwidth/10.0;
    double bump_height = wallwidth/10.0;
    double pit_x = 3.0*wallwidth/4.0;
    double pit_width = bump_width;
    double pit_height = wallwidth/2.0;

    level.AddLine(0, 0, bump_x, 0);
    level.AddLine(bump_x, 0, bump_x, bump_height);
    level.AddLine(bump_x, bump_height, bump_x+bump_width, bump_height);
    level.AddLine(bump_x+bump_width, bump_height, bump_x+bump_width, 0);
    level.AddLine(bump_x+bump_height, 0, pit_x, 0);
    level.AddLine(pit_x, 0, pit_x, -pit_height);
    level.AddLine(pit_x, -pit_height, pit_x+pit_width, -pit_height);
    level.AddLine(pit_x+pit_width, -pit_height, pit_x+pit_width, 0);
    level.AddLine(pit_x+pit_width, 0, wallwidth, 0);
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


int main(__attribute__((unused)) int argc,
         __attribute__((unused)) char* argv[]) {

    Application app;
    return app.OnExecute();
}
