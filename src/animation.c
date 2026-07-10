#include <raylib.h>
#include <stdlib.h>

#include "../include/animation.h"


static void Update(void *anim) {
    Animation *self = (Animation*)anim;
    self->timer += GetFrameTime();
    if (self->timer >= self->speed) {
        self->timer = 0.0f;
        self->frame++;
    }

    self->frame %= self->max_frame;
}


Animation* NewAnimation(int max_frame, float speed) {
    Animation *anim = (Animation*)malloc(sizeof(Animation));

    if (anim != NULL) {
        // Methods
        anim->max_frame = max_frame;
        anim->speed = speed;

        anim->frame = 0;
        anim->dir = 0;
        anim->timer = 0.0f;

        // Functions
        anim->Update = Update;

        return anim;
    }

    free(anim);
    return NULL;
}

void DelAnimation(Animation *anim) {
    free(anim);
}
