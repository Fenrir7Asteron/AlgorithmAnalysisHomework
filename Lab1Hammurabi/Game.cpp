#include "Game.h"
#include "GameConfig.h"

void Game::Play()
{
    while (!GameOver())
    {
        messagePrinter.PrintRoundStartSummary(gameData);
        EndTurn();
    }
}

bool Game::GameOver() const
{
    return gameData.GetCurrentRound() > GameConfig::MAX_ROUND_COUNT;
}

void Game::EndTurn() {
    gameData.IncrementCurrentRound();
}
