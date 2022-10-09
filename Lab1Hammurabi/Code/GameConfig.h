//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_GAMECONFIG_H
#define LAB1HAMMURABI_GAMECONFIG_H

#include <string>
#include "DataStructures/IntRange.h"

using namespace std;

class GameConfig {
private:
    int maxRoundCount = 10;
    int defaultCitizenCount = 100;
    int defaultWheatBushels = 2800;
    int defaultLandAcres = 1000;
    int defaultLandAcreSowPrice = 5;
    int defaultCitizenWheatConsumePerYear = 20;
    int defaultCitizenLandAcresCultivationMaximum = 10;
    IntRange defaultLandPriceRange {17, 26};
public:
    explicit GameConfig(const string& pathToGameConfig);

    int GetDefaultCitizenCount() const;

    int GetDefaultWheatBushels() const;

    int GetDefaultLandAcres() const;

    int GetMaxRound() const;

    int GetDefaultLandAcreSowPrice() const;

    int GetDefaultCitizenWheatConsumePerYear() const;

    int GetDefaultCitizenLandAcresCultivationMaximum() const;

    IntRange GetLandPriceRange() const;
};


#endif //LAB1HAMMURABI_GAMECONFIG_H
