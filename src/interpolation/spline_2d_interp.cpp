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
    std::size_t n = _x.size();
    if (n < 2) {
        throw std::runtime_error(
            "Not enough data points for spline interpolation.");
    }

    h.resize(n - 1);
    a = _y;
    c.resize(n);
    b.resize(n - 1);
    d.resize(n - 1);

    for (std::size_t i = 0; i < n - 1; ++i) {
        h[i] = _x[i + 1] - _x[i];
        if (h[i] <= 0) {
            throw std::runtime_error("x data must be strictly increasing.");
        }
    }

    // Set up tridiagonal system for c coefficients
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n, n);
    Eigen::VectorXd rhs = Eigen::VectorXd::Zero(n);

    // Natural spline: c[0] = c[n-1] = 0
    A(0, 0) = 1.0;
    A(n - 1, n - 1) = 1.0;

    for (std::size_t i = 1; i < n - 1; ++i) {
        A(i, i - 1) = h[i - 1];
        A(i, i) = 2.0 * (h[i - 1] + h[i]);
        A(i, i + 1) = h[i];

        rhs(i) =
            3.0 * ((_y[i + 1] - _y[i]) / h[i] - (_y[i] - _y[i - 1]) / h[i - 1]);
    }

    // Solve for c
    Eigen::VectorXd c_eigen = A.colPivHouseholderQr().solve(rhs);
    for (std::size_t i = 0; i < n; ++i) {
        c[i] = c_eigen(i);
    }

    // Compute b and d
    for (std::size_t i = 0; i < n - 1; ++i) {
        d[i] = (c[i + 1] - c[i]) / (3.0 * h[i]);
        b[i] =
            (_y[i + 1] - _y[i]) / h[i] - h[i] * (2.0 * c[i] + c[i + 1]) / 3.0;
    }

    is_ready = true;
}

int Spline2DInterpolation::find_segment(double x) const {
    auto it = std::upper_bound(_x.begin(), _x.end(), x);
    int idx = std::max<int>(
        0, std::min<int>(_x.size() - 2, std::distance(_x.begin(), it) - 1));
    return idx;
}

double Spline2DInterpolation::polate(double x) {
    if (!is_ready) {
        throw std::runtime_error(
            "Spline not initialized. Call polation_setup() first.");
    }

    int i = find_segment(x);
    double dx = x - _x[i];
    return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
}