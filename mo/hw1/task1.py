from functools import partial
from itertools import zip_longest

import numpy as np
import matplotlib.pyplot as plt
from scipy.special import expit
from sklearn import datasets
from mpl_toolkits.mplot3d import Axes3D
from sklearn.model_selection import train_test_split
import pandas as pd
from scipy.linalg import cho_factor, cho_solve
from sympy import *


def abstract_function_of_search(func, a0, b0, eps, maximum_quantity_of_iteration, x1_f, x2_f):
    a = [a0]
    b = [b0]
    iter_num = 1
    while abs(func(b[-1]) - func(a[-1])) > eps and iter_num < maximum_quantity_of_iteration:
        x1 = x1_f(a[-1], b[-1], iter_num)
        x2 = x2_f(a[-1], b[-1], iter_num)
        if func(x1) < func(x2):
            b.append(x2)
            a.append(a[-1])
        elif func(x1) > func(x2):
            b.append(b[-1])
            a.append(x1)
        else:
            break
        iter_num += 1
    return a, b, iter_num

def function_name(method):
    return method.__name__.replace('_', ' ').capitalize()


def gold_section(*args):
    phi = (1 + np.sqrt(5)) / 2
    x1_f = lambda a, b, _: b - (b - a) / phi
    x2_f = lambda a, b, _: a + (b - a) / phi
    return abstract_function_of_search(*args, x1_f, x2_f)


def dichotomy(f, a0, b0, eps, maximum_quantity_of_iteration):
    delta = eps / 3 
    x2_f = lambda a, b, _: (a + b) / 2 + delta
    x1_f = lambda a, b, _: (a + b) / 2 - delta
    return abstract_function_of_search(f, a0, b0, eps, maximum_quantity_of_iteration, x1_f, x2_f)

def functional_function(x):
    return 1.5 * x ** 2 - 5 * x + 15.5


def fibonacci(f, a0, b0, eps, maximum_quantity_of_iteration):
    fibs = [1, 1, 2]

    def add_fib():
        fibs.append(fibs[-1] + fibs[-2])
    
    while (b0 - a0) >= fibs[-1] * eps:
        add_fib()

    fib_np2 = fibs[-1]

    n = len(fibs) - 3
    x2_f = lambda a, _, iter_num: a + (b0 - a0) * fibs[n - iter_num + 2] / fib_np2
    x1_f = lambda a, _, iter_num: a + (b0 - a0) * fibs[n - iter_num + 1] / fib_np2
    return abstract_function_of_search(f, a0, b0, eps, maximum_quantity_of_iteration, x1_f, x2_f)


abstract_function_of_search_methods = [dichotomy, gold_section, fibonacci]



def interval_relationship(a0, b0, eps, maximum_quantity_of_iteration):
    def inner(odm):
        a, b, iter_num = odm(functional_function, a0, b0, eps, maximum_quantity_of_iteration)
        return [(b[i] - a[i]) / (b[i - 1] - a[i - 1]) for i in range(1, iter_num)]

    return inner


def draw_initial_function():
    begin = -100.0
    end = 100.0

    xs = np.linspace(begin, end, 10000)
    ys = functional_function(xs)
    plt.plot(xs, ys)
    plt.xlabel('$x$')
    plt.ylabel('$f(x)$')
    plt.title('$f(x) = 1.5x^2 - 5 * x + 15.5$')
    plt.show()
    print(f'x_min = {xs[ys.argmin()]}')


def draw_iteration_accuracy():
    begin = -100.0
    end = 100.0

    a0, b0 = begin, end
    eps_range = np.arange(0.01, 0.5, 0.01)
    maximum_quantity_of_iteration = 100
    print(eps_range)
    for odm in abstract_function_of_search_methods:
        iter_nums = []
        for eps in eps_range:
            _, _, iter_num = odm(functional_function, a0, b0, eps, maximum_quantity_of_iteration)
            iter_nums.append(iter_num)
        plt.plot(eps_range, iter_nums)
        plt.title(function_name(odm))
        plt.xlabel('$\epsilon$')
        plt.ylabel('Iterations number')
        plt.show()


def draw_interval_by_iteration_number():
    begin = -100.0
    end = 100.0

    a0, b0 = begin, end
    eps = 1e-5
    maximum_quantity_of_iteration = 100
    for odm in abstract_function_of_search_methods:
        a, b, iter_num = odm(functional_function, a0, b0, eps, maximum_quantity_of_iteration)
        iters = range(0, iter_num)
        plt.step(iters, a, label='a border')
        plt.step(iters, b, label='b border')
        plt.fill_between(iters, a, b, step='pre', alpha=0.1)
        plt.title(function_name(odm))
        plt.xlabel('Iteration number')
        plt.ylabel('$x$')
        plt.legend()
        plt.show()


if __name__ == "__main__":
    print("AAA")