#include "Entity.h"


Entity::Entity(InputComponent* inputc, PhysicsComponent* physicsc,
       RenderComponent* renderc)
    : input(inputc), physics(physicsc), render(renderc) {}


void Entity::update(Graphics& graphics) {

    input->update(*this);
    physics->update(*this);
    render->update(*this, graphics);
}


// This class directly copies the values from the b2body calculation
// onto the local state of the object

CopyPhysicsComponent::CopyPhysicsComponent(b2World* worldc)
    : world(worldc) {

    body = NULL;
}

void CopyPhysicsComponent::update(Entity& ent) {

    if(body == NULL) {

        // Create its counterpart in the world

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(ent.x, ent.y);
        bodyDef.fixedRotation = true;
        bodyDef.userData = &ent;
        body = world->CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(ent.width / 2, ent.height / 2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 3;

        body->CreateFixture(&fixtureDef);
    }

    b2Vec2 position = body->GetPosition();
    b2Vec2 velocity = body->GetLinearVelocity();

    ent.x = position.x;
    ent.y = position.y;
    ent.angle = body->GetAngle() / -b2_pi * 180.0;
    ent.xvel = velocity.x;
    ent.yvel = velocity.y;

}

void CopyPhysicsComponent::ApplyForce(double x, double y) {

    if(body == NULL) {
        return;
    }

    body->ApplyForce(b2Vec2(x, y), body->GetWorldCenter(), true);
}

void NullInputComponent::update(Entity& ent) {}

/*
std::vector<Entity*> Entity::entities;

Entity::Entity() {
    texture = NULL;
    animation_object = new Animation();
    AI_object = new AI();
    this_a_player = false;
    hit_pts = 0;
    dead = false;
}

SDL_Texture* Entity::LoadTexture(const char* File, SDL_Renderer* renderer) {

    texture = animation_object->Animation_Load_Texture(File,renderer);
    return texture;
}

void Entity::Shoot(SDL_Renderer* renderer, double pr_xvel, double pr_yvel, bool dir_right) {
    if (dir_right) {
        Project::Create(renderer, proj_shoot_type, x + 1.1*width/2.0,
                        y, 100+xvel, yvel);
    }
    else {
        Project::Create(renderer, proj_shoot_type, x - 1.1*width/2.0,
                        y, -100+xvel, yvel);
    }
};


void Entity::Calculate_Motion(int dt) {

    double targetx = ActionState::p_astate->targetx;
    double targety = ActionState::p_astate->targety;

    b2Vec2 position = body->GetPosition();
    b2Vec2 velocity = body->GetLinearVelocity();

    x = position.x;
    y = position.y;
    angle = body->GetAngle() / -b2_pi * 180.0;
    xvel = velocity.x;
    yvel = velocity.y;

    EnvLine* closest = Level::p_level->ClosestLine(x, y);
    EnvLine* second_closest = Level::p_level->SecondClosestLine(x,y, closest);
    double tan_theta_closest;
    double tan_theta_second_closest;
    if (fabs(closest->x2 - closest->x1) < DBL_EPSILON) {
        tan_theta_closest = (closest->y2 - closest->y1)/DBL_EPSILON;
    }
    else {
        tan_theta_closest = (closest->y2 - closest->y1)
            /(closest->x2 - closest->x1);
    }
    if (fabs(second_closest->x2 - second_closest->x1) < DBL_EPSILON) {
        tan_theta_second_closest =
            (second_closest->y2 - second_closest->y1)/DBL_EPSILON;
    }
    else {
        tan_theta_second_closest =
            (second_closest->y2 - second_closest->y1)
            /(second_closest->x2 - second_closest->x1);
    }

    if (this->hit_pts < 0.0) {
        this->dead = true;
    }

    if (this_a_player) {
        if (!dead) {
            if (swing_right == true) {
                animation_object->anim_swing_r = true;
                swing_right = false;
            }
            if (swing_left == true) {
                animation_object->anim_swing_l = true;
                swing_left = false;
            }
            if (shoot_right == true) {
                animation_object->anim_shoot_r = true;
                shoot_right = false;
            }
            if (shoot_left == true) {
                animation_object->anim_shoot_l = true;
                shoot_left = false;
            }
            if(ActionState::p_astate->pushing) {
                body->ApplyForce(b2Vec2(-targetx * 2 * 9.8 * 3,
                                        -targety * 2 * 9.8 * 3),
                                 body->GetWorldCenter(), true);
            }
            if (closest->DistToPoint(x,y).dist_to_pt < height
                && (fabs(tan_theta_closest) < .3 || fabs(tan_theta_second_closest) < .3)) {
                if(fabs(xvel) < 15) {
                    body->ApplyForce(b2Vec2(ActionState::p_astate->xcont * 100, 0),
                                     body->GetWorldCenter(), true);
                }
                else if ( (ActionState::p_astate->xcont > 0.0 && xvel < 0.0) ||
                          (ActionState::p_astate->xcont < 0.0 && xvel > 0.0) ) {
                    body->ApplyForce(b2Vec2(ActionState::p_astate->xcont * 100, 0),
                                     body->GetWorldCenter(), true);
                }
            }
            Camera::camera->x = x;
            Camera::camera->zoom = y > 22 ? 10 : -fabs(y) + 32;
        }
    }
    else {
        if (!dead) {
            if (fabs(Player::player->x - x)
                < 1.2*(width/2.0 + Player::player->width/2.0)
                && fabs(Player::player->y - y) < height) {
                if (Player::player->swing_right
                    && (Player::player->x - x) < 0.0) {
                    animation_object->hit_face_l = true;
                    hit_pts -= 50;
                }
                else if (Player::player->swing_left
                         && (Player::player->x - x) > 0.0) {
                    animation_object->hit_face_r = true;
                    hit_pts -= 50;
                }
            }
            AI_object->Calculate_Action(x,y);
            if (closest->DistToPoint(x,y).dist_to_pt < height
                && (fabs(tan_theta_closest) < .3 || fabs(tan_theta_second_closest) < .3)) {
                if(fabs(xvel) < 15) {
                    body->ApplyForce(b2Vec2(AI_object->xrun * 100, 0),
                                     body->GetWorldCenter(), true);
                }
                else if ( (AI_object->xrun > 0.0 && xvel < 0.0) ||
                          (AI_object->xrun < 0.0 && xvel > 0.0) ) {
                    body->ApplyForce(b2Vec2(AI_object->xrun * 100, 0),
                                     body->GetWorldCenter(), true);
                }
                // if(fabs(yvel) < 15) {
                //     body->ApplyForce(b2Vec2(0,AI_object->yrun * 100),
                //                      body->GetWorldCenter(), true);
                // }
            }
        }
        if(ActionState::p_astate->pushing) {
            if(collideline(Player::player->x, Player::player->y,
                           targetx, targety)) {
                body->ApplyForce(b2Vec2(targetx * 2 * 9.8 * 10,
                                        targety * 2 * 9.8 * 10),
                                 body->GetWorldCenter(), true);
            }
        }
    }
}

// Method to check if the rectangle collides with a given line segment

bool Entity::collideline(double xp, double yp, double targetx, double targety) {

    double m = targety / targetx;
    double b = yp - m * xp;

    // Equation for the line is given in y = mx + b form
    // First check the vertical, and see if it is in bounds

    double vertcoor = m * (x - width / 2) + b;

    if(vertcoor >= y - height / 2 && vertcoor <= y + height / 2) {
        if((vertcoor > yp && targety > 0) || (vertcoor < yp && targety < 0) ) {
            return true;
        }
    }

    vertcoor = m * (x + width / 2) + b;

    if(vertcoor >= y - height / 2 && vertcoor <= y + height / 2) {
        if((vertcoor > yp && targety > 0) || (vertcoor < yp && targety < 0) ) {
            return true;
        }
    }

    // Next see if it goes through the top or bottom

    double horicoor = (y - height / 2 - b) / m;

    if(horicoor >= x - width / 2 && horicoor <= x + width / 2) {
        if((horicoor > xp && targetx > 0) || (horicoor < xp && targetx < 0) ) {
            return true;
        }
    }

    horicoor = (y + height / 2 - b) / m;

    if(horicoor >= x - width / 2 && horicoor <= x + width / 2) {
        if((horicoor > xp && targetx > 0) || (horicoor < xp && targetx < 0) ) {
            return true;
        }
    }

    // None of these, then we missed

    return false;
}
*/
