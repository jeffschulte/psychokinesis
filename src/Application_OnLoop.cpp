#include "Application.h"


void Application::OnLoop() {

    player.calcMotion(screenw, screenh, xcont);

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
