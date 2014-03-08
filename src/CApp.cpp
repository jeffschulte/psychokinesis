//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp() {
    renderer = NULL;
    haptic = NULL;

    Mainlocx = 200;
    Mainlocy = 200;

    Running = true;

    movingright = false;
    movingleft = false;

    yvel = 0;
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
