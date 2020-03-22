#ifndef SOLVE_SYSTEM_H
#define SOLVE_SYSTEM_H

#include <vector>
#include "holetskiy.h"

std::vector <double> solve_system_l //L * L_t * x = b
(
    std::vector <std::vector <double> > const & l,
    std::vector <double> const & b
);

inline std::vector <double> solve_system
(
    std::vector <std::vector <double> > const & a,
    std::vector <double> const & b
)
{
    return solve_system_l(holetskiy(a), b);
}


#endif
