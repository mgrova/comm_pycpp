#!/usr/bin/env python

import numpy as np
from scipy.optimize import minimize, rosen, rosen_der

def min_rosen(x0):
    res = minimize(rosen, x0)
    return res

def increment_value(i):
    return i+1