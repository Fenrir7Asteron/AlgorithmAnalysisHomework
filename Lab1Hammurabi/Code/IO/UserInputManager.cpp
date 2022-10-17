//
// Created by biore on 10/1/2022.
//

#include <sstream>
#include "UserInputManager.h"

RoundInput UserInputManager::GetRoundInput(GameData gameData) {
    RoundInput roundInput;
    bool isInputCorrect;

    do {
        ReadRoundInput(roundInput);

        isInputCorrect = CorrectRoundInput(roundInput, gameData);

        if (!isInputCorrect) {
            MessagePrinter::PrintWrongInputReply(gameData);
        }

    } while (!isInputCorrect);

    return roundInput;
}

void UserInputManager::ReadRoundInput(RoundInput &roundInput) {
    MessagePrinter::PrintQuestionHowMuchLandToBuy();
    roundInput.landAcresToBuy = ReadInt();

    MessagePrinter::PrintQuestionHowMuchLandToSell();
    roundInput.landAcresToSell = ReadInt();

    MessagePrinter::PrintQuestionHowMuchWheatToEat();
    roundInput.wheatBushelsToEat = ReadInt();

    MessagePrinter::PrintQuestionHowMuchLandToSow();
    roundInput.landAcresToSow = ReadInt();
}

bool UserInputManager::ReadLoadInput(string &lastSaveDatetime) {
    string answer;

    while (answer != "y" && answer != "n") {
        MessagePrinter::PrintQuestionLoadGame(lastSaveDatetime);
        cin >> answer;
    }

    cin.ignore();

    return answer == "y";
}

bool UserInputManager::ReadGameExitInput() {
    string answer;

    while (answer != "y" && answer != "n") {
        MessagePrinter::PrintQuestionGameExit();
        cin >> answer;
    }

    cin.ignore();

    return answer == "y";
}

int UserInputManager::ReadInt() {
    string s;
    getline( cin, s );
    auto input = StringToInt(s);
    return input ? input.value() : -1;
}

bool UserInputManager::CorrectRoundInput(RoundInput& input, GameData gameData) {
    int requiredWheatBushels = input.landAcresToBuy * gameData.GetCurrentLandPrice()
            + input.wheatBushelsToEat
            + input.landAcresToSow * gameData.GetLandAcreSowPrice();

    if (requiredWheatBushels > gameData.GetCurrentWheatBushels()
        || input.landAcresToSow > gameData.GetCurrentLandAcres() + input.landAcresToBuy - input.landAcresToSell
        || input.landAcresToSow > gameData.GetCurrentCitizenCount() * gameData.GetCitizenLandAcresCultivationMaximum()) {
        return false;
    }

    if (input.landAcresToBuy < 0 || input.wheatBushelsToEat < 0 || input.landAcresToSow < 0) {
        return false;
    }

    return true;
}

std::experimental::optional<int> UserInputManager::StringToInt(const std::string& s )
{
    std::istringstream ss( s );
    int result;
    ss >> result >> std::ws;      // attempt the conversion
    if (ss.eof()) return result;  // success
    return {};                    // failure
}
