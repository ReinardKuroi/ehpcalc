#ifndef EXPONENTIAL_INCLUDED
#define EXPONENTIAL_INCLUDED

#include "structs.h"

double exponential_predict(Coefficients c, double x, double y);
double exponential_df_dw1(Coefficients c, Point points[], int n);
double exponential_df_dw2(Coefficients c, Point points[], int n);
double exponential_df_dw3(Coefficients c, Point points[], int n);
double exponential_df_dw4(Coefficients c, Point points[], int n);
double exponential_df_dw5(Coefficients c, Point points[], int n);
double exponential_df_dw6(Coefficients c, Point points[], int n);

#endif