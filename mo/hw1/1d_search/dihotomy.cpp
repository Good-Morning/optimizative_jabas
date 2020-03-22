#include <functional>

double dihotomy (std::function <double (double, double, double)> f, double a, double b, double eps)
{
    double sigma = eps / 3.;
    while (b - a >= eps)
    {
        double m = (a + b) / 2.;
        if (f(m - sigma, a, b) > f(m + sigma, a, b))
        {
            a = m - sigma;
        }
        else
        {
            b = m + sigma;
        }
    }
    
    return (a + b) / 2.;
}

