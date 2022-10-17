//
// Created by biore on 9/29/2022.
//

#include "MessagePrinter.h"

using namespace std;

void MessagePrinter::PrintRoundStartSummary(const GameData& data) {
    PrintGreeting();
    PrintYear(data.GetCurrentRound());
    PrintCitizensSummary(data);
    PrintWheatSummary(data);
    PrintLandSummary(data);

    PrintEndSummary();
}

void MessagePrinter::PrintGreeting() {
    wprintf(L"Мой повелитель, соизволь поведать тебе\n");
}

void MessagePrinter::PrintYear(int year) {
    wprintf(L"В году %d твоего высочайшего правления\n", year);
}

void MessagePrinter::PrintQuestionHowMuchLandToBuy() {
    wprintf(L"Сколько акров земли повелеваешь купить? \n> Повелеваю купить: ");
}

void MessagePrinter::PrintQuestionHowMuchLandToSell() {
    wprintf(L"Сколько акров земли повелеваешь продать? \n> Повелеваю продать: ");
}

void MessagePrinter::PrintQuestionHowMuchWheatToEat() {
    wprintf(L"Сколько бушелей пшеницы повелеваешь съесть? \n> Повелеваю съесть: ");
}

void MessagePrinter::PrintQuestionHowMuchLandToSow() {
    wprintf(L"Сколько акров земли повелеваешь засеять? \n> Повелеваю засеять: ");
}

void MessagePrinter::PrintWheatSummary(const GameData& data) {
    int wheatCollectedLastYear = data.GetWheatCollectedLastYear();
    int wheatEatenByRatsLastYear = data.GetWheatEatenByRatsLastYear();
    if (wheatCollectedLastYear > 0) {
        wprintf(L"Мы собрали %d бушелей пшеницы, по %d бушеля с акра\n", wheatCollectedLastYear, data.GetWheatPerLandAcre());
    }

    int currentWheatBushels = data.GetCurrentWheatBushels();

    if (wheatEatenByRatsLastYear > 0) {
        wprintf(L"Крысы истребили %d бушелей пшеницы, оставив %d бушеля в амбарах\n", wheatEatenByRatsLastYear, currentWheatBushels);
    } else {
        wprintf(L"В амбарах имеется %d бушелей пшеницы\n", currentWheatBushels);
    }
}

void MessagePrinter::PrintCitizensSummary(const GameData& data) {
    int starvedToDeathCountLastYear = data.GetStarvedToDeathCountLastYear();
    int arrivedCitizenCountLastYear = data.GetArrivedCitizenCountLastYear();

    if (starvedToDeathCountLastYear > 0) {
        wprintf(L"%d человек умерли с голоду", starvedToDeathCountLastYear);

        if (arrivedCitizenCountLastYear > 0) {
            wprintf(L", и %d человек прибыли в наш великий город", arrivedCitizenCountLastYear);
        }

        wprintf(L"\n");
    } else if (arrivedCitizenCountLastYear > 0) {
        wprintf(L"%d человек прибыли в наш великий город\n", arrivedCitizenCountLastYear);
    }

    if (data.GetPlagueFlag()) {
        wprintf(L"Чума уничтожила половину населения\n");
    }

    wprintf(L"Население города сейчас составляет %d человек\n", data.GetCurrentCitizenCount());
}

void MessagePrinter::PrintLandSummary(const GameData& data) {
    wprintf(L"Город сейчас занимает %d акров\n", data.GetCurrentLandAcres());
    wprintf(L"1 акр земли стоит сейчас %d бушель\n", data.GetCurrentLandPrice());
}

void MessagePrinter::PrintEndSummary() {
    wprintf(L"-------------------\n");
}

void MessagePrinter::PrintWrongInputReply(const GameData& data) {
    wprintf(L"О, повелитель, пощади нас! У нас только %d человек, %d бушелей пшеницы и %d\n"
            "акров земли!\n", data.GetCurrentCitizenCount(), data.GetCurrentWheatBushels(), data.GetCurrentLandAcres());
}

void MessagePrinter::PrintGameOverMessage(const GameData &data) {
    if (data.GetLoseFlag()) {
        wprintf(L"******------------******\n"
                "Из-за вашей некомпетентности в "
                "управлении, народ устроил бунт, и изгнал вас их города. Теперь вы "
                "вынуждены влачить жалкое существование в изгнании\n"
                "******------------******\n");
    } else {
        wprintf(L"******------------******\n"
                "Фантастика! Карл Великий, "
                "Дизраэли и Джефферсон вместе не справились бы лучше\n"
                "******------------******\n");
    }
}
