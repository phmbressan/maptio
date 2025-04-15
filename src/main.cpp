#include <iostream>
#include <maptio/interpolation/linear_2d_interp.hpp>
#include <maptio/extrapolation/linear_2d_extrap.hpp>
#include <maptio/extrapolation/zero_2d_extrap.hpp>
#include <maptio/extrapolation/constant_2d_extrap.hpp>
#include <vector>

int main() {
    std::vector<std::vector<double>> dataset2D = {
        {0.0, 1.0}, {1.0, 3.0}, {2.0, 5.0}};

    Zero2DExtrapolation zeroExtrapolator(dataset2D);
    Linear2DExtrapolation linearExtrapolator(dataset2D);
    Linear2DInterpolation linearInterpolator(dataset2D);
    Constant2DExtrapolation constantExtrapolator(dataset2D);

    std::cout << "Linear Extrapolation at x = 2: "
              << linearExtrapolator.polate(2.0) << std::endl;
    std::cout << "Linear Interpolation at x = 2: "
              << linearInterpolator.polate(2.0) << std::endl;

    return 0;
}