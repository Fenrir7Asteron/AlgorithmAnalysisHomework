//
// Created by biore on 10/1/2022.
//

#include "UserInputManager.h"

void UserInputManager::GetRoundInput(MessagePrinter printer, GameData gameData) {
    int landAcresToBuy = -1;
    int wheatBushelsToEat = -1;
    int landAcresToSow = -1;

    do {
        break;
    } while (!CorrectRoundInput(landAcresToBuy, wheatBushelsToEat, landAcresToSow, gameData));
}

bool UserInputManager::CorrectRoundInput(int landAcresToBuy, int wheatBushelsToEat, int landAcresToSow, GameData gameData) {
    return true;
}
