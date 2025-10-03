#include <algorithm>
#include <maptio/interpolation/linear_2d_interp.hpp>

Linear2DInterpolation::Linear2DInterpolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {}

void Linear2DInterpolation::polation_setup() {}

double Linear2DInterpolation::polate(double x) {
    auto it = std::lower_bound(_x.begin() + 1, _x.end(), x);
    size_t index = std::distance(_x.begin(), it);

    return (_y[index] - _y[index - 1]) * (x - _x[index - 1]) /
               (_x[index] - _x[index - 1]) +
           _y[index - 1];
}

double Linear2DInterpolation::derivative(double x) {
    auto it = std::lower_bound(_x.begin() + 1, _x.end(), x);
    size_t index = std::distance(_x.begin(), it);

    return (_y[index] - _y[index - 1]) / (_x[index] - _x[index - 1]);
}

double Linear2DInterpolation::integral(double x_i, double x_f) {
    auto it_i = std::upper_bound(_x.begin(), _x.end() - 1, x_i);
    auto it_f = std::upper_bound(_x.begin(), _x.end() - 1, x_f);
    size_t index_i = std::distance(_x.begin(), it_i);
    size_t index_f = std::distance(_x.begin(), it_f);

    double integral = 0.0;

    if (index_i == index_f) {
        return (x_f - x_i) * (polate(x_i) + polate(x_f)) / 2.0;
    }

    integral += (_x[index_i] - x_i) * (_y[index_i] + polate(x_i)) / 2.0;

    for (size_t i = index_i; i < index_f - 1; ++i) {
        integral += (_y[i] + _y[i + 1]) * (_x[i + 1] - _x[i]) / 2.0;
    }

    integral += (x_f - _x[index_f - 1]) * (_y[index_f - 1] + polate(x_f)) / 2.0;

    return integral;
}