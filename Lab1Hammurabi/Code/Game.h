#pragma once

#include "Code/IO/MessagePrinter.h"
#include "Code/Data/GameData.h"
#include "Code/IO/UserInputManager.h"
#include "Code/Data/GameConfig.h"
#include "Code/Utils/Random.h"

class Game
{
private:
    MessagePrinter messagePrinter;
    UserInputManager inputManager;
    GameData gameData;

    void SimulateRoundStep(const RoundInput &roundInput, GameData &data);

public:
	void Play();

    bool GameOver(GameData &data) const;

    void EndTurn();

    Game(GameConfig config);

    int GetRandomLandPrice(const GameData &data) const;

    int GetRandomWheatPerLandAcre(const GameData &data) const;

    float GetRandomRatWheatDamagePercent(const GameData &data);

    void PreRoundSimulation(GameData &data) const;

    bool RollPlagueRandom(const GameData &data);
};

