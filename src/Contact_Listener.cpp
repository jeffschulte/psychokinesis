#include "Contact_Listener.h"


void ContactListener::BeginContact(b2Contact* contact) {

    CopyPhysicsComponent* physA =
        (CopyPhysicsComponent*) contact->GetFixtureA()->GetUserData();
    CopyPhysicsComponent* physB =
        (CopyPhysicsComponent*) contact->GetFixtureB()->GetUserData();

    if(physA != NULL) {
        physA->floorContacts++;
    }
    if(physB != NULL) {
        physB->floorContacts++;
    }

    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    b2Vec2 velA = bodyA->GetLinearVelocity();
    b2Vec2 velB = bodyB->GetLinearVelocity();
    double speedA = velA.Length();
    double speedB = velB.Length();
    double massA = bodyA->GetMass();
    double massB = bodyB->GetMass();

    Entity* entA = (Entity*)bodyA->GetUserData();
    Entity* entB = (Entity*)bodyB->GetUserData();


    /// \todo Seriously figure out a clean way to do this

    if(entA != NULL && bodyA->IsFixedRotation() == false) {
        entA->removed = true;
    }
    if(entB != NULL && bodyB->IsFixedRotation() == false) {
        entB->removed = true;
    }

    if(entA != NULL && speedB*massB > 10.0) {
        entA->hit_pts -= .5*(speedB*massB);
        printf("%s A hit_pts = %g\n",entA->debugname.c_str(),entA->hit_pts);
        // if (velB.x > 0.0) {
        //     Entity::entities[i]->animation_object->hit_face_l = true;
        // }
        // else {
        //     Entity::entities[i]->animation_object->hit_face_r = true;
        // }
    }
    if(entB != NULL && speedA*massA > 10.0) {
        entB->hit_pts -= .5*(speedA*massA);
        printf("%s B hit_pts = %g\n\n",entB->debugname.c_str(),entB->hit_pts);

        // if (velA.x > 0.0) {
        //     Entity::entities[i]->animation_object->hit_face_l = true;
        // }
        // else {
        //     Entity::entities[i]->animation_object->hit_face_r = true;
        // }
    }


    /// \todo Check the enttype for different bullet effects
}


void ContactListener::EndContact(b2Contact* contact) {

    CopyPhysicsComponent* physA =
        (CopyPhysicsComponent*) contact->GetFixtureA()->GetUserData();
    CopyPhysicsComponent* physB =
        (CopyPhysicsComponent*) contact->GetFixtureB()->GetUserData();

    if(physA != NULL) {
        physA->floorContacts--;
    }
    if(physB != NULL) {
        physB->floorContacts--;
    }
}
