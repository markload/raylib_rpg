#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/player.h"
#include "include/animation.h"


static void Update(void *pl) {
    Player *self = (Player*)pl;
}

static void Draw(void *pl) {
    Player *self = (Player*)pl;
}

static void DeInit(void *pl) {
    Player *self = (Player*)pl;
}


Player* NewPlayer(Texture2D sprite, Rectangle src, Rectangle dest, int anim_max_frame, float anim_speed) {
    Player *pl = (Player*)malloc(sizeof(Player));
    if (pl != NULL) {
        // Methods
        pl->sprite = sprite;
        pl->src = src;
        pl->dest = dest;

        pl->speed = 1.0f;
        pl->moving = false;

        pl->anim = NewAnimation(anim_max_frame, anim_speed);
        pl->type_anim = IDLE;

        // Functions
        pl->Update = Update;
        pl->Draw = Draw;
        pl->DeInit = DeInit;

        return pl;
    }

    return NULL;
}

void DelPlayer(Player *pl, Animation *anim) {
    DelAnimation(anim);

    UnloadTexture(pl->sprite);
    free(pl);
}
