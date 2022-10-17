//
// Created by biore on 9/29/2022.
//

#include <random>
#include "GameData.h"

GameData::GameData(const GameConfig& config) {
    _config = &config;

    persistentGameData_.currentRound_ = 1;

    persistentGameData_.currentCitizenCount_ = _config->GetDefaultCitizenCount();
    persistentGameData_.currentWheatBushels_ = _config->GetDefaultWheatBushels();
    persistentGameData_.currentLandAcres_ = _config->GetDefaultLandAcres();

    currentLandPrice_ = 0;
}

int GameData::GetCurrentRound() const {
    return persistentGameData_.currentRound_;
}

void GameData::IncrementCurrentRound() {
    persistentGameData_.currentRound_++;
}

int GameData::GetMaxRound() const {
    return _config->GetMaxRound();
}

int GameData::GetCurrentWheatBushels() const {
    return persistentGameData_.currentWheatBushels_;
}

float GameData::GetLandAcreSowPrice() const {
    return _config->GetDefaultLandAcreSowPrice();
}

int GameData::GetCurrentLandAcres() const {
    return persistentGameData_.currentLandAcres_;
}

void GameData::SetCurrentLandAcres(int currentLandAcres) {
    persistentGameData_.currentLandAcres_ = currentLandAcres;
}

int GameData::GetCurrentCitizenCount() const {
    return persistentGameData_.currentCitizenCount_;
}

int GameData::GetCitizenLandAcresCultivationMaximum() const {
    return _config->GetDefaultCitizenLandAcresCultivationMaximum();
}

void GameData::SetCurrentWheatBushels(int wheatBushels) {
    persistentGameData_.currentWheatBushels_ = wheatBushels;
}

const NumberRange<int> &GameData::GetLandPriceRange() const {
    return _config->GetLandPriceRange();
}

const NumberRange<int> & GameData::GetWheatPerLandAcrePriceRange() const {
    return _config->GetWheatPerLandAcrePriceRange();
}

const NumberRange<float> & GameData::GetRatWheatDamagePercentRange() const {
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
    persistentGameData_.currentCitizenCount_ = newCitizenCount;
}

float GameData::GetMaxPlagueProbability() const {
    return _config->GetMaxPlagueProbability();
}

void GameData::SetPlagueFlag(bool plagueFlag) {
    persistentGameData_.plagueHappenedLastYear_ = plagueFlag;
}

bool GameData::GetPlagueFlag() const {
    return persistentGameData_.plagueHappenedLastYear_;
}

void GameData::SetLoseFlag(bool loseFlag) {
    persistentGameData_.loseFlag_ = loseFlag;
}

bool GameData::GetLoseFlag() const {
    return persistentGameData_.loseFlag_;
}

void GameData::PutStarvedToDeathCountToHistory(int starvedToDeathCount) {
    persistentGameData_.starvedToDeathCountHistory_.push_back(starvedToDeathCount);
}

int GameData::GetStarvedToDeathCountLastYear() const {
    return !persistentGameData_.starvedToDeathCountHistory_.empty()
        ? persistentGameData_.starvedToDeathCountHistory_.back() : 0;
}

void GameData::SetArrivedCitizenCount(int arrivedCitizenCount) {
    persistentGameData_.arrivedCitizenCountLastYear_ = arrivedCitizenCount;
}

int GameData::GetArrivedCitizenCountLastYear() const{
    return persistentGameData_.arrivedCitizenCountLastYear_;
}

void GameData::SetWheatCollected(int wheatCollected, int wheatPerLandAcre) {
    persistentGameData_.wheatCollectedLastYear_ = wheatCollected;
    persistentGameData_.wheatPerLandAcre_ = wheatPerLandAcre;
}

int GameData::GetWheatCollectedLastYear() const {
    return persistentGameData_.wheatCollectedLastYear_;
}

int GameData::GetWheatPerLandAcre() const {
    return persistentGameData_.wheatPerLandAcre_;
}

void GameData::SetWheatEatenByRatsLastYear(int wheatEatenByRats) {
    persistentGameData_.wheatEatenByRatsLastYear_ = wheatEatenByRats;
}

int GameData::GetWheatEatenByRatsLastYear() const {
    return persistentGameData_.wheatEatenByRatsLastYear_;
}
