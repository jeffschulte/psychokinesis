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

    // TODO: Figure out a better solution to copy params over for
    // initial b2Body, doing a manual update is awful

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


/*

Project::Project() {
    texture = NULL;
};



Project* Project::Create(SDL_Renderer* renderer,
                         int type, double x, double y,
                         double xvel, double yvel) {


    switch (type) {
        case BULLET:
            proj->width = .3;
            proj->height = .15;
            proj->mass = 100;
            proj->debugname = "bullet";
            if((proj->texture =
                proj->LoadTexture("art_assets/projectile.png", renderer)) == NULL) {
                Logger::log("Problem loading texture in Project_Create");
            }
            break;
    }

    proj->proj_type = type;
    proj->y = y;
    if (xvel > 0.0) {
        proj->x = x + proj->width/2.0;
    }
    else {
        proj->x = x - proj->width/2.0;
    }
    proj->xvel = xvel;
    proj->yvel = yvel;
    //the following so there is a small amount of overlap between characters
    proj->anim_width = 1.7*(proj->width);
    proj->anim_height = 1.0*(proj->height);

    proj->stationary_count = 0;

    // Create its counterpart in the world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(proj->x, proj->y);
    bodyDef.linearVelocity.Set(proj->xvel, proj->yvel);
    bodyDef.bullet = true;
    bodyDef.fixedRotation = true;
    proj->body = Level::p_level->world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(proj->width / 2, proj->height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 50.0f;
    fixtureDef.friction = 3;

    proj->body->CreateFixture(&fixtureDef);

    projects.push_back(proj);
    return proj;
};


SDL_Texture* Project::LoadTexture(const char* File, SDL_Renderer* renderer) {
    SDL_Texture* texture;
    if((texture = IMG_LoadTexture(renderer, File)) == NULL) {
        return NULL;
    }

    Logger::log("Loaded Projectile from " + std::string(File));
    return texture;
}


void Project::OnRender(SDL_Renderer* renderer, Camera* camera) {

    Rect rect5 = {x - anim_width / 2, y + anim_height / 2, anim_width, anim_height};
    if (texture != NULL) {
        SDL_Rect rect =  {0,0,500,200};
        if (xvel >= 0) {
            camera->RenderCopyEx(renderer, texture, &rect, &rect5,
                                 angle, NULL, SDL_FLIP_NONE);
        }
        else {
            camera->RenderCopyEx(renderer, texture, &rect, &rect5,
                                 angle, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
    else {
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        camera->RenderFillRect(renderer, &rect5);
    }
}

void Project::Calculate_Motion(int dt) {
    if (stationary_count == 4) {
        return;
    }

    b2Vec2 position = body->GetPosition();
    b2Vec2 velocity = body->GetLinearVelocity();

    // if (fabs(velocity.x) < DBL_EPSILON && fabs(velocity.y) < DBL_EPSILON) {
    //     stationary_count++;
    // }
    // else {
    //     stationary_count = 0;
    // }
    // if (stationary_count > 2) {
    //     Level::p_level->world.DestroyBody(body);
    //     delete this;
    //     printf("count = %d\n");
    //     stationary_count = 4;
    //     return;
    // }

    x = position.x;
    y = position.y;

    angle = body->GetAngle() / -b2_pi * 180.0;
}

*/
