#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "health.h"
#include "mlr.h"
#include "structs.h"

#define MAX_POINTS 32768

int this_data_is_for_testing() {
	float percent;
	float margin = 0.7;
	percent = (float)rand()/(float)RAND_MAX;
	return percent > margin;
}

int main()
{
    Stats stats;
	int max_hp;
	int max_ar;
	Point training_points[MAX_POINTS];
	Point testing_points[MAX_POINTS];
	Coefficients coefficients;
	double mse;
	int idx_testing = 0;
	int idx_training = 0;
    
	srand(time(NULL));
	
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
			if (this_data_is_for_testing()) {
				testing_points[idx_testing].x = stats.health;
				testing_points[idx_testing].y = stats.armour;
				testing_points[idx_testing].z = stats.effective_hp;
				idx_testing++;
			} else {
				training_points[idx_training].x = stats.health;
				training_points[idx_training].y = stats.armour;
				training_points[idx_training].z = stats.effective_hp;
				idx_training++;
			}
		}
	}
	
	printf("done\n");
	printf("Fitting a function using generated point list...");
	
	coefficients = fit_function(testing_points, idx_testing);
	
	printf("done\n");
	printf("Calculating MSE for training data...");
	
	mse = calculate_mean_squared_error(coefficients, training_points, idx_training);
	
	printf("done\n");
	
	printf("For the given range of possible HP and AR combinations:\n");
	printf("\n\tMax HP: %d\n\tMax AR: %d\n", max_hp, max_ar);
	printf("\n\tCoefficients: %.2f %.2f %.2f %.2f %.2f %.2f\n",
		coefficients.w1, coefficients.w2, coefficients.w3, coefficients.w4, coefficients.w5, coefficients.w6);
	printf("\tMSE on testing data: %.5f", mse);
	
    return 0;
}