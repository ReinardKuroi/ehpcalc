#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 32768

typedef struct {
    double x;
    double y;
    double z;
} Point;

double calculate_quadratic_error(Point points[], int n, double a, double b, double c) {
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

double calculate_effective_health(int health, int armour)
{
    int effective_hp;
    int current_hp;
    double average_effective_hp = 0;
    
    for (int damage = armour + 1; damage <= health + armour; ++damage) {
        effective_hp = 0;
        current_hp = health;
        while (current_hp > 0) {
            current_hp -= damage - armour;
            effective_hp += damage;
        }
        average_effective_hp += effective_hp;
    }
    
    return average_effective_hp / health;
}

double fit_function_ax_by_c(Point points[], int n, double *a, double *b, double *c) {
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
    
    return calculate_quadratic_error(points, n, *a, *b, *c);
}

int main()
{
    Point points[MAX_POINTS];
    int max_health;
    int max_armour;
    double quadratic_error;
    int n;
    double optimal_a;
    double optimal_b;
    double optimal_c;
    double a;
    double b;
    double c;
    double min_quadratic_error = 2147483647;
    
    printf("Enter max HP to test: ");
    scanf("%d", &max_health);
    printf("Enter max AR to test: ");
    scanf("%d", &max_armour);
    
    for (int cur_max_health = 1; cur_max_health <= max_health; ++cur_max_health) {
        for (int cur_max_armour = 0; cur_max_armour <= max_armour; ++cur_max_armour) {
            n = 0;
            for (int health = 1; health <= cur_max_health; ++health) {
                for (int armour = 0; armour <= cur_max_armour; ++armour) {
                    points[n].x = health;
                    points[n].y = armour;
                    points[n].z = calculate_effective_health(health, armour);
                    n++;
                }
            }
            a = 0;
            b = 0;
            c = 0;
            quadratic_error = fit_function_ax_by_c(points, n, &a, &b, &c);;
            if (quadratic_error < min_quadratic_error) {
                min_quadratic_error = quadratic_error;
                optimal_a = a;
                optimal_a = b;
                optimal_c = c;
            }
        }
    }

    printf("\nError: %f\n", calculate_quadratic_error(points, n, a, b, c));
    printf("Min error: %f\n", min_quadratic_error);
    printf("a = %f, b = %f, c = %f\n", optimal_a, optimal_a, optimal_c);
    
    return 0;
}