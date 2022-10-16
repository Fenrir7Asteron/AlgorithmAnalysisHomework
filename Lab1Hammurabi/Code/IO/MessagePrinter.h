//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_MESSAGEPRINTER_H
#define LAB1HAMMURABI_MESSAGEPRINTER_H

#include <iostream>
#include <cstdio>
#include <fcntl.h>
#include "Code/GameData.h"

class MessagePrinter {
private:
    static void PrintGreeting();
    static void PrintYear(int year);

public:
    MessagePrinter() {
        _setmode(_fileno(stdout), _O_U16TEXT);
    }

    void PrintRoundStartSummary(GameData data);

    void PrintQuestionHowMuchLandToBuy();

    void PrintQuestionHowMuchWheatToEat();

    void PrintQuestionHowMuchLandToSow();

    void PrintWheatSummary(GameData data);

    void PrintCitizensSummary(GameData data);

    void PrintLandSummary(GameData data);

    void PrintEndSummary();

    void PrintWrongInputReply(GameData data);

    void PrintQuestionHowMuchLandToSell();

    void PrintGameOverMessage(GameData &data);
};


#endif //LAB1HAMMURABI_MESSAGEPRINTER_H
