#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>

#include "../include/const.h"

Map CreateMap(char level)
{
    Map map;
    Cell c;
    int i, j;
    FILE* file = NULL;
    char fileName[10] = "Maps/map ";

    fileName[8] = level;

    map.imgs[0] = IMG_Load("Images/mur.jpg");
    map.imgs[1] = IMG_Load("Images/caisse.jpg");
    map.imgs[2] = IMG_Load("Images/objectif.png");
    map.imgs[3] = IMG_Load("Images/caisse_ok.jpg");
    
    map.objectives = 0;

    file = fopen(fileName, "r");
    
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            switch(fgetc(file))
            {
                case 'W':
                    c = Wall;
                    break;

                case 'B':
                    c = Box;
                    break;

                case 'D':
                    c = DoneBox;
                    break;

                case 'O':
                    c = Objective;
                    map.objectives++;
                    break;
                
                case 'S':
                    c = Ground;
                    map.spawn.x = j * BLOCK + ADJ;
                    map.spawn.y = i * BLOCK + ADJ;
                    break;

                default:
                    c = Ground;
                    break;
            }

            map.cells[i][j] = c;
        }
        
        fseek(file, 1, SEEK_CUR);
    }

    fclose(file);

    return map;
}

void PrintMap(Map map, SDL_Surface* screen)
{
    int i, j;
    SDL_Rect pos;

    for (i = 0; i < H; i++)
    {
        pos.y = i * BLOCK + ADJ;

        for (j = 0; j < W; j++)
        {
            pos.x = j * BLOCK + ADJ;
            if (map.cells[i][j] != Ground)
                SDL_BlitSurface(map.imgs[map.cells[i][j]], NULL, screen, &pos);
        }
    }
}

void UnloadMap(Map* map)
{
    int i;

    for (i = 0; i < 4; i++)
        SDL_FreeSurface(map->imgs[i]);

}
