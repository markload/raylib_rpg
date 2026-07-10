#ifndef ANIMATION_H
#define ANIMATION_H


// Class Animation
typedef struct {
    int frame, max_frame, dir;
    float timer, speed;

    void (*Update)(void*);
} Animation;

Animation * NewAnimation(int max_frame, float speed);
void DelAnimation(Animation *anim);

#endif
