#include <maptio/extrapolation/spline_2d_extrap.hpp>

Spline2DExtrapolation::Spline2DExtrapolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}
void Spline2DExtrapolation::polation_setup() {
    if (_x.size() < 4)
        throw std::runtime_error(
            "At least 4 points are required for extrapolation.");

    // Use first and second point for left extrapolation
    _x0 = _x[0];
    _x1 = _x[1];
    double y0 = _y[0];
    double y1 = _y[1];

    double h_l = _x1 - _x0;
    double dy_l = y1 - y0;

    // Assume quadratic behavior outside, construct cubic with 0 curvature at
    // boundary
    _a_l = y0;
    _b_l = dy_l / h_l;
    _c_l = 0.0;
    _d_l = 0.0;

    // Use last and second-to-last point for right extrapolation
    std::size_t n = _x.size();
    _x_n1 = _x[n - 2];
    _x_n = _x[n - 1];
    double y_n1 = _y[n - 2];
    double y_n = _y[n - 1];

    double h_r = _x_n - _x_n1;
    double dy_r = y_n - y_n1;

    _a_r = y_n;
    _b_r = dy_r / h_r;
    _c_r = 0.0;
    _d_r = 0.0;
}

double Spline2DExtrapolation::polate(double x) {
    if (x <= _x0) {
        double dx = x - _x0;
        return _a_l + _b_l * dx + _c_l * dx * dx + _d_l * dx * dx * dx;
    } else if (x >= _x_n) {
        double dx = x - _x_n;
        return _a_r + _b_r * dx + _c_r * dx * dx + _d_r * dx * dx * dx;
    } else {
        return 0.0;
    }
}

double Spline2DExtrapolation::derivative(double x) {
    if (x <= _x0) {
        double dx = x - _x0;
        return _b_l + 2.0 * _c_l * dx + 3.0 * _d_l * dx * dx;
    } else if (x >= _x_n) {
        double dx = x - _x_n;
        return _b_r + 2.0 * _c_r * dx + 3.0 * _d_r * dx * dx;
    } else {
        return 0.0;
    }
}

double Spline2DExtrapolation::integral(double x_i, double x_f) {
    if (x_f <= _x0) {
        double dx_i = x_i - _x0;
        double dx_f = x_f - _x0;
        return _a_l * (dx_f - dx_i) + _b_l * (dx_f * dx_f - dx_i * dx_i) / 2.0 +
               _c_l * (dx_f * dx_f * dx_f - dx_i * dx_i * dx_i) / 3.0 +
               _d_l * (dx_f * dx_f * dx_f * dx_f - dx_i * dx_i * dx_i * dx_i) /
                   4.0;
    } else if (x_i >= _x_n) {
        double dx_i = x_i - _x_n;
        double dx_f = x_f - _x_n;
        return _a_r * (dx_f - dx_i) + _b_r * (dx_f * dx_f - dx_i * dx_i) / 2.0 +
               _c_r * (dx_f * dx_f * dx_f - dx_i * dx_i * dx_i) / 3.0 +
               _d_r * (dx_f * dx_f * dx_f * dx_i) / 4.0;
    } else {
        double integral_left = 0.0;
        double integral_right = 0.0;
        if (x_i <= _x0) {
            double dx_i = _x0 - x_i;
            integral_left = _a_l * (dx_i)-_b_l * (dx_i * dx_i) / 2.0 +
                            _c_l * (dx_i * dx_i * dx_i) / 3.0 -
                            _d_l * (dx_i * dx_i * dx_i * dx_i) / 4.0;
        }
        if (x_f >= _x_n) {
            double dx_f = x_f - _x_n;
            integral_right = _a_r * (dx_f) + _b_r * (dx_f * dx_f) / 2.0 +
                             _c_r * (dx_f * dx_f * dx_f) / 3.0;
        }

        return integral_left + integral_right;
    }
}