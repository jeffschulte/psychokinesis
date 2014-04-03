#include "Player.h"


Entity* Player::player;

Player::Player() {

    //player = this;
}

Entity* Player::Create(SDL_Renderer* renderer,
                       double x, double y) {
    if(player == NULL) {
        player = Entity::Create(renderer, Entity::PLAYER, x, y);
        return player;
    }
    else {
        return NULL;
    }
}
