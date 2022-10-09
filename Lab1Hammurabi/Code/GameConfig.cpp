//
// Created by biore on 9/29/2022.
//

#include <fstream>
#include <iostream>
#include "GameConfig.h"

GameConfig::GameConfig(const std::string& pathToGameConfig) {
    ifstream strm;

    strm.open(pathToGameConfig, ios_base::in);

    if (strm.fail()) {
        throw std::system_error{ errno, std::generic_category(), "Could not open file with path: " + pathToGameConfig };
    }

    if (strm.is_open()) {
        string input_parameter;

        while (!strm.eof() && strm >> input_parameter) {
            if (input_parameter == "defaultCitizenCount:") strm >> defaultCitizenCount;

            if (input_parameter == "defaultLandAcres:") strm >> defaultLandAcres;

            if (input_parameter == "defaultWheatBushels:") strm >> defaultWheatBushels;

            if (input_parameter == "defaultLandAcreSowPrice:") strm >> defaultLandAcreSowPrice;

            if (input_parameter == "defaultCitizenWheatConsumePerYear:") strm >> defaultCitizenWheatConsumePerYear;

            if (input_parameter == "defaultCitizenLandAcresCultivationMaximum:") strm >> defaultCitizenLandAcresCultivationMaximum;

            if (input_parameter == "defaultLandPriceRange:") strm >> defaultLandPriceRange;

            if (input_parameter == "maxRoundCount:") strm >> maxRoundCount;
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

int GameConfig::GetDefaultLandAcreSowPrice() const {
    return defaultLandAcreSowPrice;
}

int GameConfig::GetDefaultCitizenWheatConsumePerYear() const {
    return defaultCitizenWheatConsumePerYear;
}

int GameConfig::GetDefaultCitizenLandAcresCultivationMaximum() const {
    return defaultCitizenLandAcresCultivationMaximum;
}

IntRange GameConfig::GetLandPriceRange() const {
    return defaultLandPriceRange;
}
