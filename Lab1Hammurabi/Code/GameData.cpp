//
// Created by biore on 9/29/2022.
//

#include <random>
#include "GameData.h"

GameData::GameData(const GameConfig& config) {
    _config = &config;

    maxRound = config.GetMaxRound();
    currentRound = 1;

    maxCitizens = config.GetDefaultCitizenCount();
    maxWheatBushels = config.GetDefaultWheatBushels();
    maxLandAcres = config.GetDefaultLandAcres();

    currentCitizenCount = maxCitizens;
    currentWheatBushels = maxWheatBushels;
    currentLandAcres = maxLandAcres;

    const IntRange &landPriceRange = config.GetLandPriceRange();
    currentLandPrice = rand() % landPriceRange.end + landPriceRange.start;
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

int GameData::GetCurrentLandPrice() const {
    return currentLandPrice;
}

int GameData::GetLandAcreSowPrice() const {
    return _config->GetDefaultLandAcreSowPrice();
}

int GameData::GetCurrentLandAcres() const {
    return currentLandAcres;
}

int GameData::GetCurrentCitizenCount() const {
    return currentCitizenCount;
}

int GameData::GetCitizenLandAcresCultivationMaximum() const {
    return _config->GetDefaultCitizenLandAcresCultivationMaximum();
}
