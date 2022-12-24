#include <stdio.h>
#include "health.h"

void stats_calculate_effective_health(Stats *stats)
{
    int effective_hp;
    int current_hp;
    float average_effective_hp = 0;
    
    for (int damage = stats->armour + 1; damage <= stats->health + stats->armour; ++damage) {
        effective_hp = 0;
        current_hp = stats->health;
        while (current_hp > 0) {
            current_hp -= damage - stats->armour;
            effective_hp += damage;
        }
        average_effective_hp += effective_hp;
    }
    
    stats->effective_hp = average_effective_hp / stats->health;
}

void stats_print(Stats stats)
{
	printf("Stats:\n\tHP: %.1f\n\tAR: %.1f\n\tEHP: %.1f\n", stats.health, stats.armour, stats.effective_hp);
}