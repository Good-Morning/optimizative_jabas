import task1 as t1
from functools import partial
from itertools import zip_longest

import numpy as np
from scipy.special import expit
from sklearn import datasets
import pandas as pd
from sympy import *
from scipy.linalg import cho_factor, cho_solve
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split


def function_name(method):
    return method.__name__.replace('_', ' ').capitalize()


def linear_search(f, x_cur, df_x):
    stp = 1.0
    alpha = 0.5
    beta = 0.5
    grad = np.array([df_x[i](*x_cur) for i in range(0, len(df_x))])
    p = np.dot(grad, grad)
    while (f(*x_cur) - (f(*(x_cur - stp * np.array(grad))) + alpha * stp * p)) < 0:
        stp *= beta
    return stp


def helper(f, x, x_evaluated_grd, lmd):
    args = []
    dim = len(x)
    for i in range(dim):
        args.append(x[i] - lmd * x_evaluated_grd[i](*x))
    return f(*args)

def gradient_descention(f, *x, eps, max_iter_num, step_f):
    dim = len(x)
    symbol = list(map(Symbol, {
        1: ['x'],
        2: ['x', 'y'],
        3: ['x', 'y', 'z']
    }.get(dim, ['x' + str(i) for i in range(1, dim + 1)])))

    x_evaluated_grd = [lambdify(symbol, f(*symbol).diff(smb)) for smb in symbol]

    x_cur = [*x]
    xs = [x_cur]
    iter_num = 0
    while True:
        if step_f is linear_search:
            step = step_f(f, np.array(x_cur), x_evaluated_grd)
        else:
            step = step_f(lambda lmd: helper(f, x_cur, x_evaluated_grd, lmd))

        x_next = [0] * dim
        for i in range(dim):
            x_next[i] = x_cur[i] - step * x_evaluated_grd[i](*x_cur)
        xs.append(x_next)

        if abs(f(*x_next) - f(*x_cur)) < eps or iter_num == max_iter_num:
            return np.array(xs), iter_num

        x_cur = x_next.copy()
        iter_num += 1
