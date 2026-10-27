#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/level.h"



// Private functions ----------------------------------------
// INFO: layers_size[1] = rows(y); layers_size[0] = cols(x);
static void DelMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

// Create matrix for layer
static int** NewMatrix(int rows, int cols) {
    int **matrix = (int**)malloc(sizeof(int*) * rows);
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            matrix[i] = (int*)malloc(sizeof(int) * cols);
            if (matrix[i] == NULL) {
                DelMatrix(matrix, i);
                return NULL;
            }
        }
        return matrix;
    }
    free(matrix);
    return NULL;
}

static void PrintMatrix(int **matrix, int rows, int cols) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            printf("%d ", matrix[y][x]);
        }
        printf("\n");
    }
}

// Read file and write inf. in class
static void LoadLevel(void *l) {
    Level *self = (Level*)l;

    FILE *fp = fopen(self->filename, "r");
    if (fp == NULL) { fclose(fp); return; }

    // Load Tilesets ---
    fscanf(fp, "%d", &self->count_tilesets);
    self->tilesets = (TilesetInfo*)malloc(sizeof(TilesetInfo) * self->count_tilesets);
    if (self->tilesets == NULL) free(self->tilesets);

    for (int i = 0; i < self->count_tilesets; i++) {
        char *file_tileset = (char*)malloc(sizeof(char) * 10000);
        if (file_tileset == NULL) { free(file_tileset); break; }
        fscanf(fp, "%s %d %d %d", file_tileset, &self->tilesets[i].size[0], &self->tilesets[i].size[1], &self->tilesets[i].firstgid);

        // Pxl -> tiles
        self->tilesets[i].size[0] /= self->tilesize;
        self->tilesets[i].size[1] /= self->tilesize;

        self->tilesets[i].tileset = LoadTexture(file_tileset);
        free(file_tileset);
    }

    // Load Layers ---
    fscanf(fp, "%d %d", &self->layers_size[0], &self->layers_size[1]);

    // Create Map with 3 Layers(background, foreground, collision)
    self->layer_back = NewMatrix(self->layers_size[1], self->layers_size[0]);
    self->layer_fore = NewMatrix(self->layers_size[1], self->layers_size[0]);
    self->layer_coll = NewMatrix(self->layers_size[1], self->layers_size[0]);

    // Read layers from file
    for (int y = 0; y < self->layers_size[1] * 3; y++) {
        for (int x = 0; x < self->layers_size[0]; x++) {
            int Y = y % self->layers_size[1];
            if (y < self->layers_size[1])
                fscanf(fp, "%d,", &self->layer_back[Y][x]);
            else if (y < self->layers_size[1] * 2)
                fscanf(fp, "%d,", &self->layer_fore[Y][x]);
            else if (y < self->layers_size[1] * 3)
                fscanf(fp, "%d,", &self->layer_coll[Y][x]);
        }
    }

    fclose(fp);
}

static void UnloadLevel(void *l) {
    Level *self = (Level*)l;
    DelMatrix(self->layer_back, self->layers_size[1]);
    DelMatrix(self->layer_fore, self->layers_size[1]);
    DelMatrix(self->layer_coll, self->layers_size[1]);


    for (int i = 0; i < self->count_tilesets; i++)
        UnloadTexture(self->tilesets[i].tileset);

    free(self->tilesets);
}

static int FindTileset(void *l, int tile) {
    Level *self = (Level*)l;
    for (int i = 1; i < self->count_tilesets; i++) {
        if (tile < self->tilesets[i].firstgid)
            return i-1;
    }
    return self->count_tilesets - 1;
}


// Public functions ----------------------------------------
void Draw(void *l) {
    Level *self = (Level*)l;

    // 1 - background; 2 - foreground
    for (int y = 0; y < self->layers_size[1]; y++) {
        for (int x = 0; x < self->layers_size[0]; x++) {
            // INFO: Tile counting starts from 1
            int tile1 = self->layer_back[y][x] - 1;
            int tile2 = self->layer_fore[y][x] - 1;

            Rectangle dest = (Rectangle){
                x * self->tilesize, y * self->tilesize,
                self->tilesize, self->tilesize
            };

            if (tile1 != -1) {
                int num_tileset1 = FindTileset(l, tile1);
                Rectangle src1 = (Rectangle){
                    (tile1 - self->tilesets[num_tileset1].firstgid) % self->tilesets[num_tileset1].size[0] * self->tilesize,
                    (tile1 - self->tilesets[num_tileset1].firstgid) / self->tilesets[num_tileset1].size[0] * self->tilesize,
                    self->tilesize, self->tilesize
                };
                DrawTexturePro(self->tilesets[num_tileset1].tileset, src1, dest, (Vector2){0, 0}, 0.0f, RAYWHITE);
            }

            if (tile2 != -1) {
                int num_tileset2 = FindTileset(l, tile2);
                Rectangle src2 = (Rectangle){
                    (tile2 - self->tilesets[num_tileset2].firstgid) % self->tilesets[num_tileset2].size[0] * self->tilesize,
                    (tile2 - self->tilesets[num_tileset2].firstgid) / self->tilesets[num_tileset2].size[0] * self->tilesize,
                    self->tilesize, self->tilesize
                };
                DrawTexturePro(self->tilesets[num_tileset2].tileset, src2, dest, (Vector2){0, 0}, 0.0f, RAYWHITE);
            }
        }
    }
}

bool Collision(void *l, Rectangle pl) {
    Level *self = (Level*)l;
    for (int y = 0; y < self->layers_size[1]; y++) {
        for (int x = 0; x < self->layers_size[0]; x++) {
            if (self->layer_coll[y][x] == 1 && CheckCollisionRecs(pl, (Rectangle){x, y, self->tilesize, self->tilesize}))
                return true;
        }
    }
    return false;
}

Level* NewLevel(int tilesize, char *filename) {
    Level *l = (Level*)malloc(sizeof(Level));

    if (l != NULL) {
        // Methods
        l->tilesize = tilesize;
        l->filename = filename;

        // Functions
        l->Draw = Draw;

        LoadLevel(l);
        return l;
    }

    free(l);
    return NULL;
}

void DelLevel(Level *l) {
    UnloadLevel(l);
    free(l);
}

/* level1.map
 *
 * 1) Count of tilesets
 * 2) Filename of tilesets & Width tilesets(pxl) & Height tilesets(pxl) & Firstgid
 * 3) Tilemap size(columns/x, rows/y)
 * 4) Tilemap background & foreground & collision
 */
