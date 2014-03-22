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

    xforce = 0;
    yforce = 0;

    yforce -= 9.8 * mass;

    double player_x=-10;
    double player_y=-10;
    if (this_a_player) {
        player_x = x;
        player_y = y;
        Camera::camera->x = player_x;
        Camera::camera->zoom = player_y > 22 ? 10 : -fabs(y) + 32;
    }
    else {
        for (int i =0; i< Entity::entities.size(); i++){
            if (Entity::entities[i]->ent_type == Entity::PLAYER) {
                player_x = Entity::entities[i]->motion_object->x;
                player_y = Entity::entities[i]->motion_object->y;
            }
        }
    }

    if (this_a_player) {
        if(ActionState::p_astate->pushing) {
            xforce -= targetx * 2 * 9.8 * mass;
            yforce -= targety * 2 * 9.8 * mass;
        }
    }

    else {
        if (this_ent->collideline(player_x,player_y,targetx,targety)) {
            xforce += targetx * 2 * 9.8 * mass;
            yforce += targety * 2 * 9.8 * mass;
        }
    }

    if(closest->DistToPoint(x, y) < height / 2) {
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
                    if (xvel < -15) {
                        if (ActionState::p_astate->xcont > 0) {
                            xforce += 2.0*98 * mass * ActionState::p_astate->xcont;
                        }
                    }
                    else if (xvel > 15) {
                        if (ActionState::p_astate->xcont < 0) {
                            xforce += 2.0*98 * mass * ActionState::p_astate->xcont;
                        }
                    }
                    else {
                        xforce += 2.0*98 * mass * ActionState::p_astate->xcont;
                    }
                }
                if(yforce < 0) {
                    yforce = 0;
                }
            }
            //friction
            double friction_force  = ((0.0 > xvel) - (xvel > 0.0))
                *fabs(normal)*10.0;
            if (fabs(friction_force) > fabs(xvel)*mass/dt*1000.0) {
                friction_force = -xvel*mass/dt*1000.0; //should set vel to zero
            }
            xforce += friction_force;
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

            double friction_force  = ((0.0 > yvel) - (yvel > 0.0))
                *fabs(normal)*10.0;
            if (fabs(friction_force) > fabs(yvel)*mass/dt*1000.0) {
                friction_force = -yvel*mass/dt*1000.0; //should set vel to zero
            }
            xforce += friction_force;
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
                if(this_a_player) {
                     if (xvrot < -15) {
                         if (ActionState::p_astate->xcont > 0) {
                            xforcerot += 2.0*98 * mass * ActionState::p_astate->xcont;
                        }
                    }
                    else if (xvrot > 15) {
                        if (ActionState::p_astate->xcont < 0) {
                            xforcerot += 2.0*98 * mass * ActionState::p_astate->xcont;
                        }
                    }
                    else {
                        xforcerot += 2.0*98 * mass * ActionState::p_astate->xcont;
                    }
                }
                if(yforcerot < 0) {
                    yforcerot = 0;
                }
            }

            double friction_force  = ((0.0 > xvrot) - (xvrot > 0.0))
                *fabs(normal)*10.0;
            if (fabs(friction_force) > fabs(xvrot)*mass/dt*1000.0) {
                friction_force = -xvrot*mass/dt*1000.0; //should set vel to zero
            }
            xforcerot += friction_force;

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
    //Starting collisions
    //printf("net\n");

    //as written, this will only have one of the two colliders bounce off,
    //need to bounce both off
    if(false) {
    for (int i=0;i<Entity::entities.size();i++) {
        if (!(this_ent == Entity::entities[i])) {
            double x_other = Entity::entities[i]->motion_object->x;
            double y_other = Entity::entities[i]->motion_object->y;
            double width_other = Entity::entities[i]->motion_object->width;
            double height_other = Entity::entities[i]->motion_object->height;
            if (abs(x - x_other) < width + width_other
                && abs(y-y_other) < height + height_other) {
                printf("collision!  Between %d and %d at x,y %g,%g and x,y %g,%g\n",
                       ent_type, Entity::entities[i]->ent_type,x,y,x_other,y_other);
                double xa = x;
                double xb = x_other;
                double ya = y;
                double yb = y_other;
                double mb = Entity::entities[i]->motion_object->mass;
                double Ia = 2*mass*(width + height)/2/5;
                double Ib = 2*mb*(width_other + height_other)/2/5;
                if (x - x_other > 0 && x - x_other < width + width_other) {
                    x += 1.1*((width + width_other)/2.0 - (x - x_other));
                    xa = -width/2.0;
                    xb = width_other/2.0;
                }
                else if (x - x_other < 0 && x_other - x < width + width_other) {
                    x -= 1.1*((width + width_other)/2.0 - (x_other - x));
                    xa = width/2.0;
                    xb = -width_other/2.0;
                }
                if (y - y_other > 0 && y - y_other < height + height_other){
                    y += 1.1*((height + height_other)/2.0 - (y - y_other));
                    ya = -height/2.0;
                    yb = height_other/2.0;
                    }
                else if (y - y_other < 0 && y_other - y < height + height_other){
                    y -= 1.1*((height + height_other)/2.0 - (y_other - y));
                    ya = height/2.0;
                    ya = -height_other/2.0;
                }
                double e = .1;
                double k = 1/(mass*mass)+ 2/(mass*mb) +1/(mb*mb)
                                       - xa*xa/(mass*Ia) - xb*xb/(mass*Ib)
                                       - ya*ya/(mass*Ia) - ya*ya/(mb*Ia)
                                       - xa*xa/(mb*Ia) - xb*xb/(mb*Ib)
                                       - yb*yb/(mass*Ib) - yb*yb/(mb*Ib)
                                       + ya*ya*xb*xb/(Ia*Ib) + xa*xa*yb*yb/(Ia*Ib)
                                       - 2*xa*ya*xb*yb/(Ia*Ib);
                double xvelb = Entity::entities[i]->motion_object->xvel;
                double yvelb = Entity::entities[i]->motion_object->yvel;
                double Jx = (e+1)/k * (xvel - xvelb)*
                                       ( 1/mass - xa*xa/Ia + 1/mb - xb*xb/Ib)
                                       - (e+1)/k * (yvel - yvelb)*
                                       (xa*ya / Ia + xb*yb / Ib);

                double Jy = - (e+1)/k * (xvel - xvelb)*
                    (xa*ya / Ia + xb*yb / Ib)
                    + (e+1)/k  * (yvel - yvelb)*
                    ( 1/mass - ya*ya/Ia + 1/mb - yb*yb/Ib);

                xvel = xvel - .01*Jx/mass;
                yvel = yvel - .01*Jy/mass;
                xvelb = xvelb - Jx/mb;
                yvelb = yvelb - Jy/mb;
                //the following lines will give the angular momentum.
                //Should try to incorporate this too, otherwise all
                //special moment of inertia stuff above is useless
                // waf.x = wai.x - (Jx*ra.y - Jy*ra.x) /Ia;
                // waf.y = wai.y - (Jx*ra.y - Jy*ra.x) /Ia;
                // wbf.x = wbi.x - (Jx*rb.y - Jy*rb.x) /Ib;
                // wbf.y = wbi.y - (Jx*rb.y - Jy*rb.x) /Ib;
            }
        }
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


    return;
}



    // if(this_a_player) {
    //     printf("%d: %g, %g; %g, %g\n", dt, xvel, yvel, x, y);
    // }


   /**
       This function calulates the velocities after a 2D collision vaf, vbf,
       waf and wbf from information about the colliding bodies
       @param double e coefficient of restitution which depends on the nature
       of the two colliding materials
       @param double ma total mass of body a
       @param double mb total mass of body b
       @param double Ia inertia for body a.
       @param double Ib inertia for body b.
       @param vector ra position of collision point relative to centre of mass
       of body a in absolute coordinates (if this is
       known in local body coordinates it must be converted before this is called).
       @param vector rb position of collision point relative to centre of mass
       of body b in absolute coordinates (if this is
       known in local body coordinates it must be converted before this is called).
       @param vector n normal to collision point, the line along which the
       impulse acts.
       @param vector vai initial velocity of centre of mass on object a
       @param vector vbi initial velocity of centre of mass on object b
       @param vector wai initial angular velocity of object a
       @param vector wbi initial angular velocity of object b
       @param vector vaf final velocity of centre of mass on object a
       @param vector vbf final velocity of centre of mass on object a
       @param vector waf final angular velocity of object a
       @param vector wbf final angular velocity of object b
    */
    //     double k=1/(ma*ma)+ 2/(ma*mb) +1/(mb*mb) - ra.x*ra.x/(ma*Ia) - rb.x*rb.x/(ma*Ib)  - ra.y*ra.y/(ma*Ia)
    //         - ra.y*ra.y/(mb*Ia) - ra.x*ra.x/(mb*Ia) - rb.x*rb.x/(mb*Ib) - rb.y*rb.y/(ma*Ib)
    //         - rb.y*rb.y/(mb*Ib) + ra.y*ra.y*rb.x*rb.x/(Ia*Ib) + ra.x*ra.x*rb.y*rb.y/(Ia*Ib) - 2*ra.x*ra.y*rb.x*rb.y/(Ia*Ib);
    //     Vaf.x = Vai.x - Jx/Ma;
    //     Vaf.y = Vai.y - Jy/Ma;
    //     Vbf.x = Vbi.x - Jx/Mb;
    //     Vbf.y = Vbi.y - Jy/Mb;
    //     waf.x = wai.x - (Jx*ra.y - Jy*ra.x) /Ia;
    //     waf.y = wai.y - (Jx*ra.y - Jy*ra.x) /Ia;
    //     wbf.x = wbi.x - (Jx*rb.y - Jy*rb.x) /Ib;
    //     wbf.y = wbi.y - (Jx*rb.y - Jy*rb.x) /Ib;
    // }
