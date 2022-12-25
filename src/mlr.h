#ifndef MLR_INCLUDED
#define MLR_INCLUDED

#include "structs.h"
#include "polynomial.h"
#include "exponential.h"

typedef double (*derivative_t)(Coefficients, Point *, int);
typedef double (*predict_t)(Coefficients, double, double);

#if PREDICTION_FUNCTION == POLYNOMIAL
	predict_t predict = &polynomial_predict;
	derivative_t df_dw1 = &polynomial_df_dw1;
	derivative_t df_dw2 = &polynomial_df_dw2;
	derivative_t df_dw3 = &polynomial_df_dw3;
	derivative_t df_dw4 = &polynomial_df_dw4;
	derivative_t df_dw5 = &polynomial_df_dw5;
	derivative_t df_dw6 = &polynomial_df_dw6;
#elif PREDICTION_FUNCTION == EXPONENTIAL
	predict_t predict = &exponential_predict;
	derivative_t df_dw1 = &exponential_df_dw1;
	derivative_t df_dw2 = &exponential_df_dw2;
	derivative_t df_dw3 = &exponential_df_dw3;
	derivative_t df_dw4 = &exponential_df_dw4;
	derivative_t df_dw5 = &exponential_df_dw5;
	derivative_t df_dw6 = &exponential_df_dw6;
#endif

double calculate_mean_squared_error(Coefficients c, Point points[], int n);

Coefficients fit_function(Point points[], int n);

#endif