#include "Game.h"
#include "Code/Data/GameConfig.h"
#include "Code/Data/ResourcesPaths.h"

Game::Game(const GameConfig config) : gameData_(config) {}

void Game::Play()
{
    bool firstRound = true;

    while (!GameOver(gameData_))
    {
        if (!firstRound) {
            if (UserInputManager::ReadGameExitInput())
                return;
        }

        firstRound = false;


        PreRoundSimulation(gameData_);

        MessagePrinter::PrintRoundStartSummary(gameData_);

        const RoundInput &roundInput = UserInputManager::GetRoundInput(gameData_);

        SimulateRoundStep(roundInput, gameData_);

        EndTurn();

        Save(PathToSaveFile);
    }

    MessagePrinter::PrintGameOverMessage(gameData_);
    DeleteSaveFile(PathToSaveFile);
}

bool Game::GameOver(GameData &data) const
{
    return gameData_.GetCurrentRound() > gameData_.GetMaxRound() || data.GetLoseFlag();
}

void Game::EndTurn() {
    gameData_.IncrementCurrentRound();
}

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
    data.SetStarvedToDeathCountLastYear(starvedToDeathCount);
    data.PutStarvedToDeathPercentToHistory((float) starvedToDeathCount / (float) currentCitizenCount);
    data.SetArrivedCitizenCount(arrivedCitizenCount);

    data.SetCurrentLandAcres(data.GetCurrentLandAcres() + roundInput.landAcresToBuy - roundInput.landAcresToSell);

    float starvedToDeathPercent = (float) starvedToDeathCount / (float) currentCitizenCount;
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

void Game::Load(const char *const pathToSaveFile) {
    SaveManager::Load(gameData_, pathToSaveFile);
}

void Game::Save(const char *const pathToSaveFile) {
    SaveManager::Save(gameData_, PathToSaveFile);
}

void Game::DeleteSaveFile(const string &pathToSaveFile) {
    SaveManager::DeleteSaveFile(pathToSaveFile);
}
