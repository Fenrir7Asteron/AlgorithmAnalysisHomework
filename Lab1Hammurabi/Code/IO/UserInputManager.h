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
    template<typename T>
    std::experimental::optional<T> StringTo(const string &s);

    void ReadInput(MessagePrinter& printer, RoundInput &roundInput);
    int ReadInt();

public:
    RoundInput GetRoundInput(MessagePrinter printer, GameData gameData);

    bool CorrectRoundInput(RoundInput& input, GameData gameData);
};


#endif //LAB1HAMMURABI_USERINPUTMANAGER_H
