//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp() {
    renderer = NULL;
    haptic = NULL;
    joystick = NULL;

    Running = true;

    xcont = 0;

    targetx = 0;
    targety = 0;

    screenw = 640;
    screenh = 480;

    player.x = 200;
    player.y = 200;
    player.width = 12;
    player.height = 26;
}

//------------------------------------------------------------------------------
int CApp::OnExecute() {
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

//==============================================================================
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
