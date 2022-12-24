#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 32768

typedef struct {
    double x;
    double y;
    double z;
} Point;

void fit_function_ax_by_c(Point points[], int n, double *a, double *b, double *c) {
    long double sum_x = 0;
    long double sum_y = 0;
    long double sum_z = 0;
    long double sum_x2 = 0;
    long double sum_xy = 0;
    long double sum_xz = 0;
    long double sum_yz = 0;
    long double sum_y2 = 0;
    
    for (int i = 0; i < n; ++i) {
        sum_x += points[i].x;
        sum_y += points[i].y;
        sum_z += points[i].z;
        sum_x2 += points[i].x * points[i].x;
        sum_xy += points[i].x * points[i].y;
        sum_xz += points[i].x * points[i].z;
        sum_yz += points[i].y * points[i].z;
        sum_y2 += points[i].y * points[i].y;
    }
    
    long double denom = n * (sum_x2 * sum_y2 - sum_xy * sum_xy) - sum_x * (sum_x * sum_y2 - sum_xy * sum_y) + sum_y * (sum_x * sum_xy - sum_x2 * sum_y);
    *a = (sum_xz * (sum_y2 - sum_xy) + sum_yz * (sum_xy - sum_x) - sum_z * (sum_y - sum_x * sum_y2 + sum_xy * sum_y)) / denom;
    *b = (sum_xz * (sum_xy - sum_x) + sum_yz * (sum_x2 - sum_x) - sum_z * (sum_x * sum_xy - sum_x2 * sum_y)) / denom;
    *c = (sum_x * (sum_x * sum_yz - sum_y * sum_xz) + sum_y * (sum_y * sum_xz - sum_x * sum_yz) + n * (sum_x2 * sum_yz - sum_xy * sum_xz)) / denom;
}

double quadratic_error(Point points[], int n, double a, double b, double c) {
    double error;
    double expected;
    double actual;
    double cumulative_error = 0;
    
    for (int i = 0; i < n; ++i) {
        expected = points[i].z;
        actual = a * points[i].x + b * points[i].y + c;
        error = actual - expected;
        cumulative_error += error * error;
    }
    
    return sqrt(cumulative_error / n);
}

int main() {
    Point points[MAX_POINTS];
    int n = 0;
    FILE *fp;
    double a = 0;
    double b = 0;
    double c = 0;

    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        return 1;
    }
    
    while (fscanf(fp, "%lf %lf %lf", &points[n].x, &points[n].y, &points[n].z) == 3) {
        n++;
    }
    
    fit_function_ax_by_c(points, n, &a, &b, &c);
    
    printf("Error: %f\n", quadratic_error(points, n, a, b, c));
    printf("\na = %f, b = %f, c = %f\n", a, b, c);

    return 0;
}