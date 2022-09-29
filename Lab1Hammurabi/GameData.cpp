//
// Created by biore on 9/29/2022.
//

#include "GameData.h"

const int GameData::GetCurrentRound() const {
    return currentRound;
}

void GameData::IncrementCurrentRound() {
    currentRound++;
}
