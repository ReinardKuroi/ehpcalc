#include "structs.h"
#include "polynomial.h"

double polynomial_predict(Coefficients c, double x, double y) {
	return c.w1 * x * x + c.w2 * x + c.w3 * y * y + c.w4 * y + c.w5 * x * y + c.w6;
}

double polynomial_df_dw1(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]x2*(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].x * points[i].x * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
}

double polynomial_df_dw2(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]x(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].x * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;
	
}

double polynomial_df_dw3(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]y2(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].y * points[i].y * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;	
}

double polynomial_df_dw4(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]y(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].y * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;	
}

double polynomial_df_dw5(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n]xy(w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += points[i].x * points[i].y * (predict(c, points[i].x, points[i].y) - points[i].z);
	}
	return cumulative_sum / n;	
}

double polynomial_df_dw6(Coefficients c, Point points[], int n) {
	// 1/n*E[1-n](w1*x2 + w2*x + w3*y2 + w4*y + w5*x*y + w6) - z)
	double cumulative_sum = 0;
	for (int i = 0; i < n; ++i) {
		cumulative_sum += predict(c, points[i].x, points[i].y) - points[i].z;
	}
	return cumulative_sum / n;		
}