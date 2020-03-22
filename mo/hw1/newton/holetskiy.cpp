#include "holetskiy.h"

#include <math.h>

std::vector <std::vector <double> > holetskiy 
(
    std::vector <std::vector <double> > const & a
)
{
    std::vector <std::vector <double> > l(a.size(), std::vector <double> (a.size(), 0));
    
    l[0][0] = std::sqrt(a[0][0]);
    for (size_t j = 1; j < a.size(); ++j)
    {
        l[j][0] = a[j][0] / l[0][0];
    }
    
    for (size_t i = 1; i + 1 < a.size(); ++i)
    {
        {
            double sum = 0.;
            for (size_t p = 0; p != i; ++p)
            {
                sum += l[i][p] * l[i][p];
            }
            l[i][i] = std::sqrt(a[i][i] - sum);
        }
        
        {
            for (size_t j = i + 1; j < a.size(); ++j)
            {
                double sum = 0.;
                for (size_t p = 0; p != i; ++p)
                {
                    sum += l[i][p] * l[j][p];
                }
                l[j][i] = 1 / l[i][i] * (a[j][i] - sum);
            }
        }
    }

    
    {
        size_t i = a.size() - 1;
        double sum = 0.;
        for (size_t p = 0; p != i; ++p)
        {
            sum += l[i][p] * l[i][p];
        }
        l[i][i] = std::sqrt(a[i][i] - sum);
    }
    
    return l;
}

