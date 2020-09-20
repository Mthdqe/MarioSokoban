#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
 
#include "../include/const.h"
#include "../include/game.h"
#include "../include/player.h"
#include "../include/level.h"

int main()
{
    SDL_Surface* screen = NULL;
    SDL_Surface* menu = NULL;
    SDL_Rect menuPos;
    SDL_Event event;
    Uint32 bgColor;
    int leave = 0;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Mario Sokoban", NULL);
    
    TTF_Init(); 

    screen = SDL_SetVideoMode(SIZE, SIZE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    menu = IMG_Load("Images/menu.jpg");
    menuPos.x = (screen->w - menu->w) / 2;
    menuPos.y = (screen->h - menu->h) / 2;
    bgColor = SDL_MapRGB(screen->format, 0, 0, 0);
    
    while (!leave) 
    {
        SDL_FillRect(screen, NULL, bgColor);
        SDL_BlitSurface(menu, NULL, screen, &menuPos);
        SDL_Flip(screen);

        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_1:
                        Play(screen);
                        break;
                    
                    case SDLK_2:
                        Mapping(screen);
                        break; 

                    case SDLK_ESCAPE:
                        leave = 1;
                        break;

                    default:
                        break;
                }
                break;
        }
    }

    TTF_Quit();
    
    SDL_FreeSurface(screen);
    SDL_FreeSurface(menu);
    SDL_Quit();

    return 0;
}
