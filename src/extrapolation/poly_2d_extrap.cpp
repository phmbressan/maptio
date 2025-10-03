#include <boost/math/quadrature/trapezoidal.hpp>
#include <maptio/extrapolation/poly_2d_extrap.hpp>
#include <memory>
#include <stdexcept>

Polynomial2DExtrapolation::Polynomial2DExtrapolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Polynomial2DExtrapolation::polation_setup() {
    if (_x.size() < 2 || _y.size() < 2 || _x.size() != _y.size()) {
        throw std::runtime_error(
            "Invalid dataset for polynomial extrapolation.");
    }

    extrapolator = std::make_unique<
        boost::math::interpolators::barycentric_rational<double>>(
        _x.data(), _y.data(), _x.size());
}

double Polynomial2DExtrapolation::polate(double x) {
    if (x > _x[0] && x < _x[_data_length - 1]) {
        return 0.0;
    }
    return (*extrapolator)(x);
}

double Polynomial2DExtrapolation::derivative(double x) {
    if (x > _x[0] && x < _x[_data_length - 1]) {
        return 0.0;
    }
    return extrapolator->prime(x);
}

double Polynomial2DExtrapolation::integral(double x_i, double x_f) {
    if (x_f <= _x[0] || x_i >= _x[_data_length - 1]) {
        return boost::math::quadrature::trapezoidal(*extrapolator, x_i, x_f);
    }

    double integral = 0.0;

    if (x_i < _x[0]) {
        integral +=
            boost::math::quadrature::trapezoidal(*extrapolator, x_i, _x[0]);
    }
    if (x_f > _x[_data_length - 1]) {
        integral += boost::math::quadrature::trapezoidal(
            *extrapolator, _x[_data_length - 1], x_f);
    }

    return integral;
}
