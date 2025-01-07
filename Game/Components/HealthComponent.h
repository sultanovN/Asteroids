#pragma once
#include "../Utility.h"

class HealthComponent
{
private:
    int8_t Health;
    bool isAlive = true;
    std::chrono::steady_clock::time_point colorTime;



public:
    HealthComponent(int8_t Health = 3)
        :Health(Health)
    {
    }

    int8_t GetHealth()const { return Health; }

    //Heal+, Damage-, or NewHealth
    void SetHealth(int8_t NewHealth) { Health = NewHealth; }

    void TakeDamage(int8_t Damage)
    {
        Health -= Damage;

    }
};