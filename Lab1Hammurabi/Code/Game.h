#pragma once

#include "Code/IO/MessagePrinter.h"
#include "GameData.h"
#include "Code/IO/UserInputManager.h"
#include "GameConfig.h"
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

    int GetRandomWheatPerLandAcre(GameData &data) const;

    float GetRandomRatWheatDamagePercent(GameData &data);

    void PreRoundSimulation(GameData &data) const;

    bool RollPlagueRandom(GameData &data);
};

