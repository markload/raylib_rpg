#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "animation.h"


typedef enum {
    DOWN = 0,
    RIGHT = 1,
    UP = 2,
    LEFT = 3
} TypeAnim;


// Class Player
typedef struct {
    int tilesize;
    Texture2D sprite;
    Rectangle src, dest;
    float speed;
    bool moving;
    Animation *anim;
    TypeAnim type_anim;

    void (*Update)(void*);
    void (*Draw)(void*);
} Player;

Player* NewPlayer(int tilesize,
        Texture2D sprite,
        Rectangle src,
        Rectangle dest,
        int anim_min_frame,
        int anim_max_frame,
        float anim_speed);

void DelPlayer(Player *pl);

#endif
