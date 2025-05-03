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

double Constant2DExtrapolation::derivative(double x) {
    return 0.0;
}

double Constant2DExtrapolation::integral(double x_i, double x_f) {
    if (x_f <= x_min) {
        return (x_f - x_i) * y_min;
    }
    if (x_i >= x_max) {
        return (x_f - x_i) * y_max;
    }
    
    double integral = 0.0;

    if (x_i <= x_min) {
        integral += (x_min - x_i) * y_min;
    }
    if (x_f >= x_max) {
        integral += (x_f - x_max) * y_max;
    }

    return integral;
}