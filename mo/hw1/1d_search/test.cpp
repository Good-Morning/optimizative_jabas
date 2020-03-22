#include <algorithm>
#include <functional>
#include <memory>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "plots/plots.h"

double dihotomy (std::function <double (double, double, double)> f, double a, double b, double eps);
double gold_division (std::function <double (double, double, double)> f, double a, double b, double eps);
double fibonachi (std::function <double (double, double, double)> f, double a, double b, double eps);

struct calls
{
    calls 
    (
        size_t _cnt = 0, 
        std::vector <double> _a = std::vector <double> (), 
        std::vector <double> _b = std::vector <double> ()
    ) :
        cnt(_cnt),
        a(_a),
        b(_b)
    {}

    size_t cnt;
    std::vector <double> a;
    std::vector <double> b;
};

template <typename F>
struct call_counter
{
    call_counter(F && _f) :
        _storage(std::make_shared <calls> ()),
        f(_f)
    {}
    
    template <typename ... T>
    double operator () (double a, double aa, double bb)
    {
        _storage->cnt++;
        _storage->a.push_back(aa);
        _storage->b.push_back(bb);
        return f(a);
    }

    calls count () const
    {
        return calls(*_storage);
    }
    
    calls count (calls __new)
    {
        calls ans = count();
        *_storage = __new;
        return ans;
    }

private:
    std::shared_ptr <calls> _storage;
    F f;
};

template <typename F>
struct call 
{
    call 
    (
        call_counter <F> _f, 
        double _a, 
        double _b, 
        double _eps = 1e-9
    ) :
        f(_f),
        a(_a),
        b(_b),
        eps(_eps)
    {}

    calls operator () 
    (
        std::function <double (std::function <double (double, double, double)> f, double a, double b, double eps)> method
    )
    {
        f.count(calls());
        method(f, a, b, eps);
        return f.count();
    }

    double eps;

private:
    call_counter <F> f;
    double a;
    double b; 
};

std::vector <double> sequence (size_t size)
{
    std::vector <double> ans;
    ans.reserve(size);
    for (size_t i = 0; i != size; ++i)
    {
        ans.push_back(i);
    }
    return ans;
}


std::pair <double, double> min_max (std::vector <double> const & a)
{
    if (a.empty())
    {
        return {0, 0};
    }
    return 
    {
        *std::min_element(a.begin(), a.end()),
        *std::max_element(a.begin(), a.end())
    };
}

template <typename T>
std::pair <double, double> min_max (std::vector <std::vector <T> > const & a)
{
    if (a.empty())
    {
        return {0, 0};
    }
    else 
    {
        std::pair <double, double> ans = min_max(a[0]);
        for (std::vector <T> const & i : a)
        {
            std::pair <double, double> cur = min_max(i);
            ans.first = std::min(ans.first, cur.first);
            ans.second = std::max(ans.second, cur.second);
            
        }
        return {ans.first - 0.1, ans.second + 0.1};
    };
}


std::vector <double> segments_division
(
    std::vector <double> const & a,
    std::vector <double> const & b
)
{
    std::vector <double> ans;
    for (size_t i = 1; i < std::min(a.size(), b.size()); ++i)
    {
        ans.push_back((b[i] - a[i]) / (b[i - 1] - a[i - 1]));
    }
    return ans;
}


