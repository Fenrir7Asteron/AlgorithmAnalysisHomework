//
// Created by biore on 10/17/2022.
//

#ifndef LAB1HAMMURABI_PERSISTENTGAMEDATA_H
#define LAB1HAMMURABI_PERSISTENTGAMEDATA_H

#include <vector>

struct PersistentGameData {
    friend class GameData;

    int currentRound_ = 1;
    int currentWheatBushels_ = 0;
    int currentCitizenCount_ = 0;
    int currentLandAcres_ = 0;
    bool plagueHappenedLastYear_ = false;
    bool loseFlag_ = false;
    int arrivedCitizenCountLastYear_ = 0;
    int wheatCollectedLastYear_ = 0;
    int wheatPerLandAcre_ = 0;
    std::vector<int> starvedToDeathCountHistory_;
    int wheatEatenByRatsLastYear_ = 0;
};

#endif //LAB1HAMMURABI_PERSISTENTGAMEDATA_H
