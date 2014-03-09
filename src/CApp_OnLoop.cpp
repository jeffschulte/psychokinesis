//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnLoop() {

    yvel -= 0.1;

    Mainlocy -= yvel;

    // If we are in contact with a surface, then apply normal force and friction

    if(Mainlocy > 405) {
        Mainlocy = 405;
        yvel = 0;

        xvel *= .8;
        Mainlocx += xcont;
    }
    else {
        Mainlocx += xvel;
    }

    if(Mainlocx < 50) {
        Mainlocx = 50;
        xvel *= -.8;
    }
    if(Mainlocx > 590-12) {
        Mainlocx = 590-12;
        xvel *= -.8;
    }

    if(Mainlocy < 50) {
        Mainlocy = 50;
        yvel = 0;
    }

}

//==============================================================================
