#ifndef EXPONENTIAL_INCLUDED
#define EXPONENTIAL_INCLUDED

double predict(Coefficients c, double x, double y);
double df_dw1(Coefficients c, Point points[], int n);
double df_dw2(Coefficients c, Point points[], int n);
double df_dw3(Coefficients c, Point points[], int n);
double df_dw4(Coefficients c, Point points[], int n);
double df_dw5(Coefficients c, Point points[], int n);
double df_dw6(Coefficients c, Point points[], int n);

#endif