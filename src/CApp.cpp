//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp() {
    renderer = NULL;
    haptic = NULL;
    joystick = NULL;

    Mainlocx = 200;
    Mainlocy = 200;

    Running = true;

    yvel = 0;
    xvel = 0;
    xcont = 0;

    targetx = 0;
    targety = 0;

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
