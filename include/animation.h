#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>

// Class Animation
typedef struct {
    int min_frame, max_frame, current;
    float timer, speed;

    void (*Update)(void*);
} Animation;

Animation * NewAnimation(int min_frame, int max_frame, float speed);
void DelAnimation(Animation *anim);

#endif
