#pragma once
#include <random>

static std::random_device randDev;
static std::mt19937 gen(randDev());

static int RandomNumberInRange(int min, int max)
{
    //static?
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}
