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
    int currentCitizens;
    int currentLandAcres;

    int maxRound;
    int maxWheatBushels;
    int maxCitizens;
    int maxLandAcres;
public:
    int GetCurrentRound() const;

    void IncrementCurrentRound();

    GameData(const GameConfig config);

    int GetMaxRound() const;

    int GetCurrentWheatBushels() const;
};


#endif //LAB1HAMMURABI_GAMEDATA_H
