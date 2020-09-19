#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "const.h"

Player CreatePlayer()
{
    Player player;
    player.dir = Up;
    player.imgs[0] = IMG_Load("Images/mario_haut.gif");
    player.imgs[1] = IMG_Load("Images/mario_droite.gif");
    player.imgs[2] = IMG_Load("Images/mario_bas.gif");
    player.imgs[3] = IMG_Load("Images/mario_gauche.gif");
    player.coord.x = 0;
    player.coord.y = 0;

    return player;
}

static void MoveBox(int i, int j, Map* map, Dir dir)
{
    Cell* prevCell;

    prevCell = &(map->cells[i][j]);

    switch(dir)
    {
        case Up:
            i--;
            break;

        case Down:
            i++;
            break;

        case Left:
            j--;
            break;

        case Right:
            j++;
            break;
        
        default:
            break;
    }
    
    if (map->cells[i][j] == Objective)
    {
        map->cells[i][j] = DoneBox;

        if (*prevCell == Box)
        {
            *prevCell = Ground;
            map->objectives--;
        }

        else
            *prevCell = Objective;
    }

    else if (map->cells[i][j] == Ground)
    {
        map->cells[i][j] = Box;

        if (*prevCell == DoneBox)
        {
            *prevCell = Objective;
            map->objectives++;
        }

        else
            *prevCell = Ground;
    }
}

void PlayerMove(Player* player, Map* map, Dir dir)
{
    int i, j;

    i = (player->coord.y - ADJ) / BLOCK;
    j = (player->coord.x - ADJ) / BLOCK;

    player->dir = dir;

    switch(dir)
    {
        case Up:
            i--;
            break;

        case Down:
            i++;
            break;

        case Left:
            j--;
            break;

        case Right:
            j++;
            break;

        default:
            break;
    }
     
    if (map->cells[i][j] == Box || map->cells[i][j] == DoneBox)
        MoveBox(i, j, map, dir);

    if (map->cells[i][j] == Ground || map->cells[i][j] == Objective) 
    {
        player->coord.y = i * BLOCK + ADJ;
        player->coord.x = j * BLOCK + ADJ;
    }
}

void UnloadPlayer(Player* player)
{
    int i;

    for (i = 0; i < 4; i++)
        SDL_FreeSurface(player->imgs[i]);
}
