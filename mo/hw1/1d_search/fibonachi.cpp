#include <functional>

std::vector <double> get_fib (double limit)
{
    std::vector <double> ans = {1., 1.};
    
    while (ans.back() <= limit)
    {
        ans.push_back(ans.back() + *(ans.cend() - 2));
    }
    
    return ans;
}

double fibonachi (std::function <double (double, double, double)> f, double a, double b, double eps)
{
    std::vector <double> fib = get_fib((b - a) / eps);
    bool rotate = 1;
    double old_value = f(a + (b - a) * *(fib.cend() - 3) / fib.back(), a, b);
    for (size_t i = fib.size() - 2; i >= 1; --i)
    {
        double m1 = a + (b - a) * fib[i - 1] / fib[i + 1];
        double m2 = a + (b - a) * fib[i] / fib[i + 1];
        double f_m1 = (rotate? old_value : f(m1, a, b));
        double f_m2 = (rotate? f(m2, a, b) : old_value);
        if (f_m1 > f_m2)
        {
            rotate = 1;
            old_value = f_m2;
            a = m1;
        }
        else
        {
            rotate = 0;
            old_value = f_m1;
            b = m2;
        }
    }
    
    return (a + b) / 2.;
}

