#include <maptio/interpolation/spline_2d_interp.hpp>
#include <maptio/extrapolation/spline_2d_extrap.hpp>
#include "test_2d_polation.hpp"

TEST_P(Spline2DInterpolationScalarDataset, ScalarSpline2DInterpolationParam) {
    Spline2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.polate(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(ScalarSpline2DInterpolationTests,
                         Spline2DInterpolationScalarDataset,
                         ::testing::Values(std::make_tuple(0.0, 1.0),
                                           std::make_tuple(1.0, 3.0),
                                           std::make_tuple(1.5, 4.0),
                                           std::make_tuple(2.0, 5.0)));

TEST_P(Spline2DInterpolationVectorDataset, VectorSpline2DInterpolationParam) {
    Spline2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x_vals = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    std::vector<double> results = interpolator.polate(x_vals);

    ASSERT_EQ(results.size(), expected.size());
    for (size_t i = 0; i < results.size(); ++i) {
        EXPECT_DOUBLE_EQ(results[i], expected[i]);
    }
}

INSTANTIATE_TEST_SUITE_P(
    VectorSpline2DInterpolationTests,
    Spline2DInterpolationVectorDataset,
    ::testing::Values(std::make_tuple(std::vector<double>{0.5, 1.0, 1.5},
                                      std::vector<double>{2.0, 3.0, 4.0}),
                      std::make_tuple(linspace(0.0, 2.0, 100),
                                      transform_vector(linspace(0.0, 2.0, 100),
                                                       [](double x) {
                                                           return 1.0 + 2.0 * x;
                                                       }))));

TEST_P(Spline2DExtrapolationScalarDataset, ScalarSpline2DExtrapolationParam) {
    Spline2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.polate(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(ScalarSpline2DExtrapolationTests,
                         Spline2DExtrapolationScalarDataset,
                         ::testing::Values(std::make_tuple(-1.0, -1.0),
                                           std::make_tuple(0.0, 1.0),
                                           std::make_tuple(2.0, 5.0),
                                           std::make_tuple(3.0, 7.0)));

TEST_P(Spline2DInterpolationDerivativeDataset,
       DerivativeSpline2DInterpolationParam) {
    Spline2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.derivative(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(DerivativeSpline2DInterpolationTests,
                         Spline2DInterpolationDerivativeDataset,
                         ::testing::Values(std::make_tuple(0.0, 2.0),
                                           std::make_tuple(0.25, 2.0),
                                           std::make_tuple(1.5, 2.0),
                                           std::make_tuple(2.0, 2.0)));

TEST_P(Spline2DExtrapolationDerivativeDataset,
       DerivativeSpline2DExtrapolationParam) {
    Spline2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.derivative(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(DerivativeSpline2DExtrapolationTests,
                         Spline2DExtrapolationDerivativeDataset,
                         ::testing::Values(std::make_tuple(-1.0, 2.0),
                                           std::make_tuple(3.0, 2.0)));

TEST_P(Spline2DInterpolationIntegralDataset, IntegralSpline2DInterpolationParam) {
    Spline2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.integral(std::get<0>(x), std::get<1>(x));
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralSpline2DInterpolationTests,
    Spline2DInterpolationIntegralDataset,
    ::testing::Values(std::make_tuple(std::make_tuple(0.0, 2.0), 6.0),
                      std::make_tuple(std::make_tuple(0.5, 1.5), 3.0),
                      std::make_tuple(std::make_tuple(0.0, 1.5), 3.75),
                      std::make_tuple(std::make_tuple(1.5, 2.0), 2.25)));

TEST_P(Spline2DExtrapolationIntegralDataset, IntegralSpline2DExtrapolationParam) {
    Spline2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.integral(std::get<0>(x), std::get<1>(x));
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralSpline2DExtrapolationTests,
    Spline2DExtrapolationIntegralDataset,
    ::testing::Values(std::make_tuple(std::make_tuple(0.0, 2.0), 0.0),
                      std::make_tuple(std::make_tuple(-1.0, -0.5), -0.25),
                      std::make_tuple(std::make_tuple(2.5, 3.0), 3.25),
                      std::make_tuple(std::make_tuple(-2.0, 4.0), 12.0)));
