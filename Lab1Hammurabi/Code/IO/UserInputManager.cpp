//
// Created by biore on 10/1/2022.
//

#include <sstream>
#include "UserInputManager.h"

RoundInput UserInputManager::GetRoundInput(MessagePrinter printer, GameData gameData) {
    RoundInput roundInput;
    bool isInputCorrect;

    do {
        ReadInput(printer, roundInput);

        isInputCorrect = CorrectRoundInput(roundInput, gameData);

        if (!isInputCorrect) {
            printer.PrintWrongInputReply(gameData);
        }

    } while (!isInputCorrect);

    return roundInput;
}

void UserInputManager::ReadInput(MessagePrinter& printer, RoundInput &roundInput) {
    printer.PrintQuestionHowMuchLandToBuy();
    roundInput.landAcresToBuy = ReadInt();

    printer.PrintQuestionHowMuchLandToSell();
    roundInput.landAcresToSell = ReadInt();

    printer.PrintQuestionHowMuchWheatToEat();
    roundInput.wheatBushelsToEat = ReadInt();

    printer.PrintQuestionHowMuchLandToSow();
    roundInput.landAcresToSow = ReadInt();
}

int UserInputManager::ReadInt() {
    string s;
    getline( cin, s );
    auto input = StringTo<int>(s);
    return input ? input.value() : -1;
}

bool UserInputManager::CorrectRoundInput(RoundInput& input, GameData gameData) {
    int requiredWheatBushels = input.landAcresToBuy * gameData.GetCurrentLandPrice()
            + input.wheatBushelsToEat
            + input.landAcresToSow * gameData.GetLandAcreSowPrice();

    if (requiredWheatBushels > gameData.GetCurrentWheatBushels()
        || input.landAcresToSow > gameData.GetCurrentLandAcres() + input.landAcresToBuy
        || input.landAcresToSow > gameData.GetCurrentCitizenCount() * gameData.GetCitizenLandAcresCultivationMaximum()) {
        return false;
    }

    if (input.landAcresToBuy < 0 || input.wheatBushelsToEat < 0 || input.landAcresToSow < 0) {
        return false;
    }

    return true;
}

template <typename T>
std::experimental::optional <T> UserInputManager::StringTo(const std::string& s )
{
    std::istringstream ss( s );
    T result;
    ss >> result >> std::ws;      // attempt the conversion
    if (ss.eof()) return result;  // success
    return {};                    // failure
}
