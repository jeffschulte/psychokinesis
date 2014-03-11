#include "Player.h"


// Updates the position of the player based on the environment

void Player::calcMotion(int screenw, int screenh, double xcont) {
    
    yvel -= 0.1;

    y -= yvel;

    // If we are in contact with a surface, then apply normal force and friction

    if(y > screenh - height / 2 - 50) {
        y = screenh - height / 2 - 50;
        yvel = 0;

        xvel *= .8;

        // The movement will give a constant accel up to a maximum speed

        if (xvel < 2 && xvel > -2)
        {
            xvel += xcont;
        }
    }

    x += xvel;


    if(x < 50 + width / 2) {
        x = 50 + width / 2;
        xvel = 0;
        yvel *= .8;
    }
    if(x > screenw - width / 2 - 50) {
        x = screenw - width / 2 - 50;
        yvel *= .8;
        xvel = 0;
    }

    if(y < 50 + height / 2) {
        y = 50 + height / 2;
        yvel = 0;
        xvel *= .8;
    }
}