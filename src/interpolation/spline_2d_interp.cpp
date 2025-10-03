#include <algorithm>
#include <maptio/interpolation/spline_2d_interp.hpp>
#include <stdexcept>

Spline2DInterpolation::Spline2DInterpolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Spline2DInterpolation::dataset(
    const std::vector<std::vector<double>>& dataset) {
    Polation2D::dataset(dataset);
    this->polation_setup();
}

void Spline2DInterpolation::polation_setup() {
    if (_data_length < 2) {
        throw std::runtime_error(
            "Spline interpolation requires at least 2 data points.");
    }

    for (size_t i = 0; i < _data_length - 1; ++i) {
        if (_x[i] >= _x[i + 1]) {
            throw std::runtime_error(
                "Dataset must be sorted by x-values for spline interpolation.");
        }
    }

    if (_data_length == 2) {
        _m.assign(2, 0.0);
        return;
    }

    const std::size_t n = _data_length;
    const std::size_t system_size = n - 2;
    std::vector<double> a(system_size), b(system_size), c(system_size),
        d(system_size);

    for (std::size_t i = 0; i < system_size; ++i) {
        const double h_i = _x[i + 1] - _x[i];
        const double h_i1 = _x[i + 2] - _x[i + 1];

        // Main diagonal
        b[i] = 2.0 * (h_i + h_i1);

        // Lower and upper diagonals
        if (i > 0)
            a[i] = h_i;
        if (i < system_size - 1)
            c[i] = h_i1;

        // Right-hand side vector
        d[i] =
            6.0 * ((_y[i + 2] - _y[i + 1]) / h_i1 - (_y[i + 1] - _y[i]) / h_i);
    }

    // Thomas algorithm for solving the tridiagonal system
    // Forward elimination
    for (std::size_t i = 1; i < system_size; ++i) {
        double factor = a[i] / b[i - 1];
        b[i] -= factor * c[i - 1];
        d[i] -= factor * d[i - 1];
    }

    // Back substitution
    std::vector<double> m_internal(system_size);
    m_internal[system_size - 1] = d[system_size - 1] / b[system_size - 1];
    for (long i = system_size - 2; i >= 0; --i) {
        m_internal[i] = (d[i] - c[i] * m_internal[i + 1]) / b[i];
    }

    // Store final coefficients including boundaries
    _m.resize(n);
    _m[0] = 0.0;
    _m[n - 1] = 0.0;
    for (std::size_t i = 0; i < system_size; ++i) {
        _m[i + 1] = m_internal[i];
    }
}

std::size_t Spline2DInterpolation::find_interval(double x) const {
    if (x < _x.front() || x > _x.back()) {
        throw std::out_of_range("Input x is outside the interpolation range.");
    }

    auto it = std::upper_bound(_x.begin(), _x.end(), x);
    auto i = std::distance(_x.begin(), it) - 1;

    return std::max(static_cast<std::size_t>(0),
                    std::min(static_cast<std::size_t>(i), _data_length - 2));
}

double Spline2DInterpolation::polate(double x) {
    if (_data_length < 2)
        return 0.0;

    const std::size_t i = find_interval(x);
    const double h_i = _x[i + 1] - _x[i];

    const double A = (_x[i + 1] - x) / h_i;
    const double B = (x - _x[i]) / h_i;

    return A * _y[i] + B * _y[i + 1] +
           (h_i * h_i / 6.0) *
               ((A * A * A - A) * _m[i] + (B * B * B - B) * _m[i + 1]);
}

double Spline2DInterpolation::derivative(double x) {
    if (_data_length < 2)
        return 0.0;

    const std::size_t i = find_interval(x);
    const double h_i = _x[i + 1] - _x[i];

    const double term1 = (_y[i + 1] - _y[i]) / h_i;
    const double term2 =
        -(3.0 * (_x[i + 1] - x) * (_x[i + 1] - x) - h_i * h_i) / (6.0 * h_i) *
        _m[i];
    const double term3 =
        (3.0 * (x - _x[i]) * (x - _x[i]) - h_i * h_i) / (6.0 * h_i) * _m[i + 1];

    return term1 + term2 + term3;
}

double Spline2DInterpolation::integral(double x_i, double x_f) {
    if (_data_length < 2)
        return 0.0;

    bool swapped = false;
    if (x_i > x_f) {
        std::swap(x_i, x_f);
        swapped = true;
    }

    const std::size_t start_idx = find_interval(x_i);
    const std::size_t end_idx = find_interval(x_f);

    double total_integral = 0.0;

    if (start_idx == end_idx) {
        total_integral = eval_indefinite_integral(x_f, start_idx) -
                         eval_indefinite_integral(x_i, start_idx);
    } else {
        total_integral +=
            eval_indefinite_integral(_x[start_idx + 1], start_idx) -
            eval_indefinite_integral(x_i, start_idx);

        for (std::size_t i = start_idx + 1; i < end_idx; ++i) {
            total_integral += integral_segment(i);
        }

        total_integral += eval_indefinite_integral(x_f, end_idx) -
                          eval_indefinite_integral(_x[end_idx], end_idx);
    }

    return swapped ? -total_integral : total_integral;
}

double Spline2DInterpolation::integral_segment(std::size_t i) const {
    const double h_i = _x[i + 1] - _x[i];
    return (h_i / 2.0) * (_y[i] + _y[i + 1]) -
           (h_i * h_i * h_i / 24.0) * (_m[i] + _m[i + 1]);
}

double Spline2DInterpolation::eval_indefinite_integral(double x,
                                                       std::size_t i) const {
    const double h_i = _x[i + 1] - _x[i];
    const double dx_i = x - _x[i];
    const double dx_i1 = _x[i + 1] - x;

    const double term_y_i =
        (_y[i] / h_i - _m[i] * h_i / 6.0) * (-(dx_i1 * dx_i1) / 2.0);
    const double term_y_i1 =
        (_y[i + 1] / h_i - _m[i + 1] * h_i / 6.0) * ((dx_i * dx_i) / 2.0);
    const double term_m_i =
        _m[i] / (6.0 * h_i) * (-(dx_i1 * dx_i1 * dx_i1 * dx_i1) / 4.0);
    const double term_m_i1 =
        _m[i + 1] / (6.0 * h_i) * ((dx_i * dx_i * dx_i * dx_i) / 4.0);

    return term_y_i + term_y_i1 + term_m_i + term_m_i1;
}