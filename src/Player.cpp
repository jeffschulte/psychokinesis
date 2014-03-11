#include "Player.h"


// Updates the position of the player based on the environment

void Player::calcMotion(int screenw, int screenh, double xcont, Level level) {
    
    yvel -= 0.1;

    y -= yvel;

    // If we are in contact with a surface, then apply normal force and friction

    if(y > screenh - height / 2 - 50) {
        y = screenh - height / 2 - 50;
        yvel = 0;

        xvel *= .8;

        // The movement will give a constant accel up to a maximum speed

        if (xvel < 1 && xvel > -1)
        {
            xvel += 0.5 * xcont;
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


    // For now, we'll just draw a circle from the CoM and see which line it is closest to

    EnvLine* closest = level.ClosestLine(x, y);

    if(closest->DistToPoint(x, y) > height / 2) {

        // We are airborne at this point, and we only care about gravity

        // yvel -= 0.1;
        // y -= yvel;
        // x += xvel;
    }
    else {

        // We want to first constrain it to the surface
        // Keep it a certain radial distace from the surface and set that component
        // of the velocity = 0

        // Apply our friction component parallel to the surface

        // If we are attempting to walk, add a force if not going too fast

        // Apply gravity and pushing forces, and solve for the perpendicular accel


        //printf("Nearest to line %g, %g; %g, %g; %g\n", closest->x1, 
        //    closest->y1, closest->x2, closest->y2, closest->DistToPoint(x, y) );
    }
}