#ifndef HEALTH_INCLUDED
#define HEALTH_INCLUDED

typedef struct {
	float health;
	float armour;
	float effective_hp;
} Stats;

void stats_calculate_effective_health(Stats *stats);

void stats_print(Stats stats);

#endif