//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnLoop() {

    player.yvel -= 0.1;

    player.y -= player.yvel;

    // If we are in contact with a surface, then apply normal force and friction

    if(player.y > screenh - player.height / 2 - 50) {
        player.y = screenh - player.height / 2 - 50;
        player.yvel = 0;

        player.xvel *= .8;
        player.x += xcont;
    }
    else {
        player.x += player.xvel;
    }

    if(player.x < 50 + player.width / 2) {
        player.x = 50 + player.width / 2;
        player.xvel *= -.8;
    }
    if(player.x > screenw - player.width / 2 - 50) {
        player.x = screenw - player.width / 2 - 50;
        player.xvel *= -.8;
    }

    if(player.y < 50 + player.height / 2) {
        player.y = 50 + player.height / 2;
        player.yvel = 0;
    }

}

//==============================================================================
