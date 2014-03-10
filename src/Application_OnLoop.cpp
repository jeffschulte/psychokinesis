//==============================================================================
#include "Application.h"

//==============================================================================
void Application::OnLoop() {

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


    block.yvel -= 0.1;
    block.y -= block.yvel;
    block.x += block.xvel;

    if(block.y > screenh - block.height / 2 - 50) {
        block.y = screenh - block.height / 2 - 50;
        block.yvel *= -0.8;

        block.xvel -= 0.01 * block.xvel;
    }
    if(block.x < 50 + block.width / 2) {
        block.x = 50 + block.width / 2;
        block.xvel *= -.8;
    }
    if(block.x > screenw - block.width / 2 - 50) {
        block.x = screenw - block.width / 2 - 50;
        block.xvel *= -.8;
    }

    if(block.y < 50 + block.height / 2) {
        block.y = 50 + block.height / 2;
        block.yvel *= -.8;
    }
}

//==============================================================================
