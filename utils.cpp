#include "utils.h"
#include "math.h"

int utils::signum(double x)
{
    double sign = double(0.0 < x) - double(x < 0.0);
    return int(sign);
}

double utils::modulus(double a, double b)
{
    return std::fmod(std::fmod(a, b) + b, b);
}
