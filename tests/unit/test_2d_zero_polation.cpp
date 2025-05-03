#include <maptio/extrapolation/zero_2d_extrap.hpp>
#include "test_2d_polation.hpp"

TEST_P(Zero2DExtrapolationScalarDataset, ScalarZero2DExtrapolationParam) {
    Zero2DExtrapolation extrapolator(dataset);
    extrapolator.polation_setup();

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.polate(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(ScalarZero2DExtrapolationTests,
                         Zero2DExtrapolationScalarDataset,
                         ::testing::Values(std::make_tuple(-1.0, 0.0),
                                           std::make_tuple(0.0, 0.0),
                                           std::make_tuple(2.0, 0.0),
                                           std::make_tuple(3.0, 0.0)));

TEST_P(Zero2DExtrapolationDerivativeDataset,
       DerivativeZero2DExtrapolationParam) {
    Zero2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.derivative(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(DerivativeZero2DExtrapolationTests,
                         Zero2DExtrapolationDerivativeDataset,
                         ::testing::Values(std::make_tuple(-1.0, 0.0),
                                           std::make_tuple(3.0, 0.0)));

TEST_P(Zero2DExtrapolationIntegralDataset, IntegralZero2DExtrapolationParam) {
    Zero2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.integral(std::get<0>(x), std::get<1>(x));
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralZero2DExtrapolationTests,
    Zero2DExtrapolationIntegralDataset,
    ::testing::Values(std::make_tuple(std::make_tuple(0.0, 2.0), 0.0),
                      std::make_tuple(std::make_tuple(-1.0, -0.5), 0.0),
                      std::make_tuple(std::make_tuple(2.5, 3.0), 0.0),
                      std::make_tuple(std::make_tuple(-2.0, 4.0), 0.0)));