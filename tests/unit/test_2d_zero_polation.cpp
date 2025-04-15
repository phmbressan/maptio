#include "test_2d_polation.hpp"
#include <maptio/extrapolation/zero_2d_extrap.hpp>

TEST_P(Zero2DExtrapolationScalarDataset, ScalarZero2DExtrapolationParam) {
    Zero2DExtrapolation extrapolator(dataset);
    extrapolator.polation_setup();

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.polate(x);
    EXPECT_DOUBLE_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(ScalarZero2DExtrapolationTests,
                         Zero2DExtrapolationScalarDataset,
                         ::testing::Values(std::make_tuple(-1.0, 0.0),
                                           std::make_tuple(0.0, 0.0),
                                           std::make_tuple(2.0, 0.0),
                                           std::make_tuple(3.0, 0.0)));