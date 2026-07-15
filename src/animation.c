#include <raylib.h>
#include <stdlib.h>

#include "../include/animation.h"


static void Update(void *anim) {
    Animation *self = (Animation*)anim;
    self->timer += GetFrameTime();
    if (self->timer >= self->speed) {
        self->timer = 0.0f;
        self->current++;
    }

    if (self->current > self->max_frame)
        self->current = self->min_frame;

}


Animation* NewAnimation(int min_frame, int max_frame, float speed) {
    Animation *anim = (Animation*)malloc(sizeof(Animation));

    if (anim != NULL) {
        // Methods
        anim->min_frame = min_frame;
        anim->max_frame = max_frame;
        anim->speed = speed;

        anim->current = 0;
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
