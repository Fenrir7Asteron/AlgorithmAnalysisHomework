#include "Game.h"
#include "GameConfig.h"

void Game::Play()
{
    while (!GameOver())
    {
        messagePrinter.PrintRoundStartSummary(gameData);
        inputManager.GetRoundInput(messagePrinter, gameData);

        EndTurn();
    }
}

bool Game::GameOver() const
{
    return gameData.GetCurrentRound() > gameData.GetMaxRound();
}

void Game::EndTurn() {
    gameData.IncrementCurrentRound();
}

Game::Game(const GameConfig config) : gameData(config) {}
