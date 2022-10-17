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
    wprintf(L"Мой повелитель, соизвольте поведать вам\n");
}

void MessagePrinter::PrintYear(int year) {
    wprintf(L"В году %d вашего высочайшего правления\n", year);
}

void MessagePrinter::PrintQuestionHowMuchLandToBuy() {
    wprintf(L"Сколько акров земли повелеваете купить? \n> Повелеваю купить: ");
}

void MessagePrinter::PrintQuestionHowMuchLandToSell() {
    wprintf(L"Сколько акров земли повелеваете продать? \n> Повелеваю продать: ");
}

void MessagePrinter::PrintQuestionHowMuchWheatToEat() {
    wprintf(L"Сколько бушелей пшеницы повелеваете съесть? \n> Повелеваю съесть: ");
}

void MessagePrinter::PrintQuestionHowMuchLandToSow() {
    wprintf(L"Сколько акров земли повелеваете засеять? \n> Повелеваю засеять: ");
}

void MessagePrinter::PrintQuestionLoadGame(string &lastSaveDatetime) {
    wprintf(L"Найден файл сохранения с предыдущей игры [%s].\nХотите его загрузить? [y - загрузить/n - начать игру заново]: ", lastSaveDatetime.c_str());
}

void MessagePrinter::PrintQuestionGameExit() {
    wprintf(L"Будет исполнено, мой повелитель. Хотите ли вы отправиться отдыхать? [y - закрыть игру/n - продолжить игру]: ");
}

void MessagePrinter::PrintWheatSummary(const GameData& data) {
    int wheatCollectedLastYear = data.GetWheatCollectedLastYear();
    int wheatEatenByRatsLastYear = data.GetWheatEatenByRatsLastYear();
    if (wheatCollectedLastYear > 0) {
        int wheatPerLandAcre = data.GetWheatPerLandAcre();

        wprintf(L"Мы собрали %d %ls пшеницы, по %d %ls с акра\n",
                wheatCollectedLastYear, SelectCountBasedWord(wheatCollectedLastYear, L"бушель", L"бушеля", L"бушелей").c_str(),
                wheatPerLandAcre, SelectCountBasedWord(wheatPerLandAcre, L"бушель", L"бушеля", L"бушелей").c_str());
    }

    int currentWheatBushels = data.GetCurrentWheatBushels();

    if (wheatEatenByRatsLastYear > 0) {
        wprintf(L"Крысы истребили %d %ls пшеницы, оставив %d %ls в амбарах\n",
                wheatEatenByRatsLastYear, SelectCountBasedWord(wheatEatenByRatsLastYear, L"бушель", L"бушеля", L"бушелей").c_str(),
                currentWheatBushels, SelectCountBasedWord(currentWheatBushels, L"бушель", L"бушеля", L"бушелей").c_str());
    } else {
        wprintf(L"В амбарах имеется %d %ls пшеницы\n",
                currentWheatBushels, SelectCountBasedWord(currentWheatBushels, L"бушель", L"бушеля", L"бушелей").c_str());
    }
}

void MessagePrinter::PrintCitizensSummary(const GameData& data) {
    int starvedToDeathCountLastYear = data.GetStarvedToDeathCountLastYear();
    int arrivedCitizenCountLastYear = data.GetArrivedCitizenCountLastYear();

    if (starvedToDeathCountLastYear > 0) {
        wprintf(L"%d %ls умерли с голоду", 
                starvedToDeathCountLastYear, SelectCountBasedWord(starvedToDeathCountLastYear, L"человек", L"человека", L"человек").c_str()
                );

        if (arrivedCitizenCountLastYear > 0) {
            wprintf(L", и %d %ls прибыли в наш великий город", 
                    arrivedCitizenCountLastYear, SelectCountBasedWord(arrivedCitizenCountLastYear, L"человек", L"человека", L"человек").c_str());
        }

        wprintf(L"\n");
    } else if (arrivedCitizenCountLastYear > 0) {
        wprintf(L"%d %ls прибыли в наш великий город\n", 
                arrivedCitizenCountLastYear, SelectCountBasedWord(arrivedCitizenCountLastYear, L"человек", L"человека", L"человек").c_str());
    }

    if (data.GetPlagueFlag()) {
        wprintf(L"Чума уничтожила половину населения\n");
    }

    int currentCitizenCount = data.GetCurrentCitizenCount();
    wprintf(L"Население города сейчас составляет %d %ls\n",
            currentCitizenCount, SelectCountBasedWord(currentCitizenCount, L"человек", L"человека", L"человек").c_str());
}

