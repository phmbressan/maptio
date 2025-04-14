#include <algorithm>
#include <maptio/polation.hpp>

Linear2DInterpolation::Linear2DInterpolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {}

void Linear2DInterpolation::polation_setup() {}

double Linear2DInterpolation::polate(double x) {
    auto it = std::lower_bound(_x.begin() + 1, _x.end(), x);
    size_t index = std::distance(_x.begin(), it);

    if (index == 0 || index >= _x.size())
        return _y[0];

    return (_y[index] - _y[index - 1]) * (x - _x[index - 1]) /
               (_x[index] - _x[index - 1]) +
           _y[index - 1];
}
