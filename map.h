#ifndef MAP
#define MAP

Map CreateMap(char level);
void PrintMap(Map map, SDL_Surface* screen);
void UnloadMap(Map* map);

#endif
