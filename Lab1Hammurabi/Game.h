#pragma once

#include "MessagePrinter.h"
#include "GameData.h"

class Game
{
private:
    MessagePrinter messagePrinter;
    GameData gameData;

public:
	void Play();

    bool GameOver() const;

    void EndTurn();
};

