#include <maptio/extrapolation/constant_2d_extrap.hpp>

Constant2DExtrapolation::Constant2DExtrapolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Constant2DExtrapolation::polation_setup() {
    x_min = _x[0];
    x_max = _x[_data_length - 1];
    y_min = _y[0];
    y_max = _y[_data_length - 1];
}

double Constant2DExtrapolation::polate(double x) {
    if (x <= x_min)
        return y_min;
    if (x >= x_max)
        return y_max;
    return 0.0;
}