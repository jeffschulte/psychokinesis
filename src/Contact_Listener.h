#pragma once

#include <SDL.h>
#include <Box2D/Box2D.h>
#include "Entity.h"

class ContactListener : public b2ContactListener {
 public:
    void BeginContact(b2Contact* contact)
    {
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();
        double speedA = bodyA->GetLinearVelocity().Length();
        double massA = bodyA->GetMass();
        double speedB = bodyB->GetLinearVelocity().Length();
        double massB = bodyB->GetMass();
        //dont know how to get the entity when I have a pointer to the body:
        for (int i =0; i< Entity::entities.size(); i++){
            if (Entity::entities[i]->body == bodyA) {
                Entity::entities[i]->hit_pts -= .5*(speedB*massB);
                //printf("num %d hit_pts = %g\n",i,Entity::entities[i]->hit_pts);
            }
            if (Entity::entities[i]->body == bodyB) {
                Entity::entities[i]->hit_pts -= .5*(speedA*massA);
                //printf("num %d hit_pts = %g\n",i,Entity::entities[i]->hit_pts);
            }
        }
    }
};
