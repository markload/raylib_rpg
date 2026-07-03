#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "animation.h"


typedef enum TypeAnim {
    IDLE, WALK, ATTACK, DIE
} TypeAnim;


// Class Player
typedef struct Player {
    Texture2D sprite;
    Rectangle src, dest;
    float speed;
    bool moving;
    Animation *anim;
    TypeAnim type_anim;

    void (*Update)(void*);
    void (*Draw)(void*);
    void (*DeInit)(void*);

    void (*Input)(void*);
} Player;

Player* NewPlayer(Texture2D sprite, Rectangle src, Rectangle dest, int anim_max_frame, float anim_speed);
void DelPlayer(Player *pl, Animation *anim);

#endif
