#include "Motion_Calc.h"

Motion_Calc::Motion_Calc(){
    x = y = xvel = yvel = 0;      // Velocity
    width = height = 0;      // Size of Entity
    mass = xforce = yforce =0;
}

void Motion_Calc::Calc_Motion(Entity* this_ent, int ent_type, int dt,
                              bool this_a_player) {

    EnvLine* closest  = Level::p_level->ClosestLine(x, y);
    double targetx = ActionState::p_astate->targetx;
    double targety = ActionState::p_astate->targety;
    // For now, we'll just draw a circle from the CoM and see which
    // line it is closest to

    // TODO: Fix the below to take into account all lines somehow

    // Apply gravity
    //printf("i = %d and xforce = %g and yforce= %g mass = %g\n",1,Entity::entities[1]->motion_object->xforce,
    //       Entity::entities[1]->motion_object->yforce,mass);

    yforce -= 9.8 * mass;

    // Apply pushing force

    double player_x=-10;
    double player_y=-10;
    if (this_a_player) {
        player_x = x;
        player_y = y;
        Camera::camera->x = player_x;
        Camera::camera->zoom = player_y > 22 ? 10 : -fabs(y) + 32;
        if(ActionState::p_astate->pushing) {
            xforce -= targetx * 2 * 9.8 * mass;
            yforce -= targety * 2 * 9.8 * mass;
        }
    }

    // if (!this_a_player) {
    //     if (this_ent->collideline(player_x,player_y,targetx,targety)) {
    //         xvel += 2 * 9.8 * targetx * dt / 1000.0;
    //         yvel += 2 * 9.8 * targety * dt / 1000.0;
    //     }
    // }

    //if(false) {
    if(closest->DistToPoint(x, y) < height / 2) {
        // We are airborne at this point, and we only care about gravity
        // Keep it a certain radial distace from the surface and set
        // that component of the velocity = 0

        // If we are horiz or vert, then we can apply in the usual fashion

        if(fabs(closest->y1 - closest->y2) < DBL_EPSILON) {
            double normal = -yforce;
            yvel = 0;

            if(y < closest->y1) {
                y = closest->y1 - height / 2;
                if(yforce > 0) {
                    yforce = 0;
                }
            }
            else {
                y = closest->y1 + height / 2;

                if(this_a_player) {
                    if(xvel < 15 && xvel > -15) {
                        xforce += 98 * mass * ActionState::p_astate->xcont;
                    }
                }

                if(yforce < 0) {
                    yforce = 0;
                }
            }

            xforce -= ((0.0 < xvel) - (xvel < 0.0)) *
                (fabs(normal) * 10.0);

        }

        else if(fabs(closest->x1 - closest->x2) < DBL_EPSILON) {

            double normal = -xforce;
            xvel  = 0;

            if(x < closest->x1) {
                x = closest->x1 - width / 2;

                if(xforce > 0) {
                    xforce = 0;
                }
            }
            else {
                x = closest->x1 + width / 2;

                if(xforce < 0) {
                    xforce = 0;
                }
            }

            yforce -= ((0.0 < yvel) - (yvel < 0.0)) *
                (fabs(normal) * 1.0);
        }

        else {

            // Rotate coordinate system so line is horizontal
            double lineangle = atan2(closest->y2 - closest->y1,
                                     closest->x2 - closest->x1);
            double xrot = x * cos(lineangle) + y * sin(lineangle);
            double yrot = -x * sin(lineangle) + y * cos(lineangle);

            double xvrot = xvel * cos(lineangle) + yvel * sin(lineangle);
            double yvrot = -xvel * sin(lineangle) + yvel * cos(lineangle);

            double xforcerot = xforce * cos(lineangle) + yforce * sin(lineangle);
            double yforcerot = -xforce * sin(lineangle) + yforce * cos(lineangle);

            //double x1rot = closest->x1 * cos(lineangle) + closest->y1 * sin(lineangle);
            double y1rot = -closest->x1 * sin(lineangle) + closest->y1 * cos(lineangle);

            //double x2rot = closest->x2 * cos(lineangle) + closest->y2 * sin(lineangle);
            //double y2rot = -closest->x2 * sin(lineangle) + closest->y2 * cos(lineangle);


            double normal = -yforcerot;
            yvrot = 0;

            if(yrot < y1rot) {
                yrot = y1rot - height / 2;

                if(yforcerot > 0) {
                    yforcerot = 0;
                }
            }
            else {
                yrot = y1rot + height / 2;

                if(xvrot < 15 && xvrot > -15) {
                    xforcerot += 98 * mass * ActionState::p_astate->xcont;
                }

                if(yforcerot < 0) {
                    yforcerot = 0;
                }
            }

            xforcerot -= ((0.0 < xvrot) - (xvrot < 0.0)) *
                (fabs(normal) * 1.0);

            if(fabs(xvrot) < dt / 1000.0) {
                xvrot = 0.0;
            }
            if(fabs(yvrot) < dt / 1000.0) {
                yvrot = 0.0;
            }


            x = xrot * cos(lineangle) - yrot * sin(lineangle);
            y = xrot * sin(lineangle) + yrot * cos(lineangle);

            xvel = xvrot * cos(lineangle) - yvrot * sin(lineangle);
            yvel = xvrot * sin(lineangle) + yvrot * cos(lineangle);

            xforce = xforcerot * cos(lineangle) - yforcerot * sin(lineangle);
            yforce = xforcerot * sin(lineangle) + yforcerot * cos(lineangle);
        }
    }

    //Final velocity and position adjustments
    xvel += xforce / mass * dt / 1000.0;
    yvel += yforce / mass * dt / 1000.0;

    if(fabs(xvel) < dt / 1000.0) {
        xvel = 0.0;
    }
    if(fabs(yvel) < dt / 1000.0) {
        yvel = 0.0;
    }
    y += yvel * dt / 1000.0;
    x += xvel * dt / 1000.0;

    // if(this_a_player) {
    //     printf("%d: %g, %g; %g, %g\n", dt, xvel, yvel, x, y);
    // }

    return;
}
