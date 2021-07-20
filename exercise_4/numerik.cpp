#include "numerik.hpp"

double newton(double (*fx)(double), float (*fderiv)(float), double x0, size_t n) {
    return GenericNewton<double, double, float>(fx, fderiv, x0, n);
};

template <typename newtonTemp, typename fxTemp, typename fderivTemp>
newtonTemp GenericNewton(fxTemp (*fx)(fxTemp), fderivTemp (*fderiv)(fderivTemp), newtonTemp x0, size_t n) {
    newtonTemp xN = x0;
    while(n-- > 0) {
        fxTemp p = fx(xN);
        fderivTemp q = fderiv(xN);
        if(q) xN = xN - p / q;
        else break;
    }
    return xN;
};