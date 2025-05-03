#include <maptio/extrapolation/constant_2d_extrap.hpp>
#include "test_2d_polation.hpp"

TEST_P(Constant2DExtrapolationScalarDataset,
       ScalarConstant2DExtrapolationParam) {
    Constant2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.polate(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(ScalarConstant2DExtrapolationTests,
                         Constant2DExtrapolationScalarDataset,
                         ::testing::Values(std::make_tuple(-1.0, 1.0),
                                           std::make_tuple(0.0, 1.0),
                                           std::make_tuple(2.0, 5.0),
                                           std::make_tuple(3.0, 5.0)));

TEST_P(Constant2DExtrapolationDerivativeDataset,
       DerivativeConstant2DExtrapolationParam) {
    Constant2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.derivative(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(DerivativeConstant2DExtrapolationTests,
                         Constant2DExtrapolationDerivativeDataset,
                         ::testing::Values(std::make_tuple(-1.0, 0.0),
                                           std::make_tuple(3.0, 0.0)));

TEST_P(Constant2DExtrapolationIntegralDataset,
       IntegralConstant2DExtrapolationParam) {
    Constant2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.integral(std::get<0>(x), std::get<1>(x));
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralConstant2DExtrapolationTests,
    Constant2DExtrapolationIntegralDataset,
    ::testing::Values(std::make_tuple(std::make_tuple(0.0, 2.0), 0.0),
                      std::make_tuple(std::make_tuple(-1.0, -0.5), 0.5),
                      std::make_tuple(std::make_tuple(2.5, 3.0), 2.5),
                      std::make_tuple(std::make_tuple(-2.0, 4.0), 12.0)));