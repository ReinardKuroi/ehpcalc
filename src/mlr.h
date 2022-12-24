#ifndef MLR_INCLUDED
#define MLR_INCLUDED

typedef struct {
	double w1;
	double w2;
	double w3;
	double w4;
	double w5;
	double w6;
} Coefficients;

typedef struct {
	double x;
	double y;
	double z;
} Point;

double predict(Coefficients c, double x, double y);

double calculate_mean_squared_error(Coefficients c, Point points[], int n);

void adjust_coefficients_based_on_error(Coefficients *c, Point points[], int n);

void fit_function();

#endif