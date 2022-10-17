#include <iostream>
#include "Game.h"
#include "Code/Data/GameConfig.h"
#include "Code/Data/ResourcesPaths.h"

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    GameConfig gameConfig(PathToGameConfig);

    Game game(gameConfig);

    game.Load(PathToSaveFile);
    game.Play();
    return 0;
}
