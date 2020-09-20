#ifndef PLAYER
#define PLAYER

Player CreatePlayer();
void PlayerMove(Player* player, Map* map, Dir dir);
void UnloadPlayer(Player* player);

#endif
