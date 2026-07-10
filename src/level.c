#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/level.h"



// Private functions ----------------------------------------
static int** CreateLayer(int rows, int cols) {
    int **matrix = (int**)malloc(sizeof(int*) * rows);
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            matrix[i] = (int*)malloc(sizeof(int) * cols);
            if (matrix[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(matrix[j]);
                }
                free(matrix);
                return NULL;
            }
        }
        return matrix;
    }
    free(matrix);
    return NULL;
}

static void LoadLevel(void *l) {
    Level *self = (Level*)l;
    FILE *fp = fopen(self->filename, "r");

    if (fp == NULL) return;

    // layers_size[0] = rows(y); layers_size[1] = cols(x);
    fscanf(fp, "%d %d", &self->layers_size[0], &self->layers_size[1]);

    // Create Layers
    self->layer_bag = CreateLayer(self->layers_size[0], self->layers_size[1]);
    self->layer_for = CreateLayer(self->layers_size[0], self->layers_size[1]);
    self->layer_coll = CreateLayer(self->layers_size[0], self->layers_size[1]);

    // Read layers from file
    for (int i = 0; i < self->layers_size[0] * 3; i++) {
        for (int j = 0; j < self->layers_size[1]; j++) {
            if (i < self->layers_size[0])
                fscanf(fp, "%d", &self->layer_bag[i][j]);
            else if (i < self->layers_size[0] * 2)
                fscanf(fp, "%d", &self->layer_for[i][j]);
            else if (i < self->layers_size[0] * 3)
                fscanf(fp, "%d", &self->layer_coll[i][j]);
        }
    }
}


// Public functions ----------------------------------------
static void Draw(void *l) {
    Level *self = (Level*)l;
}

Level* NewLevel(
        Texture2D tileset,
        int tileset_size[2],
        int tilesize,
        char *filename) {
    Level *l = (Level*)malloc(sizeof(Level));

    if (l != NULL) {
        // Methods
        l->tileset = tileset;
        l->tileset_size[2] = tileset_size[2];
        l->tilesize = tilesize;

        l->filename = filename;

        // Functions
        l->Draw = Draw;
    }

    free(l);
    return NULL;
}

void DelLayer(Level *l) {
    UnloadTexture(l->tileset);
    free(l);
}
