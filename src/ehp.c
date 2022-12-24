#include <stdio.h>
#include "health.h"
#include "mlr.h"

#define MAX_POINTS 32768

int main()
{
    Stats stats;
	int max_hp;
	int max_ar;
	Point points[MAX_POINTS];
	Coefficients coefficients;
	double mse;
	int n = 0;
    
    printf("Enter HP range to test: ");
    scanf("%d", &max_hp);
    printf("Enter AR range to test: ");
    scanf("%d", &max_ar);
	printf("Generating a list of possible stat points...\n");
	
	for (int hp = 1; hp < max_hp; ++hp) {
		for (int ar = 0; ar < max_ar; ++ar) {
			stats.health = hp;
			stats.armour = ar;
			stats_calculate_effective_health(&stats);
			points[n].x = stats.health;
			points[n].y = stats.armour;
			points[n].z = stats.effective_hp;
			n++;
		}
	}
	
	printf("Fitting a function using generated point list...");
	
	coefficients = fit_function(points, n);
	mse = calculate_mean_squared_error(coefficients, points, n);
	
	printf("done.\n");
	
	printf("For the given range of possible HP and AR combinations:\n");
	printf("\n\tMax HP: %d\n\tMax AR: %d\n", max_hp, max_ar);
	printf("\n\tFormula: %.1f * x * x + %.1f * x + %.1f * y * y + %.1f * y + %.1f * x * y + %.1f\n", coefficients.w1, coefficients.w2, coefficients.w3, coefficients.w4, coefficients.w5, coefficients.w6);
	printf("\tMSE: %.5f", mse);
	
    return 0;
}