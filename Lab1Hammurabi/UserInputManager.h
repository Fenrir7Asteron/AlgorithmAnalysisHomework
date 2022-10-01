//
// Created by biore on 10/1/2022.
//

#ifndef LAB1HAMMURABI_USERINPUTMANAGER_H
#define LAB1HAMMURABI_USERINPUTMANAGER_H


#include "MessagePrinter.h"

class UserInputManager {

public:
    void GetRoundInput(MessagePrinter printer, GameData gameData);

    bool CorrectRoundInput(int landAcresToBuy, int wheatBushelsToEat, int landAcresToSow, GameData gameData);
};


#endif //LAB1HAMMURABI_USERINPUTMANAGER_H
