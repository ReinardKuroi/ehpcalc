#include "health.h"

double calculate_effective_health(int health, int armour)
{
    int effective_hp;
    int current_hp;
    double average_effective_hp = 0;
    
    for (int damage = armour + 1; damage <= health + armour; ++damage) {
        effective_hp = 0;
        current_hp = health;
        while (current_hp > 0) {
            current_hp -= damage - armour;
            effective_hp += damage;
        }
        average_effective_hp += effective_hp;
    }
    
    return average_effective_hp / health;
}