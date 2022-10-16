//
// Created by biore on 10/16/2022.
//

#ifndef LAB1HAMMURABI_RANDOM_H
#define LAB1HAMMURABI_RANDOM_H

#include <random>
#include <ctime>

class Random {
private:
    static std::mt19937 random_;
    static bool inited_;

public:
    static void Init();

    static int GetRandomInRange(int start, int end);

    static float GetRandomInRange(float start, float end);
};


#endif //LAB1HAMMURABI_RANDOM_H
