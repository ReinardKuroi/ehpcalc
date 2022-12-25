#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structs.h"
#include "polynomial.h"
#include "mlr.h"

#define E 0.000001
#define LEARNING_RATE 0.000001

typedef double (*derivative_t)(Coefficients, Point, int);
typedef double (*predict_t)(Coefficients, double, double);

predict_t predict = polynomial_predict;
derivative_t df_dw1 = polynomial_df_dw1;
derivative_t df_dw2 = polynomial_df_dw2;
derivative_t df_dw3 = polynomial_df_dw3;
derivative_t df_dw4 = polynomial_df_dw4;
derivative_t df_dw5 = polynomial_df_dw5;
derivative_t df_dw6 = polynomial_df_dw6;

double calculate_mean_squared_error(Coefficients c, Point points[], int n) {
	double error;
	double cumulative_error = 0;
	for (int i = 0; i < n; ++i) {
		error = predict(c, points[i].x, points[i].y) - points[i].z;
		cumulative_error += error * error;
	}
	cumulative_error /= 2 * n;
	return cumulative_error;
}

void adjust_coefficients_based_on_error(Coefficients *c, Point points[], int n) {
	Coefficients new_c;
	
	new_c.w1 = c->w1 - LEARNING_RATE * df_dw1(*c, points, n);
	new_c.w2 = c->w2 - LEARNING_RATE * df_dw2(*c, points, n);
	new_c.w3 = c->w3 - LEARNING_RATE * df_dw3(*c, points, n);
	new_c.w4 = c->w4 - LEARNING_RATE * df_dw4(*c, points, n);
	new_c.w5 = c->w5 - LEARNING_RATE * df_dw5(*c, points, n);
	new_c.w6 = c->w6 - LEARNING_RATE * df_dw6(*c, points, n);
	
	*c = new_c;
	
	return;
}

Coefficients fit_function(Point points[], int n) {
	Coefficients coefficients = {
		.5,
		.5,
		.5,
		.5,
		.5,
		0,
	};
	double error;
	double prev_error;
	int generation = 0;
	error = calculate_mean_squared_error(coefficients, points, n);

	do {
		adjust_coefficients_based_on_error(&coefficients, points, n);
		prev_error = error;
		error = calculate_mean_squared_error(coefficients, points, n);
		if (generation % 1000 == 0) {
			printf("gen %d: mse: %.4f\n", generation/1000, error);
		}
		generation++;
	} while (prev_error - error > E);
		
	return coefficients;
}