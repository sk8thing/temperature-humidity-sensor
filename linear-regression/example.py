import numpy as np
from scipy.optimize import curve_fit


def power_law(x, a, b):
    return a * np.power(x, b)


def main():
    values = [1.45e6, 700e3, 340e3, 170e3, 88e3, 50e3, 31e3, 19.5e3, 13e3, 8.6e3, 6e3, 4.2e3, 3e3, 2.1e3, 1.55e3]
    y = np.array(range(20, 95, 5))
    x = np.array(values)
    params, covariance = curve_fit(power_law, x, y)
    a, b = params
    print(f"a: {a}, b: {b}")


if __name__ == '__main__':
    main()
