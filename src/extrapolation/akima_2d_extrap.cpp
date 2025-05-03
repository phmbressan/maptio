#include <maptio/extrapolation/akima_2d_extrap.hpp>

Akima2DExtrapolation::Akima2DExtrapolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Akima2DExtrapolation::polation_setup() {
    std::size_t n = _x.size();
    if (n < 4)
        throw std::runtime_error(
            "Akima extrapolation requires at least 4 points.");

    std::vector<double> m(n - 1);
    for (std::size_t i = 0; i < n - 1; ++i) {
        double dx = _x[i + 1] - _x[i];
        if (dx == 0.0)
            throw std::runtime_error("Duplicate x-values detected.");
        m[i] = (_y[i + 1] - _y[i]) / dx;
    }

    std::vector<double> d(n);
    for (std::size_t i = 2; i < n - 2; ++i) {
        double w1 = std::abs(m[i + 1] - m[i]);
        double w2 = std::abs(m[i - 1] - m[i - 2]);
        if (w1 + w2 == 0.0)
            d[i] = (m[i - 1] + m[i]) / 2.0;
        else
            d[i] = (w1 * m[i - 1] + w2 * m[i]) / (w1 + w2);
    }

    // Use linear extrapolation for first two and last two slopes
    d[0] = m[0];
    d[1] = m[1];
    d[n - 2] = m[n - 2];
    d[n - 1] = m[n - 2];

    // Build left cubic using Hermite interpolation on [x0, x1]
    _x0 = _x[0];
    _x1 = _x[1];
    double h_l = _x1 - _x0;
    _a_l = _y[0];
    _b_l = d[0];
    _c_l = (3 * m[0] - 2 * d[0] - d[1]) / h_l;
    _d_l = (d[0] + d[1] - 2 * m[0]) / (h_l * h_l);

    // Right cubic using [xn1, xn]
    _xn1 = _x[n - 2];
    _xn = _x[n - 1];
    double h_r = _xn - _xn1;
    _a_r = _y[n - 1];
    _b_r = d[n - 1];
    _c_r = (3 * m[n - 2] - 2 * d[n - 1] - d[n - 2]) / h_r;
    _d_r = (d[n - 1] + d[n - 2] - 2 * m[n - 2]) / (h_r * h_r);
}

double Akima2DExtrapolation::polate(double x) {
    if (x <= _x0) {
        double dx = x - _x0;
        return _a_l + _b_l * dx + _c_l * dx * dx + _d_l * dx * dx * dx;
    } else if (x >= _xn) {
        double dx = x - _xn;
        return _a_r + _b_r * dx + _c_r * dx * dx + _d_r * dx * dx * dx;
    } else {
        return 0.0;
    }
}

double Akima2DExtrapolation::derivative(double x) {
    if (x <= _x0) {
        double dx = x - _x0;
        return _b_l + 2.0 * _c_l * dx + 3.0 * _d_l * dx * dx;
    } else if (x >= _xn) {
        double dx = x - _xn;
        return _b_r + 2.0 * _c_r * dx + 3.0 * _d_r * dx * dx;
    } else {
        return 0.0;
    }
}

double Akima2DExtrapolation::integral(double x_i, double x_f) {
    if (x_f <= _x0) {
        double dx_i = x_i - _x0;
        double dx_f = x_f - _x0;
        return _a_l * (dx_f - dx_i) + _b_l * (dx_f * dx_f - dx_i * dx_i) / 2.0 +
               _c_l * (dx_f * dx_f * dx_f - dx_i * dx_i * dx_i) / 3.0 +
               _d_l * (dx_f * dx_f * dx_f * dx_f - dx_i * dx_i * dx_i * dx_i) /
                   4.0;
    } else if (x_i >= _xn) {
        double dx_i = x_i - _xn;
        double dx_f = x_f - _xn;
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
        if (x_f >= _xn) {
            double dx_f = x_f - _xn;
            integral_right = _a_r * (dx_f) + _b_r * (dx_f * dx_f) / 2.0 +
                             _c_r * (dx_f * dx_f * dx_f) / 3.0;
        }

        return integral_left + integral_right;
    }
}