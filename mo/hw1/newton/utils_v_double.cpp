#include "utils_v_double.h"

#include <math.h>

double l2_norma (std::vector <double> const & a)
{
    double sum = 0.;
    for (double v : a)
    {
        sum += v * v;
    }
    return std::sqrt(sum);
}

std::vector <std::vector <double> > operator *
(
    std::vector <std::vector <double> > const & a, 
    std::vector <std::vector <double> > const & b
)
{
    std::vector <std::vector <double> > ans(a.size(), std::vector <double> (b[0].size(), 0));

    for (size_t i = 0; i != a.size(); ++i)
    {
        for (size_t j = 0; j != b[0].size(); ++j)
        {
            for (size_t k = 0; k != b.size(); ++k)
            {
                ans[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return ans;
}

std::vector <std::vector <double> > operator !
(
    std::vector <std::vector <double> > const & a 
)
{
    std::vector <std::vector <double> > ans(a.size(), std::vector <double> (a[0].size(), 0));

    for (size_t i = 0; i != a.size(); ++i)
    {
        for (size_t j = 0; j != a[0].size(); ++j)
        {
            ans[i][j] = a[j][i];
        }
    }
    return ans;
}

