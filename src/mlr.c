#include <stdlib.h>
#include <math.h>
#include "mlr.h"

#define E 0.0000001
#define LEARNING_RATE 1

double predict(Coefficients c, double x, double y) {
	return c.w1 * x * x + c.w2 * x + c.w3 * y * y + c.w4 * y + c.w5 * x * y + c.w6;
}

double df_dw1(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]x2*(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].x * points[i].x * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
}

double df_dw2(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]x(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].x * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
	
}

double df_dw3(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]y2(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].y * points[i].y * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;	
}

double df_dw4(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]y(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].y * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;	
}

double df_dw5(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]xy(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].x * points[i].y * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;	
}

double df_dw6(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n](w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += predict(c, points[i].x, points[i].y) - points[i].z;
	}
	return cumulative_sum / n;		
}

double calculate_mean_squared_error(Coefficients c, Point points[], int n) {
	// 1/(2n)*E[1-n]((w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)^2
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