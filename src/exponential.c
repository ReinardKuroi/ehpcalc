#include <math.h>

#include "structs.h"
#include "exponential.h"

double exponential_predict(Coefficients c, double x, double y) {
	return c.w1 * pow(x - c.w2, c.w3) + c.w4 * pow(y - c.w5, c.w6);
}

double exponential_df_dw1(Coefficients c, Point points[], int n) {
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += pow(points[i].x - c.w2, c.w3) * (exponential_predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
}

double exponential_df_dw2(Coefficients c, Point points[], int n) {
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += -c.w3 * c.w1 * pow(points[i].x - c.w2, c.w3 - 1) * (exponential_predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
}

double exponential_df_dw3(Coefficients c, Point points[], int n) {
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += c.w1 * pow(points[i].x - c.w2, c.w3) * log(points[i].x - c.w2) * (exponential_predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
}

double exponential_df_dw4(Coefficients c, Point points[], int n) {
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += pow(points[i].y - c.w5, c.w6) * (exponential_predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
}
double exponential_df_dw5(Coefficients c, Point points[], int n) {
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += -c.w6 * c.w4 * pow(points[i].y - c.w5, c.w6 - 1) * (exponential_predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
}

double exponential_df_dw6(Coefficients c, Point points[], int n) {
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += c.w4 * pow(points[i].y - c.w5, c.w6) * log(points[i].y - c.w5) * (exponential_predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
}