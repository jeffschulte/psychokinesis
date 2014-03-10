#include "Application.h"

Application::Application() {
    renderer = NULL;
    haptic = NULL;
    joystick = NULL;

    Running = true;

    xcont = 0;

    targetx = 0;
    targety = 0;

    screenw = 640;
    screenh = 480;

    // Set up the player object

    player.x = 200;
    player.y = 200;
    player.width = 12;
    player.height = 26;
    player.red = player.green = 0;
    player.blue = 255;
    player.debugname = "Player";

    // Set up the wall objects

    int wallwidth = 50;

    wallleft.y = wallright.y = screenh / 2;
    wallleft.x = walltop.y = wallwidth / 2;
    wallright.x = screenw - wallwidth / 2;

    walltop.x = wallbottom.x = screenw / 2;
    wallbottom.y = screenh - wallwidth / 2;

    wallleft.width = wallright.width = wallwidth;
    wallleft.height = wallright.height = screenh;

    walltop.width = wallbottom.width = screenw;
    walltop.height = wallbottom.height = wallwidth;

    walltop.red = wallleft.red = wallright.red = wallbottom.red =
        walltop.blue = wallbottom.blue = wallright.blue = wallleft.blue = 0;

    walltop.green = wallleft.green = wallright.green = wallbottom.green = 128;

    walltop.debugname = "WallTop";
    wallleft.debugname = "WallLeft";
    wallright.debugname = "WallRight";
    wallbottom.debugname = "WallBottom";


    // Test block to shove around

    block.x = 400;
    block.y = 300;
    block.width = 20;
    block.height = 20;
    block.red = 255;
    block.green = block.blue = 0;
    block.debugname = "Block";
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

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}


int main(int argc, char* argv[]) {

    Application app;
    return app.OnExecute();
}
