#ifndef NEWTON_H
#define NEWTON_H

#include <vector>
#include <functional>

typedef std::function <double (std::vector <double> const &)> func_type;
typedef std::function <double (std::vector <double> const &, size_t)> derivative_type;
typedef std::function <double (std::vector <double> const &, size_t, size_t)> hessian_type;

std::vector <double> newton 
(
    func_type f,
    derivative_type derivative,
    hessian_type hessian,
    
    std::vector <double> start,
    double eps,
    double a = 1.
);

std::vector <double> apply_ 
(
    derivative_type derivative,
    std::vector <double> const & value
);


std::vector <std::vector <double> > apply_ 
(
    hessian_type hessian,
    std::vector <double> const & value
);

#endif
