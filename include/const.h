#ifndef CONST
#define CONST

#define W 10 
#define H 10
#define BLOCK 34
#define SIZE 600
#define ADJ ((SIZE - (H * BLOCK)) / 2) 
#define LEVELS 5 

typedef enum Dir Dir;
enum Dir
{
    Up,
    Right,
    Down,
    Left,
    None
};

typedef struct Player Player;
struct Player
{
    SDL_Surface* imgs[4];
    SDL_Rect coord;
    Dir dir;
};

typedef enum Cell Cell;
enum Cell
{
    Wall,
    Box,
    Objective,
    DoneBox,
    Spawn,
    Ground
};

typedef struct Map Map;
struct Map
{
    SDL_Surface* imgs[4];
    SDL_Rect spawn;
    Cell cells[H][W];
    int objectives;
};

typedef struct Title Title;
struct Title
{
    SDL_Surface* img;
    SDL_Rect pos;
    SDL_Color color;
    char text[20];
};

#endif
