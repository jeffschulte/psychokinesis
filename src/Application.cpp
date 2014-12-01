#include "Application.h"


void Addbump (double bump_width, double bump_height,
              double* p_current_x, double* p_current_y, Level* level){
    level->AddLine(p_current_x, p_current_y, 0, bump_height);
    level->AddLine(p_current_x, p_current_y, bump_width, 0);
    level->AddLine(p_current_x, p_current_y, 0,-bump_height);
}

Application::Application() {
    haptic = NULL;
    joystick = NULL;

    Running = true;

    oldtime = SDL_GetTicks();
    render_rate = 50; //millisecends

    screenw = 1280;
    screenh = 720;

    // Set up the wall objects
    double current_x = 0;
    double current_y = -5;

    double wallwidth = 60;    // m
    double bump_x = wallwidth/2.0;
    double bump_width = wallwidth/10.0;
    double bump_height = wallwidth/10.0;
    double pit_x = 3.0*wallwidth/4.0;
    double pit_width = bump_width;
    double pit_height = wallwidth/2.0;
    level.AddLine(&current_x,&current_y, 20,1);
    level.AddLine(&current_x,&current_y, 20,5);
    level.AddLine(&current_x,&current_y, 20,0);
    level.AddLine(&current_x,&current_y, 20,0);
    Addbump(bump_width, bump_height, &current_x, &current_y, &level);
    level.AddLine(&current_x,&current_y, 20,0);
    Addbump(bump_width, bump_height, &current_x, &current_y, &level);
    level.AddLine(&current_x,&current_y, 20,0);
    level.AddLine(&current_x,&current_y, 0,35);
    level.AddLine(&current_x,&current_y, -current_x,0);
    level.AddLine(&current_x,&current_y, 0,-current_y);
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
