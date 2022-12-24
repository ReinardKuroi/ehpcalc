#include <stdio.h>
#include "health.h"

int main()
{
    Stats stats;
    
    printf("Enter HP to test: ");
    scanf("%f", &stats.health);
    printf("Enter AR to test: ");
    scanf("%f", &stats.armour);
    stats_calculate_effective_health(&stats);
	stats_print(stats);
    
    return 0;
}