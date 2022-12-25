#ifndef POLYNOMIAL_INCLUDED
#define POLYNOMIAL_INCLUDED

double polynomial_predict(Coefficients c, double x, double y);
double polynomial_df_dw1(Coefficients c, Point points[], int n);
double polynomial_df_dw2(Coefficients c, Point points[], int n);
double polynomial_df_dw3(Coefficients c, Point points[], int n);
double polynomial_df_dw4(Coefficients c, Point points[], int n);
double polynomial_df_dw5(Coefficients c, Point points[], int n);
double polynomial_df_dw6(Coefficients c, Point points[], int n);

#endif