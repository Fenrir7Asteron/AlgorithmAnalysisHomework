#include <iostream>
#include "Game.h"
#include "GameConfig.h"

static const char *const PathToGameConfig = "data/gameConfig.txt";

int main()
{
    GameConfig gameConfig(PathToGameConfig);
    Game game(gameConfig);
    game.Play();
    return 0;
}
