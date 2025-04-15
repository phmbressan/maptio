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
