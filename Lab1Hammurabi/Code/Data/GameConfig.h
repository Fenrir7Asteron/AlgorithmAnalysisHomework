//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_GAMECONFIG_H
#define LAB1HAMMURABI_GAMECONFIG_H

#include <string>
#include "Code/DataStructures/NumberRange.h"

using namespace std;

class GameConfig {
private:
    int maxRoundCount = 10;
    int defaultCitizenCount = 100;
    int defaultWheatBushels = 2800;
    int defaultLandAcres = 1000;
    float defaultLandAcreSowPrice = 0.5f;
    int defaultCitizenWheatConsumePerYear = 20;
    int defaultCitizenLandAcresCultivationMaximum = 10;
    int defaultWheatNeededForPersonPerYear = 20;
    float defaultMaxPlagueProbability = 0.15f;
    NumberRange<int> defaultLandPriceRange {17, 26};
    NumberRange<int> defaultWheatPerLandAcre {1, 6};
    NumberRange<float> defaultRatWheatDamagePercentRange {0.0f, 0.07f};
public:
    explicit GameConfig(const string& pathToGameConfig);

    int GetDefaultCitizenCount() const;

    int GetDefaultWheatBushels() const;

    int GetDefaultLandAcres() const;

    int GetMaxRound() const;

    float GetDefaultLandAcreSowPrice() const;

    int GetDefaultCitizenWheatConsumePerYear() const;

    int GetDefaultCitizenLandAcresCultivationMaximum() const;

    const NumberRange<int> & GetLandPriceRange() const;

    const NumberRange<int> & GetWheatPerLandAcrePriceRange() const;

    const NumberRange<float> & GetRatWheatDamagePercentRange() const;

    int GetWheatNeededForPersonPerYear() const;

    float GetMaxPlagueProbability();

    float GetMaxPlagueProbability() const;
};


#endif //LAB1HAMMURABI_GAMECONFIG_H
