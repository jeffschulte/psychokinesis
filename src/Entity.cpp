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


void NullInputComponent::update(__attribute__((unused)) Entity& ent) {}
void NullPhysicsComponent::update(__attribute__((unused)) Entity& ent) {}
void NullRenderComponent::update(__attribute__((unused)) Entity& ent,
                                 __attribute__((unused)) Graphics& graphics) {}




// TODO: Put this somewhere less general than entity

// void Entity::Shoot(SDL_Renderer* renderer, double pr_xvel, double pr_yvel, bool dir_right) {
//     if (dir_right) {
//         Project::Create(renderer, proj_shoot_type, x + 1.1*width/2.0,
//                         y, 100+xvel, yvel);
//     }
//     else {
//         Project::Create(renderer, proj_shoot_type, x - 1.1*width/2.0,
//                         y, -100+xvel, yvel);
//     }
// }
