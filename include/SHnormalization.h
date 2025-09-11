// SH normalization
#include <cmath>
#define R_PI 3.1415926535897932

int factorial(int n)
{
    if (n > 1) return n * factorial(n - 1);
    else return 1;
}

float* norm(unsigned order)
{
    float* result[(order * 2) + 1];
    for (int i = (-1 * order); i <= order; i++) // calc each one
    {
        float l_frac = (((2 * order) + 1) / (4.f * R_PI));
        int r_frac = (factorial(order - i) / factorial(order + i));
        result[i+order] = sqrtf(l_frac / r_frac);
    }
    return result;
}