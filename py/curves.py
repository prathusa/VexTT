from dataclasses import dataclass
from matplotlib import pyplot as plt
import numpy as np
from scipy.interpolate import CubicSpline

@dataclass
class Point:
    x: float
    y: float   


x = np.linspace(0.1, 1, 100)
rng = np.random.default_rng()
y = np.log(x) + rng.random(100)

def parameterize(t, p0, p1):
    return  [p0[0]*(1-t)+p1[0]*t, p0[1]*(1-t)+p1[1]*t]

def quad(t, p0, p1, p2):
    return parameterize(t, parameterize(t, p0, p1), parameterize(t, p1, p2))

def bezier(t, p0, p1, p2, p3):
    return parameterize(t, quad(t, p0, p1, p2), quad(t, p1, p2, p3))

def ninterpolation(t, points):
    # print('points len', len(points))
    n = len(points)
    if n == 2:
        # print('n == 2')
        return parameterize(t, points[0], points[1])
    else:
        # print(f'n == {n}')
        # print('splitting: ', points[::n], points[1::])
        return parameterize(t, ninterpolation(t, points[:n-1]), ninterpolation(t, points[1:n]))
    

def bez():
    
    # x = np.array([0, 0, 2.4, 3.6])
    # y = np.array([1, 3, .3, .2])
    
    # p = list(zip(x, y))
    p = np.column_stack((x, y)).tolist()[:21]
    # print(p)
    t = x #np.linspace(0, 1, 100)
    fig = plt.figure()
    cubic = ninterpolation(t, p)
    # cubic = bezier(t, p[0], p[1], p[2], p[3])
    plt.plot(cubic[0], cubic[1], 'b')
    plt.plot(x, y, 'ro')
    plt.title('Bezier Curve Interpolation')
    plt.show()
    # rng = np.random.default_rng()
    # p = list(zip(x, y))
    # fig = plt.figure()
    # for i in range(len(p) - 4):
    #     cubic = bezier(x[i:i+30], p[i], p[(i+1)], p[(i+2)], p[(i+3)])
    #     plt.plot(cubic[0], cubic[1], label=f'{i}')
    
    
    # p0 = points.pop(0)
    # p1 = points.pop(0)
    # p2 = points.pop(0)
    # # q0 = parameterize(t, p0, p1)
    # fig = plt.figure()
    # for i, p in enumerate(points[:- 2]):
    #     linear = parameterize(t, p0, p)
    #     quadratic = quad(t, p0, p1, p)
    #     cubic = bezier(t, p0, p1, p2, p)
    #     # plt.plot([p.x for p in points], [p.y for p in points], 'ro')
    #     # plt.plot(linear.x, linear.y, label=f'{i}')
    #     # plt.plot(quadratic.x, quadratic.y, label=f'{i}')
    #     plt.plot(cubic.x, cubic.y, label=f'{i}')
    #     p0 = p1
    #     p1 = p2
    #     p2 = p
    
    # quadratic = quad(t, p0, p1, p2)
    # cubic = bezier(t, p0, p1, p2, p3)
    # plt.plot(linear0.x, linear0.y)
    # plt.plot(linear1.x, linear1.y)
    # plt.plot(linear2.x, linear2.y)
    # plt.plot(quadratic.x, quadratic.y)
    # plt.plot(cubic.x, cubic.y)
    
    plt.show()
    
# spline function
def spline():
    f = CubicSpline(x, y, bc_type='natural')
    x_new = x
    y_new = f(x_new)
    plt.figure(figsize = (10,8))
    plt.plot(x_new, y_new, 'b')
    plt.plot(x, y, 'ro')
    plt.title('Cubic Spline Interpolation')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()
    
if __name__ == "__main__":
    bez()
    spline()