#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "const.h"
#include "map.h"
#include "title.h"

static void ModifCell(Map* map, Cell cell, SDL_Rect pos)
{
    int i, j;

    i = (pos.y - ADJ) / BLOCK;
    j = (pos.x - ADJ) / BLOCK; 
    
    if (i >= 0 && i < H && j >= 0 && j < W)  
    {
        if (cell == Spawn)
        {
            map->spawn.x = j * BLOCK + ADJ;
            map->spawn.y = i * BLOCK + ADJ;
            cell = Ground;
        }
    
        map->cells[i][j] = cell;
    }
}

static void SaveMap(Map map, char level)
{
    FILE* file = NULL;
    int i, j, c;
    char fileName[10] = "Maps/map ";

    fileName[8] = level;

    file = fopen(fileName, "w+");
    
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            if (i * BLOCK + ADJ == map.spawn.y && j * BLOCK + ADJ == map.spawn.x)
                c = 'S';
            else
            {
                switch(map.cells[i][j])
                {
                    case Wall:
                        c = 'W';
                        break;

                    case Objective:
                        c = 'O';
                        break;

                    case Box:
                        c = 'B';
                        break;

                    case DoneBox:
                        c = 'D';
                        break;
                
                    default:
                        c = ' ';
                        break;
                }
            }
            
            fputc(c, file);
        }
        
        if(i < H - 1)
            fputc('\n', file);
    }

    fclose(file);
}

static void ResetMap(Map* map)
{
    int i, j;

    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            if (map->cells[i][j] != Spawn)
                map->cells[i][j] = Ground;
        }
    }

    map->objectives = 0;
}

void Mapping(SDL_Surface* screen)
{
    Map map;
    Uint32 black, red;
    SDL_Event event;
    SDL_Surface* spawn = NULL;
    SDL_Surface* rect = NULL;
    SDL_Surface* fill = NULL;
    Cell cell;
    SDL_Rect mousePos, rectPos, fillPos;
    int leave = 0;
    char level = '1';
    
    TTF_Font* font = NULL;
    Title title;

    font = TTF_OpenFont("Fonts/AlphaWood.ttf", 50);
    title = InitTitle(level, font);
    
    black = SDL_MapRGB(screen->format, 0, 0, 0);
    red = SDL_MapRGB(screen->format, 171, 51, 53);
    map = CreateMap(level);
    spawn = IMG_Load("Images/mario_bas.gif");
    rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 350, 350, 32, 0, 0, 0, 0);
    fill = SDL_CreateRGBSurface(SDL_HWSURFACE, 340, 340, 32, 0, 0, 0 ,0);
    SDL_FillRect(rect, NULL, red);
    SDL_FillRect(fill, NULL, black);
    cell = Wall;

    rectPos.x = screen->w / 2 - rect->w / 2;
    rectPos.y = screen->h / 2 - rect->h / 2;

    fillPos.x = screen->w / 2 - fill->w / 2;
    fillPos.y = screen->h / 2 - fill->h / 2;

    while (!leave)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SaveMap(map, level);
                        leave = 1;
                        break;

                    case SDLK_s:
                        SaveMap(map, level);
                        break;

                    case SDLK_r:
                        ResetMap(&map);
                        break;

                    case SDLK_1:
                        cell = Wall;
                        break;

                    case SDLK_2:
                        cell = Box;
                        break;

                    case SDLK_3:
                        cell = Objective;
                        break;

                    case SDLK_4:
                        cell = DoneBox;
                        break;

                    case SDLK_5:
                        cell = Spawn;
                        break;

                    case SDLK_LEFT:
                        if (level > 49)
                        {
                            SaveMap(map, level);
                            level--;
                            map = CreateMap(level);
                            UpdateTitle(&title, level, font);
                        }
                        break;

                    case SDLK_RIGHT:
                        if (level - 48 < LEVELS)
                        {
                            SaveMap(map, level);
                            level++;
                            map = CreateMap(level);
                            UpdateTitle(&title, level, font);
                        }
                        break;

                    default:
                        break;
                }

                break;

            case SDL_MOUSEBUTTONUP:

                switch(event.button.button)
                {
                    case SDL_BUTTON_RIGHT:
                        ModifCell(&map, Ground, mousePos);
                        break;

                    case SDL_BUTTON_LEFT:
                        ModifCell(&map, cell, mousePos);
                        break;
                }

                break;

            case SDL_MOUSEMOTION:
                mousePos.x = event.motion.x;
                mousePos.y = event.motion.y;
                break;
        }


        SDL_FillRect(screen, NULL, black);

        SDL_BlitSurface(rect, NULL, screen, &rectPos);
        SDL_BlitSurface(fill, NULL, screen, &fillPos);
        PrintMap(map, screen);

        SDL_BlitSurface(spawn, NULL, screen, &(map.spawn));

        if (cell == Spawn)
            SDL_BlitSurface(spawn, NULL, screen, &(mousePos));
        else
            SDL_BlitSurface(map.imgs[cell], NULL, screen, &(mousePos));

        SDL_BlitSurface(title.img, NULL, screen, &(title.pos)); 
        SDL_Flip(screen);
    }

    UnloadMap(&map);
    SDL_FreeSurface(spawn);
    SDL_FreeSurface(rect);
    SDL_FreeSurface(fill);
    SDL_FreeSurface(title.img);
}


