#ifndef UTILS_H
#define UTILS_H

#include <ostream>
#include <vector>

template <typename T>
std::vector <T> operator - (std::vector <T> a, std::vector <T> const & b)
{
    for (size_t i = 0; i != a.size(); ++i)
    {
        a[i] = a[i] - b[i];
    }
    
    return a;
}

template <typename T>
std::vector <T> operator + (std::vector <T> a, std::vector <T> const & b)
{
    for (size_t i = 0; i != a.size(); ++i)
    {
        a[i] = a[i] + b[i];
    }
    
    return a;
}



template <typename T>
std::vector <T> operator - (std::vector <T> a)
{
    for (T & v : a)
    {
        v = -v;
    }
    
    return a;
}

template <typename T>
std::vector <T> operator * (std::vector <T> a, double b)
{
    for (T & v : a)
    {
        v *= b;
    }
    
    return a;
}

template <typename T>
inline std::vector <T> operator * (double b, std::vector <T> a)
{
    return a * b;
}

template <typename T>
std::ostream & operator << (std::ostream & s, std::vector <T> const & a)
{
    for (T const & v : a)
    {
        s << v << " ";
    }
    return s;
}


template <typename T>
std::ostream & operator << (std::ostream & s, std::vector <std::vector <T> > const & a)
{
    for (std::vector <T> const & v : a)
    {
        s << v << "\n";
    }
    return s;
}

#endif
