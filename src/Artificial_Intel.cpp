#include "Artificial_Intel.h"


AI::AI() {
    xrun = 0;
}

void AI::Calculate_Action(double x, double y) {
    double dx = Player::player->x - x;
    double dy = Player::player->y - y;
    xrun = (dx > 0) ? .5 : -.5;
    yrun = (dy > 0) ? .5 : -.5;
}
