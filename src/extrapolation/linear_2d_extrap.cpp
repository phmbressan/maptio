#include <maptio/extrapolation/linear_2d_extrap.hpp>

Linear2DExtrapolation::Linear2DExtrapolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Linear2DExtrapolation::polation_setup() {
    initial_slope = (_y[1] - _y[0]) / (_x[1] - _x[0]);
    final_slope = (_y[_data_length - 1] - _y[_data_length - 2]) /
                  (_x[_data_length - 1] - _x[_data_length - 2]);
    x_min = _x[0];
    x_max = _x[_data_length - 1];
    y_min = _y[0];
    y_max = _y[_data_length - 1];
}

double Linear2DExtrapolation::polate(double x) {
    if (x <= x_min)
        return (x - x_min) * initial_slope + y_min;
    if (x >= x_max)
        return (x - x_max) * final_slope + y_max;
    return 0.0;
}