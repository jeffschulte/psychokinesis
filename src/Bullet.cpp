#include "Bullet.h"


Entity* Bullet::Create(b2World* worldc, Graphics& graphics, double x, double y,
                       double xvel, double yvel) {

    CopyPhysicsComponent* bulletPhys = new CopyPhysicsComponent(worldc);

    Entity* proj = new Entity(new NullInputComponent(), bulletPhys,
                      new StaticRenderComponent("art_assets/projectile.png",
                                                graphics));


    proj->width = .3;
    proj->height = .15;
    proj->mass = 100;
    proj->debugname = "bullet";
    proj->y = y;
    if (xvel > 0.0) {
        proj->x = x + proj->width/2.0;
    }
    else {
        proj->x = x - proj->width/2.0;
    }
    proj->xvel = xvel;
    proj->yvel = yvel;

    /// \todo Figure out a better solution to copy params over for
    /// initial b2Body, doing a manual update is awful

    proj->update(graphics);
    bulletPhys->getBody()->SetBullet(true);

    return proj;
}


void StaticRenderComponent::update(Entity& ent, Graphics& graphics) {

    Rect rectw = {ent.x - ent.width / 2, ent.y + ent.height / 2,
                  ent.width, ent.height};
    if (texture != NULL) {
        SDL_Rect rects =  {0,0,500,200};
        if (ent.xvel >= 0) {
            graphics.camera->RenderCopyEx(graphics.renderer, texture,
                                          &rects, &rectw,
                                          ent.angle, NULL, SDL_FLIP_NONE);
        }
        else {
            graphics.camera->RenderCopyEx(graphics.renderer, texture,
                                          &rects, &rectw,
                                          ent.angle, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
    else {
        SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255);
        graphics.camera->RenderFillRect(graphics.renderer, &rectw);
    }
}

StaticRenderComponent::StaticRenderComponent(const char* File,
                                             Graphics& graphics) {

    texture = IMG_LoadTexture(graphics.renderer, File);
    Logger::log("Loaded Projectile from " + std::string(File));
}

StaticRenderComponent::~StaticRenderComponent() {

    /// \todo Keep textures around so it doesn't have to be reloaded
    /// each time (static reference perhaps)

    SDL_DestroyTexture(texture);
}
