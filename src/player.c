#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/player.h"
#include "../include/animation.h"



// Private functions ----------------------------------------
static void Input(void *pl) {
    Player *self = (Player*)pl;
    self->moving = false;
    if (IsKeyDown(KEY_RIGHT)) {
        self->dest.x += self->speed;
        self->type_anim = RIGHT;
        self->moving = true;
    } else if (IsKeyDown(KEY_LEFT)) {
        self->dest.x -= self->speed;
        self->type_anim = LEFT;
        self->moving = true;
    } else if (IsKeyDown(KEY_DOWN)) {
        self->dest.y += self->speed;
        self->type_anim = DOWN;
        self->moving = true;
    } else if (IsKeyDown(KEY_UP)) {
        self->dest.y -= self->speed;
        self->type_anim = UP;
        self->moving = true;
    }
}

// Public functions ----------------------------------------
static void Update(void *pl) {
    Player *self = (Player*)pl;
    Input(pl);
    if (self->moving) {
        self->anim->Update(self->anim);

        self->src = (Rectangle){
            self->anim->current * self->tilesize,
            self->type_anim * self->tilesize,
            self->tilesize, self->tilesize
        };
    } else
        self->src.x = 0;
}

static void Draw(void *pl) {
    Player *self = (Player*)pl;
    DrawTexturePro(self->sprite, self->src, self->dest, (Vector2){0, 0}, 0.0f, RAYWHITE);
}

Player* NewPlayer(int tilesize,
                  Texture2D sprite,
                  int anim_min_frame,
                  int anim_max_frame,
                  float anim_speed) {

    Player *pl = (Player*)malloc(sizeof(Player));
    if (pl != NULL) {
        // Methods
        pl->tilesize = tilesize;
        pl->sprite = sprite;
        pl->src = (Rectangle){0, 0, tilesize, tilesize};
        pl->dest = (Rectangle){10, 10, tilesize, tilesize};

        pl->speed = 1.0f;
        pl->moving = false;

        pl->anim = NewAnimation(anim_min_frame, anim_max_frame, anim_speed);

        // Functions
        pl->Update = Update;
        pl->Draw = Draw;

        return pl;
    }

    free(pl);
    return NULL;
}

void DelPlayer(Player *pl) {
    DelAnimation(pl->anim);

    UnloadTexture(pl->sprite);
    free(pl);
}
