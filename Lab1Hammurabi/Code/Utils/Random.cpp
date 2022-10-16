//
// Created by biore on 10/16/2022.
//

#include <iostream>
#include "Random.h"

std::mt19937 Random::random_;
bool Random::inited_ = false;

void Random::Init() {
    std::random_device dev;
    random_.seed(dev());

    inited_ = true;
}

int Random::GetRandomInRange(int start, int end) {
    if (!inited_)
        Init();

    std::uniform_int_distribution<int> dist(start, end);
    return dist(random_);
}

float Random::GetRandomInRange(float start, float end) {
    if (!inited_)
        Init();

    std::uniform_real_distribution<float> dist(start, end);
    return dist(random_);
}
