//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_GAMEDATA_H
#define LAB1HAMMURABI_GAMEDATA_H


#include "GameConfig.h"

class GameData {
private:
    int currentRound_;
    int currentWheatBushels_;
    int currentCitizenCount_;
    int currentLandAcres_;
    int currentLandPrice_;
    bool plagueFlag_;
    bool loseFlag_;

    const GameConfig* _config = nullptr;
public:
    int GetCurrentRound() const;

    void IncrementCurrentRound();

    GameData(const GameConfig& config);

    int GetMaxRound() const;

    int GetCurrentWheatBushels() const;

    int GetLandAcreSowPrice() const;

    int GetCurrentLandAcres() const;

    int GetCurrentCitizenCount() const;

    int GetCitizenLandAcresCultivationMaximum() const;

    const NumberRange<int> & GetLandPriceRange() const;

    void SetCurrentWheatBushels(int wheatBushels);

    const NumberRange<int> & GetWheatPerLandAcrePriceRange();

    const NumberRange<float> & GetRatWheatDamagePercentRange();

    void SetLandPrice(int landPrice);

    int GetCurrentLandPrice() const;

    int GetWheatNeededForPersonPerYear() const;

    void SetCurrentCitizenCount(int newCitizenCount);

    float GetMaxPlagueProbability() const;

    void SetPlagueFlag(bool plagueFlag);

    void SetLoseFlag(bool loseFlag);

    bool GetLoseFlag() const;
};


#endif //LAB1HAMMURABI_GAMEDATA_H
