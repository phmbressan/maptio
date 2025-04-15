#include <maptio/interpolation/akima_2d_interp.hpp>

#include <boost/math/interpolators/makima.hpp>

Akima2DInterpolation::Akima2DInterpolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Akima2DInterpolation::polation_setup() {
    akima_spline.reset(
        new boost::math::interpolators::makima<std::vector<double>>(
            std::move(_x), std::move(_y)));
}

double Akima2DInterpolation::polate(double x) {
    return (*akima_spline)(x);
}