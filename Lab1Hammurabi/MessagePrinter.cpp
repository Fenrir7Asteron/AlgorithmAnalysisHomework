//
// Created by biore on 9/29/2022.
//

#include "MessagePrinter.h"

using namespace std;

void MessagePrinter::PrintRoundStartSummary(GameData data) {
    PrintGreeting();
    PrintYear(data.GetCurrentRound());
}

void MessagePrinter::PrintGreeting() {
    wcout << L"Мой повелитель, соизволь поведать тебе" << endl;
}

void MessagePrinter::PrintYear(int year) {
    wprintf(L"\tв году %d твоего высочайшего правления\n", year);
}
