#include "Contact_Listener.h"


void ContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    b2Vec2 velA = bodyA->GetLinearVelocity();
    b2Vec2 velB = bodyB->GetLinearVelocity();
    double speedA = velA.Length();
    double speedB = velB.Length();
    double massA = bodyA->GetMass();
    double massB = bodyB->GetMass();
    //dont know how to get the entity when I have a pointer to the body:
    for (int i =0; i< Entity::entities.size(); i++){
        if (Entity::entities[i]->body == bodyA) {
        printf("speedA = %g and speedB = %g\n",speedA*massA,speedB*massB);
            if (speedB*massB > 10.0) {
                    Entity::entities[i]->hit_pts -= .5*(speedB*massB);
                    if (velB.x > 0.0) {
                        Entity::entities[i]->animation_object->hit_face_l = true;
                    }
                    else {
                        Entity::entities[i]->animation_object->hit_face_r = true;
                    }
                }
            //printf("num %d hit_pts = %g\n",i,Entity::entities[i]->hit_pts);
        }
        if (Entity::entities[i]->body == bodyB) {
            if (speedA*massA > 10.0) {
                    Entity::entities[i]->hit_pts -= .5*(speedA*massA);
                    if (velA.x > 0.0) {
                        Entity::entities[i]->animation_object->hit_face_l = true;
                    }
                    else {
                        Entity::entities[i]->animation_object->hit_face_r = true;
                    }
            //printf("num %d hit_pts = %g\n",i,Entity::entities[i]->hit_pts);
                }
        }
    }
};
