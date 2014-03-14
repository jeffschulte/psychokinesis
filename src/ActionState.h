#pragma once

#include <stdio.h>


class ActionState {

 public:
    double xcont;
    bool pushing;

    double targetx, targety;

    ActionState();
};
