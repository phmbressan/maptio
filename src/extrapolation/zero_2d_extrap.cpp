#include <maptio/extrapolation/zero_2d_extrap.hpp>

Zero2DExtrapolation::Zero2DExtrapolation(
    const std::vector<std::vector<double>>& dataset)
    : Polation2D(dataset) {
    this->polation_setup();
}

void Zero2DExtrapolation::polation_setup() {}

double Zero2DExtrapolation::polate(double x) {
    return 0.0;
}

double Zero2DExtrapolation::derivative(double x) {
    return 0.0;
}

double Zero2DExtrapolation::integral(double x_i, double x_f) {
    return 0.0;
}
