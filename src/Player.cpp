#include "Player.h"


// Updates the position of the player based on the environment

void Player::calcMotion(int screenw, int screenh, double xcont,
                        Level level, int dt) {

    // For now, we'll just draw a circle from the CoM and see which
    // line it is closest to

    // TODO: Fix the below to take into account all lines somehow

    EnvLine* closest = level.ClosestLine(x, y);

    yvel -= 9.8 * dt / 1000.0;
    y += yvel * dt / 1000.0;
    x += xvel * dt / 1000.0;

    if(closest->DistToPoint(x, y) > height / 2) {

        // We are airborne at this point, and we only care about gravity


    }
    else {

        // Keep it a certain radial distace from the surface and set
        // that component of the velocity = 0

        // If we are horiz or vert, then we can apply in the usual fashion

        if(closest->y1 == closest->y2) {
            if(y < closest->y1) {
                y = closest->y1 - height / 2;

            }
            else {
                y = closest->y1 + height / 2;

                if(xvel < 15 && xvel > -15) {
                    xvel += 1000 * xcont * dt / 1000.0;
                }
            }

            yvel = 0;
            xvel *= 0.8;
        }

        else if(closest->x1 == closest->x2) {
            if(x < closest->x1) {
                x = closest->x1 - width / 2;
            }
            else {
                x = closest->x1 + width / 2;
            }

            xvel = 0;
            yvel *= 0.8;
        }

        else {

            yvel -= 9.8 * dt / 1000.0;

            // Rotate coordinate system so line is horizontal
            double lineangle = atan2(closest->y2 - closest->y1,
                                     closest->x2 - closest->x1);
            double xrot = x * cos(lineangle) + y * sin(lineangle);
            double yrot = -x * sin(lineangle) + y * cos(lineangle);

            double xvrot = xvel * cos(lineangle) + yvel * sin(lineangle);
            double yvrot = -xvel * sin(lineangle) + yvel * cos(lineangle);

            double x1rot = closest->x1 * cos(lineangle) + closest->y1 * sin(lineangle);
            double y1rot = -closest->x1 * sin(lineangle) + closest->y1 * cos(lineangle);

            double x2rot = closest->x2 * cos(lineangle) + closest->y2 * sin(lineangle);
            double y2rot = -closest->x2 * sin(lineangle) + closest->y2 * cos(lineangle);

            if(yrot < y1rot) {
                yrot = y1rot - height / 2;
            }
            else {
                yrot = y1rot + height / 2;

                if(xvrot < 1 && xvrot > -1) {
                    xvrot -= 0.5 * xcont;
                }
            }

            yvrot = 0;
            xvrot *= 0.8;

            x = xrot * cos(lineangle) - yrot * sin(lineangle);
            y = xrot * sin(lineangle) + yrot * cos(lineangle);

            xvel = xvrot * cos(lineangle) - yvrot * sin(lineangle);
            yvel = xvrot * sin(lineangle) + yvrot * cos(lineangle);
        }
    }

}
