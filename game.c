#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "const.h"
#include "player.h"
#include "map.h"
#include "title.h"

static int IsGameFinished(Map map)
{
    return map.objectives == 0;
}

static void InitGame(Player* player, Map* map, char level)
{
    *player = CreatePlayer();
    *map = CreateMap(level);
    player->coord = map->spawn;
}

void Play(SDL_Surface* screen)
{
    Uint32 bg = SDL_MapRGB(screen->format, 0, 0, 0);
    SDL_Event event;
    Player player;
    Map map;
    Dir dir;
    int leave = 0;
    char level = '1';
    
    Title title;
    TTF_Font* font = NULL;

    InitGame(&player, &map, level);

    font = TTF_OpenFont("Fonts/AlphaWood.ttf", 50);
    title = InitTitle(level, font);
    
    SDL_EnableKeyRepeat(100, 100);

    while (!leave)
    {
        dir = None;
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_KEYDOWN:
                
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        leave = 1;
                        break;

                    case SDLK_a:
                        dir = Left;
                        break;

                    case SDLK_d:
                        dir = Right;
                        break;

                    case SDLK_w:
                        dir = Up;
                        break;

                    case SDLK_s:
                        dir = Down;
                        break;

                    case SDLK_r:
                        InitGame(&player, &map, level);
                        break;

                    case SDLK_LEFT:
                        if (level > 49)
                        {
                            level--;
                            InitGame(&player, &map, level);
                            UpdateTitle(&title, level, font);
                        }
                        break;

                    case SDLK_RIGHT:
                        if (level - 48 < LEVELS)
                        {
                            level++;
                            InitGame(&player, &map, level);
                            UpdateTitle(&title, level, font);
                        }
                        break;

                    default:
                        break;
                }
        }
            
        if (dir != None)
        {
            PlayerMove(&player, &map, dir);            

            if(IsGameFinished(map))
            {
                level++;

                if(level % 49 < LEVELS)
                {
                    InitGame(&player, &map, level);
                    UpdateTitle(&title, level, font);
                }

                else
                    leave = 1;
            }
        }
        
        SDL_FillRect(screen, NULL, bg); 
        PrintMap(map, screen);
        SDL_BlitSurface(player.imgs[player.dir], NULL, screen, &(player.coord));
        SDL_BlitSurface(title.img, NULL, screen, &(title.pos));
        SDL_Flip(screen); 
    }
    
    UnloadMap(&map);
    UnloadPlayer(&player);

    TTF_CloseFont(font);
    SDL_FreeSurface(title.img);
}
