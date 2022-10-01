//
// Created by biore on 9/29/2022.
//

#include <fstream>
#include <iostream>
#include "GameConfig.h"

GameConfig::GameConfig(const std::string& pathToGameConfig) {
    fstream strm;

    strm.open(pathToGameConfig, ios_base::in);

    if (strm.fail()) {
        throw std::system_error{ errno, std::generic_category(), "Could not open file with path: " + pathToGameConfig };
    }

    if (strm.is_open()) {
        string input_parameter;

        while (!strm.eof() && strm >> input_parameter) {
            if (input_parameter == "defaultCitizenCount:") {
                strm >> defaultCitizenCount;
            }

            if (input_parameter == "defaultLandAcres:") {
                strm >> defaultLandAcres;
            }

            if (input_parameter == "defaultWheatBushels:") {
                strm >> defaultWheatBushels;
            }

            if (input_parameter == "maxRoundCount:") {
                strm >> maxRoundCount;
            }

            cout << input_parameter << endl;
        }

        strm.close();
    }
}

int GameConfig::GetDefaultCitizenCount() const {
    return defaultCitizenCount;
}

int GameConfig::GetDefaultWheatBushels() const {
    return defaultWheatBushels;
}

int GameConfig::GetDefaultLandAcres() const {
    return defaultLandAcres;
}

int GameConfig::GetMaxRound() const {
    return maxRoundCount;
}
