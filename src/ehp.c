#include <stdio.h>
#include "health.h"

int main()
{
    int max_health;
    int max_armour;
    FILE *fp;
    
    printf("Enter max HP to test: ");
    scanf("%d", &max_health);
    printf("Enter max AR to test: ");
    scanf("%d", &max_armour);
    
    fp = fopen("data.txt", "w");

    for (int health = 1; health <= max_health; ++health) {
        for (int armour = 0; armour <= max_armour; ++armour) {
            fprintf(fp, "%d %d %.1f\n", health, armour, calculate_effective_health(health, armour));
        }
    }
    fclose(fp);
    
    return 0;
}