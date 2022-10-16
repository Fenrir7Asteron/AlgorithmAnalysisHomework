//
// Created by biore on 9/29/2022.
//

#include <random>
#include "GameData.h"

GameData::GameData(const GameConfig& config) {
    _config = &config;

    currentRound_ = 1;

    currentCitizenCount_ = _config->GetDefaultCitizenCount();
    currentWheatBushels_ = _config->GetDefaultWheatBushels();
    currentLandAcres_ = _config->GetDefaultLandAcres();

    currentLandPrice_ = 0;
    plagueFlag_ = false;
    loseFlag_ = false;
}

int GameData::GetCurrentRound() const {
    return currentRound_;
}

void GameData::IncrementCurrentRound() {
    currentRound_++;
}

int GameData::GetMaxRound() const {
    return _config->GetMaxRound();
}

int GameData::GetCurrentWheatBushels() const {
    return currentWheatBushels_;
}

int GameData::GetLandAcreSowPrice() const {
    return _config->GetDefaultLandAcreSowPrice();
}

int GameData::GetCurrentLandAcres() const {
    return currentLandAcres_;
}

int GameData::GetCurrentCitizenCount() const {
    return currentCitizenCount_;
}

int GameData::GetCitizenLandAcresCultivationMaximum() const {
    return _config->GetDefaultCitizenLandAcresCultivationMaximum();
}

void GameData::SetCurrentWheatBushels(int wheatBushels) {
    currentWheatBushels_ = wheatBushels;
}

const NumberRange<int> &GameData::GetLandPriceRange() const {
    return _config->GetLandPriceRange();
}

const NumberRange<int> &GameData::GetWheatPerLandAcrePriceRange() {
    return _config->GetWheatPerLandAcrePriceRange();
}

const NumberRange<float> &GameData::GetRatWheatDamagePercentRange() {
    return _config->GetRatWheatDamagePercentRange();
}

void GameData::SetLandPrice(int landPrice) {
    currentLandPrice_ = landPrice;
}

int GameData::GetCurrentLandPrice() const {
    return currentLandPrice_;
}

int GameData::GetWheatNeededForPersonPerYear() const {
    return _config->GetWheatNeededForPersonPerYear();
}

void GameData::SetCurrentCitizenCount(int newCitizenCount) {
    currentCitizenCount_ = newCitizenCount;
}

float GameData::GetMaxPlagueProbability() const {
    return _config->GetMaxPlagueProbability();
}

void GameData::SetPlagueFlag(bool plagueFlag) {
    plagueFlag_ = plagueFlag;
}

void GameData::SetLoseFlag(bool loseFlag) {
    loseFlag_ = loseFlag;
}

bool GameData::GetLoseFlag() const {
    return loseFlag_;
}
