#include <maptio/extrapolation/poly_2d_extrap.hpp>
#include <maptio/interpolation/poly_2d_interp.hpp>
#include "test_2d_polation.hpp"

TEST_P(Polynomial2DInterpolationScalarDataset, ScalarPolynomial2DInterpolationParam) {
    Polynomial2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.polate(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(ScalarPolynomial2DInterpolationTests,
                         Polynomial2DInterpolationScalarDataset,
                         ::testing::Values(std::make_tuple(0.0, 1.0),
                                           std::make_tuple(1.0, 3.0),
                                           std::make_tuple(1.5, 4.0),
                                           std::make_tuple(2.0, 5.0)));

TEST_P(Polynomial2DInterpolationVectorDataset, VectorPolynomial2DInterpolationParam) {
    Polynomial2DInterpolation interpolator(dataset);

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
    VectorPolynomial2DInterpolationTests,
    Polynomial2DInterpolationVectorDataset,
    ::testing::Values(std::make_tuple(std::vector<double>{0.5, 1.0, 1.5},
                                      std::vector<double>{2.0, 3.0, 4.0}),
                      std::make_tuple(linspace(0.0, 2.0, 100),
                                      transform_vector(linspace(0.0, 2.0, 100),
                                                       [](double x) {
                                                           return 1.0 + 2.0 * x;
                                                       }))));

TEST_P(Polynomial2DExtrapolationScalarDataset,
       ScalarPolynomial2DExtrapolationParam) {
    Polynomial2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.polate(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(ScalarPolynomial2DExtrapolationTests,
                         Polynomial2DExtrapolationScalarDataset,
                         ::testing::Values(std::make_tuple(-1.0, -1.0),
                                           std::make_tuple(0.0, 1.0),
                                           std::make_tuple(2.0, 5.0),
                                           std::make_tuple(3.0, 7.0)));

TEST_P(Polynomial2DInterpolationDerivativeDataset,
       DerivativePolynomial2DInterpolationParam) {
    Polynomial2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.derivative(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(DerivativePolynomial2DInterpolationTests,
                         Polynomial2DInterpolationDerivativeDataset,
                         ::testing::Values(std::make_tuple(0.0, 2.0),
                                           std::make_tuple(0.25, 2.0),
                                           std::make_tuple(1.5, 2.0),
                                           std::make_tuple(2.0, 2.0)));

TEST_P(Polynomial2DExtrapolationDerivativeDataset,
       DerivativePolynomial2DExtrapolationParam) {
    Polynomial2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.derivative(x);
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(DerivativePolynomial2DExtrapolationTests,
                         Polynomial2DExtrapolationDerivativeDataset,
                         ::testing::Values(std::make_tuple(-1.0, 2.0),
                                           std::make_tuple(3.0, 2.0)));

TEST_P(Polynomial2DInterpolationIntegralDataset,
       IntegralPolynomial2DInterpolationParam) {
    Polynomial2DInterpolation interpolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.integral(std::get<0>(x), std::get<1>(x));
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralPolynomial2DInterpolationTests,
    Polynomial2DInterpolationIntegralDataset,
    ::testing::Values(std::make_tuple(std::make_tuple(0.0, 2.0), 6.0),
                      std::make_tuple(std::make_tuple(0.5, 1.5), 3.0),
                      std::make_tuple(std::make_tuple(0.0, 1.5), 3.75),
                      std::make_tuple(std::make_tuple(1.5, 2.0), 2.25)));

TEST_P(Polynomial2DExtrapolationIntegralDataset,
       IntegralPolynomial2DExtrapolationParam) {
    Polynomial2DExtrapolation extrapolator(dataset);

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.integral(std::get<0>(x), std::get<1>(x));
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralPolynomial2DExtrapolationTests,
    Polynomial2DExtrapolationIntegralDataset,
    ::testing::Values(std::make_tuple(std::make_tuple(0.0, 2.0), 0.0),
                      std::make_tuple(std::make_tuple(-1.0, -0.5), -0.25),
                      std::make_tuple(std::make_tuple(2.5, 3.0), 3.25),
                      std::make_tuple(std::make_tuple(-2.0, 4.0), 12.0)));
