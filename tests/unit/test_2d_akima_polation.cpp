#include <maptio/extrapolation/akima_2d_extrap.hpp>
#include <maptio/interpolation/akima_2d_interp.hpp>
#include "test_2d_polation.hpp"

TEST_P(Akima2DInterpolationScalarDataset, ScalarAkima2DInterpolationParam) {
    Akima2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.polate(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(ScalarAkima2DInterpolationTests,
                         Akima2DInterpolationScalarDataset,
                         ::testing::Values(std::make_tuple(0.0, 1.0),
                                           std::make_tuple(1.0, 3.0),
                                           std::make_tuple(1.5, 4.0),
                                           std::make_tuple(2.0, 5.0)));

TEST_P(Akima2DInterpolationVectorDataset, VectorAkima2DInterpolationParam) {
    Akima2DInterpolation interpolator(dataset);

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
    VectorAkima2DInterpolationTests,
    Akima2DInterpolationVectorDataset,
    ::testing::Values(std::make_tuple(std::vector<double>{0.5, 1.0, 1.5},
                                      std::vector<double>{2.0, 3.0, 4.0}),
                      std::make_tuple(linspace(0.0, 2.0, 100),
                                      transform_vector(linspace(0.0, 2.0, 100),
                                                       [](double x) {
                                                           return 1.0 + 2.0 * x;
                                                       }))));

TEST_P(Akima2DExtrapolationScalarDataset, ScalarAkima2DExtrapolationParam) {
    Akima2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.polate(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(ScalarAkima2DExtrapolationTests,
                         Akima2DExtrapolationScalarDataset,
                         ::testing::Values(std::make_tuple(-1.0, -1.0),
                                           std::make_tuple(0.0, 1.0),
                                           std::make_tuple(2.0, 5.0),
                                           std::make_tuple(3.0, 7.0)));

TEST_P(Akima2DInterpolationDerivativeDataset,
       DerivativeAkima2DInterpolationParam) {
    Akima2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.derivative(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(DerivativeAkima2DInterpolationTests,
                         Akima2DInterpolationDerivativeDataset,
                         ::testing::Values(std::make_tuple(0.0, 2.0),
                                           std::make_tuple(0.25, 2.0),
                                           std::make_tuple(1.5, 2.0),
                                           std::make_tuple(2.0, 2.0)));

TEST_P(Akima2DExtrapolationDerivativeDataset,
       DerivativeAkima2DExtrapolationParam) {
    Akima2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.derivative(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(DerivativeAkima2DExtrapolationTests,
                         Akima2DExtrapolationDerivativeDataset,
                         ::testing::Values(std::make_tuple(-1.0, 2.0),
                                           std::make_tuple(3.0, 2.0)));

TEST_P(Akima2DInterpolationIntegralDataset, IntegralAkima2DInterpolationParam) {
    Akima2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.integral(std::get<0>(x), std::get<1>(x));
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralAkima2DInterpolationTests,
    Akima2DInterpolationIntegralDataset,
    ::testing::Values(std::make_tuple(std::make_tuple(0.0, 2.0), 6.0),
                      std::make_tuple(std::make_tuple(0.5, 1.5), 3.0),
                      std::make_tuple(std::make_tuple(0.0, 1.5), 3.75),
                      std::make_tuple(std::make_tuple(1.5, 2.0), 2.25)));

TEST_P(Akima2DExtrapolationIntegralDataset, IntegralAkima2DExtrapolationParam) {
    Akima2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.integral(std::get<0>(x), std::get<1>(x));
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralAkima2DExtrapolationTests,
    Akima2DExtrapolationIntegralDataset,
    ::testing::Values(std::make_tuple(std::make_tuple(0.0, 2.0), 0.0),
                      std::make_tuple(std::make_tuple(-1.0, -0.5), -0.25),
                      std::make_tuple(std::make_tuple(2.5, 3.0), 3.25),
                      std::make_tuple(std::make_tuple(-2.0, 4.0), 12.0)));