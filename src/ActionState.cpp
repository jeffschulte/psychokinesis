#include "ActionState.h"

ActionState* ActionState::p_astate;

ActionState::ActionState() {

    xcont = targetx = targety = 0;
    pushing = false;

    ActionState::p_astate = this;
}
