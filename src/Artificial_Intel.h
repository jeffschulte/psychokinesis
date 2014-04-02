#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "Logger.h"
#include "Entity.h"
#include "Level.h"

class AI {
 public:
    double xrun;
    double yrun;
    AI();
    void Calculate_Action(double x,double y);
};



/* class ActionState { */

/*  public: */
/*     double xcont; */
/*     bool pushing; */

/*     double targetx, targety; */
/*     static ActionState* p_astate; */

/*     ActionState(); */
/* }; */

