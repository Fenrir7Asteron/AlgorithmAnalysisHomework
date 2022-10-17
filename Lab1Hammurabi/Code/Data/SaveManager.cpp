//
// Created by biore on 10/17/2022.
//

#include <iostream>
#include <iomanip>
#include "SaveManager.h"
#include "Code/IO/UserInputManager.h"

void SaveManager::Load(GameData &data, const string &pathToSaveFile) {
    ifstream strm;

    strm.open(pathToSaveFile, ios_base::in);

    if (strm.fail()) {
        return;
    }

    if (strm.is_open()) {
        string inputParameter;

        strm >> inputParameter;
        if (inputParameter == "saveDatetime:") {
            string saveDatetime;
            strm >> saveDatetime;

            if (!UserInputManager::ReadLoadInput(saveDatetime))
                return;
        } else {
            return;
        }

        PersistentGameData &persistentData = data.GetPersistentData();

        while (!strm.eof() && strm >> inputParameter) {
            if (inputParameter == "currentRound:") strm >> persistentData.currentRound_;
            if (inputParameter == "currentWheatBushels:") strm >> persistentData.currentWheatBushels_;
            if (inputParameter == "currentCitizenCount:") strm >> persistentData.currentCitizenCount_;
            if (inputParameter == "currentLandAcres:") strm >> persistentData.currentLandAcres_;
            if (inputParameter == "plagueHappenedLastYear:") strm >> persistentData.plagueHappenedLastYear_;
            if (inputParameter == "arrivedCitizenCountLastYear:") strm >> persistentData.arrivedCitizenCountLastYear_;
            if (inputParameter == "wheatCollectedLastYear:") strm >> persistentData.wheatCollectedLastYear_;
            if (inputParameter == "wheatPerLandAcre:") strm >> persistentData.wheatPerLandAcre_;
            if (inputParameter == "starvedToDeathCountLastYear:") strm >> persistentData.starvedToDeathCountLastYear_;
            if (inputParameter == "starvedToDeathPercentAccumulated:") strm >> persistentData.starvedToDeathPercentAccumulated_;
            if (inputParameter == "wheatEatenByRatsLastYear:") strm >> persistentData.wheatEatenByRatsLastYear_;
        }

        strm.close();
    }
}

void SaveManager::Save(GameData &data, const string &pathToSaveFile) {
    ofstream strm;

    strm.open(pathToSaveFile, ios_base::out);

    if (strm.fail()) {
        throw std::system_error{ errno, std::generic_category(), "Could not open file with path: " + pathToSaveFile };
    }

    if (strm.is_open()) {

        const PersistentGameData &persistentData = data.GetPersistentData();

        // Save current date as header
        time_t t = time(nullptr);
        tm tm = *localtime(&t);
        strm << "saveDatetime: " << put_time(&tm, "%Y-%m-%d|%H:%M:%S") << endl;

        // Save persistent game data
        strm << "currentRound: " << persistentData.currentRound_ << endl;
        strm << "currentWheatBushels: " << persistentData.currentWheatBushels_ << endl;
        strm << "currentCitizenCount: " << persistentData.currentCitizenCount_ << endl;
        strm << "currentLandAcres: " << persistentData.currentLandAcres_ << endl;
        strm << "plagueHappenedLastYear: " << persistentData.plagueHappenedLastYear_ << endl;
        strm << "arrivedCitizenCountLastYear: " << persistentData.arrivedCitizenCountLastYear_ << endl;
        strm << "wheatCollectedLastYear: " << persistentData.wheatCollectedLastYear_ << endl;
        strm << "wheatPerLandAcre: " << persistentData.wheatPerLandAcre_ << endl;
        strm << "starvedToDeathCountLastYear: " << persistentData.starvedToDeathCountLastYear_ << endl;
        strm << "starvedToDeathPercentAccumulated: " << persistentData.starvedToDeathPercentAccumulated_ << endl;
        strm << "wheatEatenByRatsLastYear: " << persistentData.wheatEatenByRatsLastYear_ << endl;

        strm.close();
    }
}

void SaveManager::DeleteSaveFile(const string &pathToSaveFile) {
    std::remove(pathToSaveFile.c_str()); // delete file
}
