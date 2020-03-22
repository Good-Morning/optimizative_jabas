#include "newton.h"
#include <iostream>

#include "utils.h"
#include "utils_v_double.h"
#include "solve_system.h"

std::vector <double> newton 
(
    func_type,
    derivative_type derivative,
    hessian_type hessian,
    
    std::vector <double> start,
    double eps,
    double a
)
{
    while (1)
    {
        std::vector <double> grad = apply_(derivative, start);
        std::vector <std::vector <double> > hess = apply_(hessian, start);
        
        std::vector <double> direction = solve_system(hess, -grad);
        start = start + a * direction;

        if (l2_norma(a * direction) < eps)
        {
            break;
        }
    }

    return start;
}

std::vector <double> apply_ 
(
    derivative_type derivative,
    std::vector <double> const & value
)
{
    std::vector <double> ans(value.size());
    
    for (size_t i = 0; i != ans.size(); ++i)
    {
        ans[i] = derivative(value, i);
    }
    return ans;
}

std::vector <std::vector <double> > apply_ 
(
    hessian_type hessian,
    std::vector <double> const & value
)
{
    std::vector <std::vector <double> > ans(value.size(), std::vector <double> (value.size()));
    
    for (size_t i = 0; i != ans.size(); ++i)
    {
        for (size_t j = 0; j != ans[i].size(); ++j)
        {
            ans[i][j] = hessian(value, i, j);
        }
    }
    return ans;
}