int main ()
{
    auto f = [] (double x) -> double
    {
        //return std::cos(v);
        return 1.5 * x*x - -5 * x + 15.5;
    };

    auto f_ = [&f] (double v, double, double) -> double
    {
        return f(v);
    };
    double a = -100;
    double b = 100;

    {
        std::cout.precision(12);
        std::cout << dihotomy(f_, a, b, 1e-12) << "\n";
        std::cout << gold_division(f_, a, b, 1e-12) << "\n";
        std::cout << fibonachi(f_, a, b, 1e-12) << "\n";
    }
    
    {
        std::vector <double> dihotomy_cnt;
        std::vector <double> gold_div_cnt;
        std::vector <double> fibonachi_cnt;
        std::vector <double> precision_v;

        call caller(call_counter <std::function <double (double)> > (f), a, b);

        for (double precision = 1e0; precision >= 1e-14; precision /= 1.05)
        {
            caller.eps = precision;
            dihotomy_cnt.push_back(caller(dihotomy).cnt);
            gold_div_cnt.push_back(caller(gold_division).cnt);
            fibonachi_cnt.push_back(caller(fibonachi).cnt);
            precision_v.push_back(precision);
        }

        make_plot plot
        (
            "1\\_task",
            "1\\_task",
            {10, 1e-15},
            {1, 150},
            "precision",
            "f\\_call\\_count"
        );
        
        plot.add(precision_v, dihotomy_cnt, "b", "dihotomy");
        plot.add(precision_v, gold_div_cnt, "g", "gold\\_division");
        plot.add(precision_v, fibonachi_cnt, "r", "fibonachi");
    }

    {
        call caller(call_counter <std::function <double (double)> > (f), a, b);

        caller.eps = 1e-6;
        calls dih = caller(dihotomy);
        calls gold = caller(gold_division);
        calls fib = caller(fibonachi);

        {
            make_plot plot
            (
                "segment\\_dihotomy eps=" + std::to_string(caller.eps),
                "segment\\_dihotomy",
                {-1, dih.a.size() + 1},
                min_max(std::vector <std::vector <double> > {dih.a, dih.b}),
                "call",
                "value",
                "x",
                "y",
                1,
                1.0,
                1.0
            );

            plot.add(sequence(dih.a.size()), dih.a, "b", "a");
            plot.add(sequence(dih.b.size()), dih.b, "r", "b");
        }
        {
            make_plot plot
            (
                "segment\\_fibbonachi eps=" + std::to_string(caller.eps),
                "segment\\_fibbonachi",
                {-1, fib.a.size() + 1},
                min_max(std::vector <std::vector <double> > {fib.a, fib.b}),
                "call",
                "value",
                "x",
                "y",
                1,
                1.0,
                1.0
            );
            plot.add(sequence(fib.a.size()), fib.a, "b", "a");
            plot.add(sequence(fib.b.size()), fib.b, "r", "b");
        }
        {
            make_plot plot
            (
                "segment\\_gold eps=" + std::to_string(caller.eps),
                "segment\\_gold",
                {-1, gold.a.size() + 1},
                min_max(std::vector <std::vector <double> > {gold.a, gold.b}),
                "call",
                "value",
                "x",
                "y",
                1,
                1.0,
                1.0
            );
            plot.add(sequence(gold.a.size()), gold.a, "b", "a");
            plot.add(sequence(gold.b.size()), gold.b, "r", "b");
        }
        
        {
            std::vector <double> s_div_dih = segments_division(dih.a, dih.b);
            std::vector <double> s_div_gold = segments_division(gold.a, gold.b);
            std::vector <double> s_div_fib = segments_division(fib.a, fib.b);
            std::cout << std::setw(10) << "dihotomy" << " ";
            std::cout << std::setw(10) << "gold" << " ";
            std::cout << std::setw(10) << "fibonachi" << " ";
            std::cout << "\n";
            std::cout << std::setw(10) << s_div_dih.size() << " ";
            std::cout << std::setw(10) << s_div_gold.size() << " ";
            std::cout << std::setw(10) << s_div_fib.size() << " ";
            std::cout << "\n";
            for (size_t i = 0; i != std::max(s_div_dih.size(), std::max(s_div_gold.size(), s_div_fib.size())); ++i)
            {
                std::cout << std::setw(10) << ((s_div_dih.size() > i)? std::to_string(s_div_dih[i]) : " ") << " ";
                std::cout << std::setw(10) << ((s_div_gold.size() > i)? std::to_string(s_div_gold[i]) : " ") << " ";
                std::cout << std::setw(10) << ((s_div_fib.size() > i)? std::to_string(s_div_fib[i]) : " ") << " ";
                std::cout << "\n";
            }
        }
    }
}

