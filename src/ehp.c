#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "structs.h"
#include "health.h"
#include "mlr.h"

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
	double training_mse;
	double testing_mse;
	int idx_training = 0;
	int idx_testing = 0;
    
	srand(time(NULL));
	
    printf("Enter HP range to test: ");
    scanf("%d", &max_hp);
    printf("Enter AR range to test: ");
    scanf("%d", &max_ar);
	printf("Generating a list of possible stat points...");
	
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
	
	coefficients = fit_function(training_points, idx_training);
	
	printf("done\n");
	printf("Calculating MSE for training data...");
	
	training_mse = calculate_mean_squared_error(coefficients, training_points, idx_training);
	
	printf("done\n");
	printf("Calculating MSE for testing data...");
	
	testing_mse = calculate_mean_squared_error(coefficients, testing_points, idx_testing);
	
	printf("done\n");
	
	fflush(stdout);
	
	if (testing_mse > 2<<16) {
		printf("MSE exceeding at %'5f\nAborting...\n", testing_mse);
		return 1;
	}
	
	printf("For the given range of possible HP and AR combinations:\n");
	print_predict_function(coefficients);
	printf("\n\tCoefficients: %.2f %.2f %.2f %.2f %.2f %.2f\n",
		coefficients.w1, coefficients.w2, coefficients.w3, coefficients.w4, coefficients.w5, coefficients.w6);
	printf("\tMSE on training data: %.5f\n", training_mse);
	printf("\tMSE on testing data: %.5f\n", testing_mse);
	
	Stats example_guardsman = {
		.health = 4,
		.armour = 2,
	};
	stats_calculate_effective_health(&example_guardsman);
	Stats example_hammerhead = {
		.health = 30,
		.armour = 6,
	};
	stats_calculate_effective_health(&example_hammerhead);
	Stats example_triarch_praetorian = {
		.health = 10,
		.armour = 5,
	};
	stats_calculate_effective_health(&example_triarch_praetorian);
	
	printf("\nSome arbitrary examples:\n");
	printf("\nGuardsman ");
	stats_print(example_guardsman);
	printf("\tEHP(predicted): %.1f\n", calculate_using_formula(coefficients, example_guardsman.health, example_guardsman.armour));
	printf("\nHammerhead ");
	stats_print(example_hammerhead);
	printf("\tEHP(predicted): %.1f\n", calculate_using_formula(coefficients, example_hammerhead.health, example_hammerhead.armour));
	printf("\nTriarch Praetorian ");
	stats_print(example_triarch_praetorian);
	printf("\tEHP(predicted): %.1f\n", calculate_using_formula(coefficients, example_triarch_praetorian.health, example_triarch_praetorian.armour));
	
    return 0;
}