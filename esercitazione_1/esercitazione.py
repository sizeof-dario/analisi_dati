import numpy as np

def zeroin(x, y, f, tolx):
    a = x
    fa = f(x)
    b = x = y
    fb = f(x)

    interpolate = True

    while True:
        # interpolate
        if interpolate:
            c = a
            fc = fa

        # extrapolate
        if abs(fc) < abs(fb):
            a = b
            fa = fb
            x = b = c
            fb = fc
            c = a
            fc = fa

        tol = tolx
        m = (c + b) / 2
        if abs(m - b) > tol:
            p = (b - a) * fb
            if p >= 0:
                q = fa - fb
            else:
                q = fb - fa
                p = -p

            a = b
            fa = fb
            if p <= abs(q) * tol:
                x = b = np.sign(c - b) * tol + b
            elif p < (m - b) * q:
                x = b = p / q + b
            else:
                x = b = m

            fb = f(x)

            if np.sign(fb) == np.sign(fc):
                interpolate = True
            else:
                interpolate = False

            continue
        else:
            break

    y = c

    return np.sign(fb) * np.sign(fc) <= 0, x, y


function = lambda x : x**2 - 1

x = 0
y = 2
tol = 0.001

b, x, y = zeroin(x, y, function, tol)

print(f"({b}): [{x}, {y}]")
