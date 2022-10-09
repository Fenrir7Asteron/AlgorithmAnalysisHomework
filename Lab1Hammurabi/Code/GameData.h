//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_GAMEDATA_H
#define LAB1HAMMURABI_GAMEDATA_H


#include "GameConfig.h"

class GameData {
private:
    int currentRound;
    int currentWheatBushels;
    int currentCitizenCount;
    int currentLandAcres;

    int currentLandPrice;

    int maxRound;
    int maxWheatBushels;
    int maxCitizens;
    int maxLandAcres;

    const GameConfig* _config = nullptr;
public:
    int GetCurrentRound() const;

    void IncrementCurrentRound();

    GameData(const GameConfig& config);

    int GetMaxRound() const;

    int GetCurrentWheatBushels() const;

    int GetCurrentLandPrice() const;

    int GetLandAcreSowPrice() const;

    int GetCurrentLandAcres() const;

    int GetCurrentCitizenCount() const;

    int GetCitizenLandAcresCultivationMaximum() const;
};


#endif //LAB1HAMMURABI_GAMEDATA_H
