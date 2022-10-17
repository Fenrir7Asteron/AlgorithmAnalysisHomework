#include "Game.h"
#include "Code/Data/GameConfig.h"

void Game::Play()
{
    while (!GameOver(gameData))
    {
        PreRoundSimulation(gameData);

        messagePrinter.PrintRoundStartSummary(gameData);

        const RoundInput &roundInput = inputManager.GetRoundInput(messagePrinter, gameData);

        SimulateRoundStep(roundInput, gameData);

        EndTurn();
    }

    messagePrinter.PrintGameOverMessage(gameData);
}

bool Game::GameOver(GameData &data) const
{
    return gameData.GetCurrentRound() > gameData.GetMaxRound() || data.GetLoseFlag();
}

void Game::EndTurn() {
    gameData.IncrementCurrentRound();
}

Game::Game(const GameConfig config) : gameData(config) {}

void Game::PreRoundSimulation(GameData &data) const {
    int landPrice = GetRandomLandPrice(data);
    data.SetLandPrice(landPrice);
}

void Game::SimulateRoundStep(const RoundInput &roundInput, GameData &data) {
    int landPrice = data.GetCurrentLandPrice();
    int wheatPerLandAcre = GetRandomWheatPerLandAcre(data);
    int wheatCollected = roundInput.landAcresToSow * wheatPerLandAcre;
    int previousRoundWheatBushels = data.GetCurrentWheatBushels();

    int newWheatBushels = previousRoundWheatBushels
                          - roundInput.landAcresToBuy * landPrice                   // wheat used to buy land
                          + roundInput.landAcresToSell * landPrice                  // wheat received for sold land
                          - roundInput.wheatBushelsToEat                            // wheat eaten
                          - roundInput.landAcresToSow * data.GetLandAcreSowPrice()  // wheat used to sow land
                          + wheatCollected                                          // wheat collected from land
                          ;

    int wheatEatenByRats = min(newWheatBushels, (int) ((float) newWheatBushels * (GetRandomRatWheatDamagePercent(data))));
    newWheatBushels -= wheatEatenByRats;

    int currentCitizenCount = data.GetCurrentCitizenCount();

    int starvedToDeathCount = max(0,
                                  currentCitizenCount
                                  - roundInput.wheatBushelsToEat / data.GetWheatNeededForPersonPerYear());

    int arrivedCitizenCount = clamp(starvedToDeathCount / 2 + (5 - wheatCollected) * newWheatBushels / 600 + 1,
                                    0, 50);
    
    int newCitizenCount = max(0, currentCitizenCount - starvedToDeathCount + arrivedCitizenCount);

    if (RollPlagueRandom(data)) {
        newCitizenCount /= 2;
        data.SetPlagueFlag(true); // Remember that plague happened.
    } else {
        data.SetPlagueFlag(false); // Reset plague flag.
    }

    data.SetCurrentWheatBushels(newWheatBushels);
    data.SetWheatCollected(wheatCollected, wheatPerLandAcre);
    data.SetWheatEatenByRatsLastYear(wheatEatenByRats);

    data.SetCurrentCitizenCount(newCitizenCount);
    data.PutStarvedToDeathCountToHistory(starvedToDeathCount);
    data.SetArrivedCitizenCount(arrivedCitizenCount);

    data.SetCurrentLandAcres(data.GetCurrentLandAcres() + roundInput.landAcresToBuy - roundInput.landAcresToSell);

    float starvedToDeathPercent = (float) starvedToDeathCount / currentCitizenCount;
    if (starvedToDeathPercent >= 0.45f)
        data.SetLoseFlag(true);
}

int Game::GetRandomLandPrice(const GameData &data) const {
    const NumberRange<int> &range = data.GetLandPriceRange();
    return Random::GetRandomInRange(range.start, range.end);
}

int Game::GetRandomWheatPerLandAcre(const GameData &data) const {
    const NumberRange<int> &range = data.GetWheatPerLandAcrePriceRange();
    return Random::GetRandomInRange(range.start, range.end);
}

float Game::GetRandomRatWheatDamagePercent(const GameData &data) {
    const NumberRange<float> &range = data.GetRatWheatDamagePercentRange();
    return Random::GetRandomInRange(range.start, range.end);
}

bool Game::RollPlagueRandom(const GameData &data) {
    if (Random::GetRandomInRange(0.0f, 1.0f) <= data.GetMaxPlagueProbability()) {
        return true;
    }

    return false;
}
