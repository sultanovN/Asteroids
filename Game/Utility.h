#pragma once
#include <random>

std::random_device randDev;
std::mt19937 gen(randDev());

int RandomNumberInRange(int min, int max)
{
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}
