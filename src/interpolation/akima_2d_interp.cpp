#include <maptio/interpolation/akima_2d_interp.hpp>

#include <boost/math/interpolators/makima.hpp>
#include <boost/math/quadrature/trapezoidal.hpp>
#include <maptio/utils/utils.hpp>

Akima2DInterpolation::Akima2DInterpolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Akima2DInterpolation::polation_setup() {
    akima_spline = make_unique<
        boost::math::interpolators::makima<std::vector<double>>>(
        std::move(_x), std::move(_y));
}

double Akima2DInterpolation::polate(double x) {
    return (*akima_spline)(x);
}

double Akima2DInterpolation::derivative(double x) {
    return akima_spline->prime(x);
}

double Akima2DInterpolation::integral(double x_i, double x_f) {
    return boost::math::quadrature::trapezoidal(*akima_spline, x_i, x_f);
}