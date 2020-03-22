#include <functional>
#include <math.h>

double gold_division (std::function <double (double, double, double)> f, double a, double b, double eps)
{
    auto split = [&a, &b] () -> double {return (1. + (1. - std::sqrt(5.)) / 2.) * (b - a);};
    bool rotate = 1;
    double old_value = f(a + split(), a, b);
    while (b - a >= eps)
    {
        double f_m1 = (rotate? old_value : f(a + split(), a, b));
        double f_m2 = (rotate? f(b - split(), a, b) : old_value);
        if (f_m1 > f_m2)
        {
            rotate = 1;
            old_value = f_m2;
            a += split();
        }
        else
        {
            rotate = 0;
            old_value = f_m1;
            b -= split();
        }
    }
    
    return (a + b) / 2.;
}

