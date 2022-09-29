//
// Created by biore on 9/29/2022.
//

#ifndef LAB1HAMMURABI_GAMEDATA_H
#define LAB1HAMMURABI_GAMEDATA_H


class GameData {
private:
    int currentRound = 1;
public:
    const int GetCurrentRound() const;

    void IncrementCurrentRound();
};


#endif //LAB1HAMMURABI_GAMEDATA_H
