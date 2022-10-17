//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_GAMEDATA_H
#define LAB1HAMMURABI_GAMEDATA_H


#include "GameConfig.h"
#include "PersistentGameData.h"

class GameData {
private:
    PersistentGameData persistentGameData_;
    int currentLandPrice_;

    const GameConfig* _config = nullptr;
public:
    int GetCurrentRound() const;

    void IncrementCurrentRound();

    GameData(const GameConfig& config);

    int GetMaxRound() const;

    int GetCurrentWheatBushels() const;

    float GetLandAcreSowPrice() const;

    int GetCurrentLandAcres() const;

    int GetCurrentCitizenCount() const;

    int GetCitizenLandAcresCultivationMaximum() const;

    const NumberRange<int> & GetLandPriceRange() const;

    void SetCurrentWheatBushels(int wheatBushels);

    const NumberRange<int> & GetWheatPerLandAcrePriceRange() const;

    const NumberRange<float> & GetRatWheatDamagePercentRange() const;

    void SetLandPrice(int landPrice);

    int GetCurrentLandPrice() const;

    int GetWheatNeededForPersonPerYear() const;

    void SetCurrentCitizenCount(int newCitizenCount);

    float GetMaxPlagueProbability() const;

    void SetPlagueFlag(bool plagueFlag);

    void SetLoseFlag(bool loseFlag);

    bool GetLoseFlag() const;

    void PutStarvedToDeathCountToHistory(int starvedToDeathCount);

    void SetArrivedCitizenCount(int arrivedCitizenCount);

    void SetWheatCollected(int wheatCollected, int wheatPerLandAcre);

    int GetWheatCollectedLastYear() const;

    int GetWheatPerLandAcre() const;

    void SetWheatEatenByRatsLastYear(int wheatEatenByRats);

    int GetWheatEatenByRatsLastYear() const;

    int GetArrivedCitizenCountLastYear() const;

    int GetStarvedToDeathCountLastYear() const;

    bool GetPlagueFlag() const;

    void SetCurrentLandAcres(int currentLandAcres);
};


#endif //LAB1HAMMURABI_GAMEDATA_H
