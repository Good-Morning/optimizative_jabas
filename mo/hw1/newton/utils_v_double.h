#ifndef UTILS_V_DOUBLE_H
#define UTILS_V_DOUBLE_H

#include <vector>

double l2_norma (std::vector <double> const & a);

std::vector <std::vector <double> > operator *
(
    std::vector <std::vector <double> > const & a, 
    std::vector <std::vector <double> > const & b
);

std::vector <std::vector <double> > operator !
(
    std::vector <std::vector <double> > const & a 
);

#endif
