#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define MAP_SIZE 9

struct Player {
    int x;
    int y;
};

struct Map {
    int map[MAP_SIZE][MAP_SIZE];
};

struct Map* init_map() {
    struct Map *map = malloc(sizeof(struct Map));

    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            map->map[i][j] = 1;
        }
    }

    return map;
}

void delay(int milliseconds){
    clock_t start_time = clock();
    while(clock() < start_time + milliseconds * (CLOCKS_PER_SEC/1000));
}

void make_random_move(struct Player* player) {
    int rand_number = rand() % 4;
    switch (rand_number) {
        case 0:
            if( player->y < MAP_SIZE-1) {
                player->y += 1;
            }
            break;
        case 1:
            if(player->y > 0) {

                player->y -= 1;
            }
            break;
        case 2:
            if(player->x  < MAP_SIZE -1) {
                player->x += 1;

            }
            break;
        case 3:
            if(player->x >0) {
                player->x -= 1;

            }
            break;
    }
}

void update_map(struct Map* map, struct Player* player) {
    map->map[player->x][player->y] = 0;
}

void init_window(struct Map* map, struct Player* player) {
    const int tileSize = 50;
    const int tileSpacing = 2;
    const int width = MAP_SIZE * tileSize + (MAP_SIZE - 1) * tileSpacing;
    const int height = MAP_SIZE * tileSize + (MAP_SIZE - 1) * tileSpacing;

    InitWindow(width, height, "Random Walk Generator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        make_random_move(player);
        update_map(map,player);
        delay(200);

        BeginDrawing();
        ClearBackground(BLACK);


        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                if (map->map[i][j] == 1) {
                    int x = j * (tileSize + tileSpacing);
                    int y = i * (tileSize + tileSpacing);
                    DrawRectangle(x, y, tileSize, tileSize, GRAY);
                }
            }
        }


        int playerX = player->y * (tileSize + tileSpacing);
        int playerY = player->x * (tileSize + tileSpacing);
        DrawRectangle(playerX, playerY, tileSize, tileSize, RED);

        EndDrawing();
    }

    CloseWindow();
}

struct Player* init_player() {
    struct Player* plr = malloc(sizeof(struct Player));
    plr->x = MAP_SIZE / 2;
    plr->y = MAP_SIZE / 2;

    return plr;
}

int main() {
    srand(time(NULL));

    struct Map* map = init_map();
    struct Player* player = init_player();

    init_window(map, player);

    free(map);
    free(player);

    return 0;
}
