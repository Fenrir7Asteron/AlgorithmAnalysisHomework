#pragma once

#include "MessagePrinter.h"
#include "GameData.h"
#include "UserInputManager.h"
#include "GameConfig.h"

class Game
{
private:
    MessagePrinter messagePrinter;
    UserInputManager inputManager;
    GameData gameData;

public:
	void Play();

    bool GameOver() const;

    void EndTurn();

    Game(GameConfig config);
};

