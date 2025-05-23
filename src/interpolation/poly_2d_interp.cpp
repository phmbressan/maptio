#include <boost/math/quadrature/trapezoidal.hpp>
#include <maptio/interpolation/poly_2d_interp.hpp>
#include <maptio/utils/utils.hpp>
#include <stdexcept>

Polynomial2DInterpolation::Polynomial2DInterpolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Polynomial2DInterpolation::polation_setup() {
    if (_x.size() < 2 || _y.size() < 2 || _x.size() != _y.size()) {
        throw std::runtime_error(
            "Invalid dataset for polynomial interpolation.");
    }

    interpolator =
        make_unique<boost::math::interpolators::barycentric_rational<double>>(
            _x.data(), _y.data(), _x.size());
}

double Polynomial2DInterpolation::polate(double x) {
    return (*interpolator)(x);
}

double Polynomial2DInterpolation::derivative(double x) {
    return interpolator->prime(x);
}

double Polynomial2DInterpolation::integral(double x_i, double x_f) {
    return boost::math::quadrature::trapezoidal(*interpolator, x_i, x_f);
}
