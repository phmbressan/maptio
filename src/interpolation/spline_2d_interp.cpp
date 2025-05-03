#include <Eigen/Dense>
#include <algorithm>
#include <maptio/interpolation/spline_2d_interp.hpp>
#include <stdexcept>

Spline2DInterpolation::Spline2DInterpolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Spline2DInterpolation::polation_setup() {
    if (_data_length < 2 || _x.size() != _y.size())
        throw std::invalid_argument("Invalid dataset for spline interpolation");

    std::size_t n = _data_length - 1;
    _a = _y;
    _h.resize(n);

    for (std::size_t i = 0; i < n; ++i)
        _h[i] = _x[i + 1] - _x[i];

    Eigen::VectorXd alpha(n - 1);
    for (std::size_t i = 1; i < n; ++i)
        alpha[i - 1] = (3.0 / _h[i]) * (_a[i + 1] - _a[i]) -
                       (3.0 / _h[i - 1]) * (_a[i] - _a[i - 1]);

    // Tridiagonal system
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n - 1, n - 1);
    Eigen::VectorXd rhs = alpha;

    for (std::size_t i = 0; i < n - 1; ++i) {
        if (i > 0)
            A(i, i - 1) = _h[i];
        A(i, i) = 2.0 * (_h[i] + _h[i + 1]);
        if (i < n - 2)
            A(i, i + 1) = _h[i + 1];
    }

    Eigen::VectorXd c = Eigen::VectorXd::Zero(_data_length);
    if (n > 1)
        c.segment(1, n - 1) = A.colPivHouseholderQr().solve(rhs);

    _c.assign(c.data(), c.data() + _data_length);

    _b.resize(n);
    _d.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        _d[i] = (_c[i + 1] - _c[i]) / (3.0 * _h[i]);
        _b[i] = (_a[i + 1] - _a[i]) / _h[i] -
                _h[i] * (_c[i + 1] + 2.0 * _c[i]) / 3.0;
    }
    is_ready = true;
}

std::size_t Spline2DInterpolation::find_segment(double x) const {
    if (x <= _x[0])
        return 0;
    if (x >= _x[_data_length - 1])
        return _data_length - 2;

    auto it = std::upper_bound(_x.begin(), _x.end(), x);
    return std::max<std::ptrdiff_t>(0, std::distance(_x.begin(), it) - 1);
}

double Spline2DInterpolation::polate(double x) {
    if (!is_ready) {
        throw std::runtime_error(
            "Spline not initialized. Call polation_setup() first.");
    }

    std::size_t i = find_segment(x);
    double dx = x - _x[i];
    return _a[i] + _b[i] * dx + _c[i] * dx * dx + _d[i] * dx * dx * dx;
}

double Spline2DInterpolation::derivative(double x) {
    if (!is_ready) {
        throw std::runtime_error(
            "Spline not initialized. Call polation_setup() first.");
    }

    std::size_t i = find_segment(x);
    double dx = x - _x[i];
    return _b[i] + 2.0 * _c[i] * dx + 3.0 * _d[i] * dx * dx;
}

double Spline2DInterpolation::integral(double x_i, double x_f) {
    double integral = 0.0;
    std::size_t i_start = find_segment(x_i);
    std::size_t i_end = find_segment(x_f);

    if (i_start == i_end) {
        double dx = x_f - x_i;
        integral += integrate_interval(i_start, x_i, dx);
    } else {
        // First partial interval
        double dx = _x[i_start + 1] - x_i;
        integral += integrate_interval(i_start, x_i, dx);

        // Full intervals
        for (std::size_t i = i_start + 1; i < i_end; ++i)
            integral += integrate_interval(i, _x[i], _h[i]);

        // Last partial interval
        double dx_last = x_f - _x[i_end];
        integral += integrate_interval(i_end, _x[i_end], dx_last);
    }

    return integral;
}

double Spline2DInterpolation::integrate_interval(std::size_t i,
                                                 double x0,
                                                 double dx) const {
    double dx_rel = x0 - _x[i];
    return _a[i] * dx + _b[i] * dx * dx / 2.0 + _c[i] * dx * dx * dx / 3.0 +
           _d[i] * dx * dx * dx * dx / 4.0 + _b[i] * dx_rel * dx +
           _c[i] * dx_rel * dx * dx + _d[i] * dx_rel * dx * dx * dx;
}