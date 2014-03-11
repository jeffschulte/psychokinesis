#include "Player.h"


// Updates the position of the player based on the environment

void Player::calcMotion(int screenw, int screenh, double xcont, Level level) {

    // For now, we'll just draw a circle from the CoM and see which line it is closest to

    EnvLine* closest = level.ClosestLine(x, y);

    yvel -= 0.1;
    y -= yvel;
    x += xvel;

    if(closest->DistToPoint(x, y) > height / 2) {

        // We are airborne at this point, and we only care about gravity


    }
    else {

        // We want to first constrain it to the surface
        // Keep it a certain radial distace from the surface and set that component
        // of the velocity = 0

        // If we are horiz or vert, then we can apply in the usual fashion

        if(closest->y1 == closest->y2) {
            if(y < closest->y1) {
                y = closest->y1 - height / 2;

                if(xvel < 1 && xvel > -1) {
                    xvel += 0.5 * xcont;
                }
            }
            else {
                y = closest->y1 + height / 2;
            }

            yvel = 0;
            xvel *= 0.8;
        }

        if(closest->x1 == closest->x2) {
            if(x < closest->x1) {
                x = closest->x1 - width / 2;
            }
            else {
                x = closest->x1 + width / 2;
            }

            xvel = 0;
            yvel *= 0.8;
        }


        // Apply our friction component parallel to the surface

        // If we are attempting to walk, add a force if not going too fast

        // Apply gravity and pushing forces, and solve for the perpendicular accel


        //printf("Nearest to line %g, %g; %g, %g; %g\n", closest->x1, 
        //    closest->y1, closest->x2, closest->y2, closest->DistToPoint(x, y) );
    }
}
