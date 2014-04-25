#include "Application.h"

Entity* Application::Create(Graphics& graphics,
                            Entity::EntType type, double x, double y) {

    Entity* ent;

    if(type == Entity::PLAYER) {
        Animation* playerAnim = new Animation("art_assets/stickman6sword.png",
                                   graphics.renderer);
        CopyPhysicsComponent* playerPhys =
            new CopyPhysicsComponent(&Level::p_level->world);
        astate = new ActionState(playerAnim, playerPhys);
        ent = new Entity(astate,
                         playerPhys,
                         playerAnim);
    }
    else {
        CopyPhysicsComponent* entPhys =
            new CopyPhysicsComponent(&Level::p_level->world);
        ent = new Entity(new AI(entPhys),
                         entPhys,
                         new Animation("art_assets/stickman6sword.png",
                                       graphics.renderer));
    }

    switch (type) {
    case Entity::BIG_MAN:
            ent->width = 1.5;
            ent->height = 2.0;
            ent->mass = 100;
            ent->hit_pts = 200;
            ent->proj_shoot_type=0;
            ent->debugname = "big_man";
            break;
    case Entity::LITTLE_MAN:
            ent->width = 1.0;
            ent->height = 1.5;
            ent->mass = 90;
            ent->hit_pts = 200;
            ent->proj_shoot_type=0;
            ent->debugname = "little_man";
            break;
    case Entity::PLAYER:
            ent->width = 1.0;
            ent->height = 1.5;
            ent->mass = 90;
            ent->hit_pts = 500;
            ent->proj_shoot_type=0;
            ent->debugname = "player";
            ent->this_a_player = true;
            break;
    }

    ent->ent_type = type;
    ent->x = x;
    ent->y = y;
    ent->swing_right = false;
    ent->swing_left = false;
    ent->shoot_right = false;
    ent->shoot_left = false;
    //the following so there is a small amount of overlap between characters
    ent->anim_width = 1.7*(ent->width);
    ent->anim_height = 1.0*(ent->height);

    entities.push_back(ent);

    return ent;
}
