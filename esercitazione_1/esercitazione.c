#include <stdbool.h>
#include <stdio.h>

#define ABS(x) ((x) > 0 ? (x) : -(x))
#define SIGN(x) ((x) == 0 ? 0 : ((x) / ABS(x)))

bool zeroin(double *x_ptr, double *y_ptr, double (*f)(double), double tolx)
{
    double a, fa, b, fb, c, fc, tol, m, p, q;

    a = *x_ptr;
    fa = f(*x_ptr);
    b = *x_ptr = *y_ptr;
    fb = f(*x_ptr);

interpolate:
    c = a;
    fc = fa;

extrapolate:
    if (ABS(fc) < ABS(fb)) {
        a = b;
        fa = fb;
        *x_ptr = b = c;
        fb = fc;
        c = a;
        fc = fa;
    }

    tol = tolx;
    m = (c + b) / 2;
    if (ABS(m - b) > tol) {
        p = (b - a) * fb;
        if (p >= 0) {
            q = fa - fb;
        } else {
            q = fb - fa;
            p = -p;
        }
        a = b;
        fa = fb;
        *x_ptr = b = (p <= ABS(q) * tol) ? (SIGN(c - b) * tol + b) : \
            ((p < (m - b) * q) ? (p / q + b ): m);
        fb = f(*x_ptr);

        if (SIGN(fb) == SIGN(fc)) {
            goto interpolate;
        } else {
            goto extrapolate;
        }
    }

    *y_ptr = c;

    return (SIGN(fb) * SIGN(fc) <= 0);
}



double function(double x)
{
    return x*x - 1;
}

int main()
{
    double x, y, tol;
    double (*f)(double) = &function;
    bool b;

    x = 0;
    y = 2;
    
    tol = 0.001;

    b = zeroin(&x, &y, f, tol);
    printf("(%d): [%f, %f]\n", b, x, y);
}