//
// Created by biore on 9/29/2022.
//

#include "GameData.h"

GameData::GameData(const GameConfig config) {
    maxRound = config.GetMaxRound();
    currentRound = 1;

    maxCitizens = config.GetDefaultCitizenCount();
    maxWheatBushels = config.GetDefaultWheatBushels();
    maxLandAcres = config.GetDefaultLandAcres();

    currentCitizens = maxCitizens;
    currentWheatBushels = maxWheatBushels;
    currentLandAcres = maxLandAcres;
}

int GameData::GetCurrentRound() const {
    return currentRound;
}

void GameData::IncrementCurrentRound() {
    currentRound++;
}

int GameData::GetMaxRound() const {
    return maxRound;
}

int GameData::GetCurrentWheatBushels() const {
    return currentWheatBushels;
}