void MessagePrinter::PrintLandSummary(const GameData& data) {
    int currentLandAcres = data.GetCurrentLandAcres();
    int currentLandPrice = data.GetCurrentLandPrice();
    wprintf(L"Город сейчас занимает %d %ls\n", 
            currentLandAcres, SelectCountBasedWord(currentLandAcres, L"акр", L"акра", L"акров").c_str());
    wprintf(L"1 акр земли стоит сейчас %d %ls\n",
            currentLandPrice, SelectCountBasedWord(currentLandPrice, L"бушель", L"бушеля", L"бушелей").c_str());
}

void MessagePrinter::PrintEndSummary() {
    wprintf(L"-------------------\n");
}

void MessagePrinter::PrintWrongInputReply(const GameData& data) {
    int currentCitizenCount = data.GetCurrentCitizenCount();
    int currentWheatBushels = data.GetCurrentWheatBushels();
    wprintf(L"О, повелитель, пощадите нас! У нас только %d %ls, %d %ls пшеницы и %d %ls земли!\n",
            currentCitizenCount, SelectCountBasedWord(currentCitizenCount, L"человек", L"человека", L"человек").c_str(),
            currentWheatBushels, SelectCountBasedWord(currentWheatBushels, L"бушель", L"бушеля", L"бушелей").c_str(),
            data.GetCurrentLandAcres(), SelectCountBasedWord(currentWheatBushels, L"акр", L"акра", L"акров").c_str());
}

void MessagePrinter::PrintGameOverMessage(const GameData &data) {
    float averageStarvedToDeathPercent = data.GetAverageStarvedToDeathPercent();

    int currentCitizenCount = data.GetCurrentCitizenCount();
    float landAcresPerCitizen = currentCitizenCount > 0
            ? ((float) data.GetCurrentLandAcres() / (float) currentCitizenCount) : 0;

    if (data.GetLoseFlag() || (averageStarvedToDeathPercent > 0.33f && landAcresPerCitizen < 7.0f)) {
        wprintf(L"******------------******\n"
                "Из-за вашей некомпетентности в "
                "управлении, народ устроил бунт, и изгнал вас их города. Теперь вы "
                "вынуждены влачить жалкое существование в изгнании.\n"
                "******------------******\n");
    } else if (averageStarvedToDeathPercent > 0.1f && landAcresPerCitizen < 9.0f) {
        wprintf(L"******------------******\n"
                "Вы правили железной "
                "рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с "
                "облегчением, и никто больше не желает видеть вас правителем.\n"
                "******------------******\n");
    } else if (averageStarvedToDeathPercent > 0.03f && landAcresPerCitizen < 10.0f) {
        wprintf(L"******------------******\n"
                "Вы справились вполне неплохо, у вас, "
                "конечно, есть недоброжелатели, но многие хотели бы увидеть вас во "
                "главе города снова.\n"
                "******------------******\n");
    } else {
        wprintf(L"******------------******\n"
                "Фантастика! Карл Великий, "
                "Дизраэли и Джефферсон вместе не справились бы лучше.\n"
                "******------------******\n");
    }
}

const wstring &MessagePrinter::SelectCountBasedWord(int count, const wstring& wordSingle, const wstring& wordSeveral,
                                           const wstring& wordMany) {
    if (count == 1)
        return wordSingle;
    else if (count >= 2 && count <= 4)
        return wordSeveral;
    else
        return wordMany;
}
