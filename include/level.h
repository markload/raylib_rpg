#ifndef LAYER_H
#define LAYER_H

#include <raylib.h>
#include <stdio.h>

typedef struct {
    Texture2D tileset;
    int tileset_size[2];
    int tilesize;

    int layers_size[2];
    int **layer_bag, **layer_for, **layer_coll;

    char *filename;

    void (*Draw)(void*);
} Level;

Level* NewLayer(Texture2D tileset, Vector2 tileset_size, int tilesize, char *filename);
void DelLayer(Level* l);

#endif
