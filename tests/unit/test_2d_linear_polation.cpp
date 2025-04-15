#include "test_2d_polation.hpp"
#include <maptio/interpolation/linear_2d_interp.hpp>
#include <maptio/extrapolation/linear_2d_extrap.hpp>


TEST_P(Linear2DInterpolationScalarDataset, ScalarLinear2DInterpolationParam) {
    Linear2DInterpolation interpolator(dataset);
    interpolator.polation_setup();

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = interpolator.polate(x);
    EXPECT_DOUBLE_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(ScalarLinear2DInterpolationTests,
                         Linear2DInterpolationScalarDataset,
                         ::testing::Values(std::make_tuple(0.0, 1.0),
                                           std::make_tuple(1.0, 3.0),
                                           std::make_tuple(1.5, 4.0),
                                           std::make_tuple(2.0, 5.0)));

TEST_P(Linear2DInterpolationVectorDataset,
       VectorizedLinear2DInterpolationParam) {
    Linear2DInterpolation interpolator(dataset);
    interpolator.polation_setup();

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
    VectorizedLinear2DInterpolationTests,
    Linear2DInterpolationVectorDataset,
    ::testing::Values(std::make_tuple(std::vector<double>{0.5, 1.0, 1.5},
                                      std::vector<double>{2.0, 3.0, 4.0}),
                      std::make_tuple(linspace(0.0, 2.0, 100),
                                      transform_vector(linspace(0.0, 2.0, 100),
                                                       [](double x) {
                                                           return 1.0 + 2.0 * x;
                                                       }))));

TEST_P(Linear2DExtrapolationScalarDataset, ScalarLinear2DExtrapolationParam) {
    Linear2DExtrapolation extrapolator(dataset);
    extrapolator.polation_setup();

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.polate(x);
    EXPECT_DOUBLE_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(ScalarLinear2DExtrapolationTests,
                         Linear2DExtrapolationScalarDataset,
                         ::testing::Values(std::make_tuple(-1.0, -1.0),
                                           std::make_tuple(0.0, 1.0),
                                           std::make_tuple(2.0, 5.0),
                                           std::make_tuple(3.0, 7.0)));