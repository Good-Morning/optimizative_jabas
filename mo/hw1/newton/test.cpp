#include <vector>
#include <iostream>
#include "newton.h"
#include "utils.h"
#include "utils_v_double.h"
#include "solve_system.h"


int main ()
{
    std::vector <std::vector <double> > v = 
    {
        {2, -1, 0},
        {-1, 2, -1},
        {0, -1, 2}
    };
    
    std::cout << v << "\n";
    std::cout << holetskiy(v) << "\n";
    std::cout << holetskiy(v) * !holetskiy(v) << "\n";
    std::cout << solve_system(v, {0, 0, 4}) << "\n";

    func_type f = [] (std::vector <double> const & a) -> double {return a[0]*a[0] + a[1]*a[1];};
    std::vector <func_type> d = 
    {
        [] (std::vector <double> const & a) -> double {return 2.*a[0] + a[1]*a[1];},
        [] (std::vector <double> const & a) -> double {return a[0]*a[0] + 2.*a[1];}
    };
    func_type h_00 = [] (std::vector <double> const & a) -> double {return 2. + a[1]*a[1];};
    func_type h_01 = [] (std::vector <double> const & a) -> double {return 2.*a[0] + 2.*a[1];};
    func_type h_10 = [] (std::vector <double> const & a) -> double {return 2.*a[0] + 2.*a[1];};
    func_type h_11 = [] (std::vector <double> const & a) -> double {return a[0]*a[0] + 2.;};
    std::vector <std::vector <func_type> > h = 
    {
        {h_00, h_01},
        {h_10, h_11}
    };
    
    std::cout << newton
    (
        f, 
        [&d] (std::vector <double> const & a, size_t i) -> double {return d[i](a);},
        [&h] (std::vector <double> const & a, size_t i, size_t j) -> double {return h[i][j](a);},
        {1, -1},
        1e-4
    );
}


