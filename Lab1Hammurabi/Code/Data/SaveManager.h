//
// Created by biore on 10/17/2022.
//

#ifndef LAB1HAMMURABI_SAVEMANAGER_H
#define LAB1HAMMURABI_SAVEMANAGER_H


#include "GameData.h"

class SaveManager {
public:
    static void Load(GameData &data, const string &pathToSaveFile);

    static void Save(GameData &data, const string &pathToSaveFile);

    static void DeleteSaveFile(const string &pathToSaveFile);
};


#endif //LAB1HAMMURABI_SAVEMANAGER_H
