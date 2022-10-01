//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_GAMECONFIG_H
#define LAB1HAMMURABI_GAMECONFIG_H

#include <string>

using namespace std;

class GameConfig {
private:
    int defaultCitizenCount = 100;
    int defaultWheatBushels = 2800;
    int defaultLandAcres = 1000;
    int maxRoundCount = 10;
public:
    explicit GameConfig(const string& pathToGameConfig);

    int GetDefaultCitizenCount() const;

    int GetDefaultWheatBushels() const;

    int GetDefaultLandAcres() const;

    int GetMaxRound() const;
};


#endif //LAB1HAMMURABI_GAMECONFIG_H
