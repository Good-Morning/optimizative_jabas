#include "solve_system.h"

std::vector <double> solve_system_l //L * L_t * x = b
(
    std::vector <std::vector <double> > const & l,
    std::vector <double> const & b
)
{
    //L * y = b
    std::vector <double> y (l.size());
    
    for (size_t i = 0; i != l.size(); ++i)
    {
        double sum = 0.;
        for (size_t j = 0; j != i; ++j)
        {
            sum += y[j] * l[i][j];
        }
        y[i] = (b[i] - sum) / l[i][i];
    }
    
    //L_t * x = y
    //L_t implicit
    std::vector <double> x (l.size());
    
    for (size_t i = l.size() - 1; i < l.size(); --i)
    {
        double sum = 0.;
        for (size_t j = i + 1; j < l.size(); ++j)
        {
            sum += x[j] * l[j][i]; //l_t[i][j]
        }
        x[i] = (y[i] - sum) / l[i][i];
    }
    
    return x;
}

