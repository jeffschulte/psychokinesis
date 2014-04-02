#pragma once

#include <SDL.h>
#include <Box2D/Box2D.h>
#include "Entity.h"

class ContactListener : public b2ContactListener {
 public:
    void BeginContact(b2Contact* contact);
};
