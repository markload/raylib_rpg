#ifndef LAYER_H
#define LAYER_H

#include <raylib.h>
#include <stdio.h>

typedef struct {
    Texture2D tileset;
    int size[2];
    int firstgid;
} TilesetInfo;

typedef struct {
    int count_tilesets;
    TilesetInfo *tilesets;
    int tilesize;

    int layers_size[2];
    int **layer_back, **layer_fore, **layer_coll;

    char *filename;

    void (*Draw)(void*);
    bool (*Collision)(void*, Rectangle);
} Level;

Level* NewLevel(int tilesize, char *filename);
void DelLevel(Level* l);

#endif
