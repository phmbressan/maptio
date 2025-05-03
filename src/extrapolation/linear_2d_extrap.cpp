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

double Linear2DExtrapolation::derivative(double x) {
    if (x <= x_min)
        return initial_slope;
    if (x >= x_max)
        return final_slope;
    return 0.0;
}

double Linear2DExtrapolation::integral(double x_i, double x_f) {
    double integral = 0.0;

    if (x_f <= x_min || x_i >= x_max) {
        return (x_f - x_i) * (polate(x_i) + polate(x_f)) / 2.0;
    }

    if (x_i <= x_min) {
        integral += (x_min - x_i) * (y_min + polate(x_i)) / 2.0;
    }
    if (x_f >= x_max) {
        integral += (x_f - x_max) * (y_max + polate(x_f)) / 2.0;
    }

    return integral;
}