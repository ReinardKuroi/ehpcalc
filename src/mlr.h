#ifndef MLR_INCLUDED
#define MLR_INCLUDED

#include "structs.h"

double calculate_mean_squared_error(Coefficients c, Point points[], int n);

Coefficients fit_function(Point points[], int n);

#endif