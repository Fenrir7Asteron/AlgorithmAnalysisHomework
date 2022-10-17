//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_MESSAGEPRINTER_H
#define LAB1HAMMURABI_MESSAGEPRINTER_H

#include <iostream>
#include <cstdio>
#include <fcntl.h>
#include "Code/Data/GameData.h"

class MessagePrinter {
private:
    static void PrintGreeting();
    static void PrintYear(int year);

public:
    static void PrintRoundStartSummary(const GameData& data);

    static void PrintQuestionHowMuchLandToBuy();

    static void PrintQuestionHowMuchWheatToEat();

    static void PrintQuestionHowMuchLandToSow();

    static void PrintWheatSummary(const GameData& data);

    static void PrintCitizensSummary(const GameData& data);

    static void PrintLandSummary(const GameData& data);

    static void PrintEndSummary();

    static void PrintWrongInputReply(const GameData& data);

    static void PrintQuestionHowMuchLandToSell();

    static void PrintGameOverMessage(const GameData &data);

    static void PrintQuestionLoadGame(string &lastSaveDatetime);

    static void PrintQuestionGameExit();

    static const wstring & SelectCountBasedWord(int count, const wstring& wordSingle, const wstring& wordSeveral, const wstring& wordMany);
};


#endif //LAB1HAMMURABI_MESSAGEPRINTER_H
