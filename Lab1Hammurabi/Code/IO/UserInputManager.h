//
// Created by biore on 10/1/2022.
//

#ifndef LAB1HAMMURABI_USERINPUTMANAGER_H
#define LAB1HAMMURABI_USERINPUTMANAGER_H


#include "MessagePrinter.h"
#include "Code/DataStructures/RoundInput.h"
#include <experimental/optional>

class UserInputManager {
private:
    static std::experimental::optional<int> StringToInt(const std::string& s );

    static void ReadRoundInput(RoundInput &roundInput);
    static int ReadInt();

public:
    static RoundInput GetRoundInput(GameData gameData);

    static bool CorrectRoundInput(RoundInput& input, GameData gameData);

    static bool ReadLoadInput(string &lastSaveDatetime);

    static bool ReadGameExitInput();
};


#endif //LAB1HAMMURABI_USERINPUTMANAGER_H
