#include <iostream>
#include <maptio/extrapolation/constant_2d_extrap.hpp>
#include <maptio/extrapolation/linear_2d_extrap.hpp>
#include <maptio/extrapolation/zero_2d_extrap.hpp>
#include <maptio/interpolation/akima_2d_interp.hpp>
#include <maptio/interpolation/linear_2d_interp.hpp>
#include <maptio/interpolation/poly_2d_interp.hpp>
#include <maptio/interpolation/spline_2d_interp.hpp>
#include <vector>

int main() {
    std::vector<std::vector<double>> dataset2D = {
        {0.0, 1.0}, {1.0, 3.0}, {2.0, 5.0}, {3.0, 7.0}};

    std::vector<std::vector<double>> dataset_diff = {
        {0.0, 1.0}, {0.5, 2.0}, {1.0, 3.0}, {2.0, 5.0}
    };

    Zero2DExtrapolation zeroExtrapolator(dataset2D);
    Linear2DExtrapolation linearExtrapolator(dataset2D);
    Constant2DExtrapolation constantExtrapolator(dataset2D);
    Linear2DInterpolation linearInterpolator(dataset2D);
    Akima2DInterpolation akimaInterpolator(dataset2D);
    Spline2DInterpolation splineInterpolator(dataset2D);
    Polynomial2DInterpolation polynomialInterpolator(dataset2D);

    // std::cout << "Akima Extrapolation at x = 2: "
    //           << akimaExtrapolator.polate(2.0) << std::endl;
    std::cout << "Linear Interpolation at x = 2.5: "
              << linearInterpolator.polate(2.5) << std::endl;
    std::cout << "Akima Interpolation at x = 2.5: "
              << akimaInterpolator.polate(2.5) << std::endl;
    std::cout << "Spline Interpolation at x = 2.5: "
              << splineInterpolator.polate(2.5) << std::endl;
    std::cout << "Polynomial Interpolation at x = 2.5: "
              << polynomialInterpolator.polate(2.5) << std::endl;

    Linear2DInterpolation linearInterpolator2(dataset_diff);
    Spline2DInterpolation splineInterpolator2(dataset_diff);
    splineInterpolator2.polate(0.7);
    std::cout << "Linear derivative at x = 0.0: "
              << splineInterpolator2.integral(1.5,2.0) << std::endl;

    std::cout << "Linear integral at x = 0.0: "
              << linearInterpolator2.integral(0.0,2.0) << std::endl;

    return 0;
}