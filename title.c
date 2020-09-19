#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

#include "const.h"
#include "title.h"

Title InitTitle(char level, TTF_Font* font)
{
    Title title;

    title.color.r = 255;
    title.color.b = 255;
    title.color.g = 255;

    sprintf(title.text, "Level %d", level % 49 + 1);
    
    title.pos.y = 25;
    title.pos.x = 220;

    title.img = TTF_RenderText_Solid(font, title.text, title.color);
    
    UpdateTitle(&title, level, font); 

    return title;
}

void UpdateTitle(Title* title, char level, TTF_Font* font)
{
    sprintf(title->text, "Level %d", level % 49 + 1);
    title->img = TTF_RenderText_Solid(font, title->text, title->color);
}
