#pragma once
#include <cstddef>

double newton(double (*fx)(double), float (*fderiv)(float), double x0, size_t n);

template <typename newtonTemp, typename fxTemp, typename fderivTemp>
newtonTemp GenericNewton(fxTemp (*fx)(fxTemp), fderivTemp (*fderiv)(fderivTemp), newtonTemp x0, size_t n);