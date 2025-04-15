#include "test_2d_polation.hpp"
#include <maptio/extrapolation/constant_2d_extrap.hpp>

TEST_P(Constant2DExtrapolationScalarDataset,
       ScalarConstant2DExtrapolationParam) {
    Constant2DExtrapolation extrapolator(dataset);
    extrapolator.polation_setup();

    auto param = GetParam();
    const auto& x = std::get<0>(param);
    const auto& expected = std::get<1>(param);

    double result = extrapolator.polate(x);
    EXPECT_DOUBLE_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(ScalarConstant2DExtrapolationTests,
                         Constant2DExtrapolationScalarDataset,
                         ::testing::Values(std::make_tuple(-1.0, 1.0),
                                           std::make_tuple(0.0, 1.0),
                                           std::make_tuple(2.0, 5.0),
                                           std::make_tuple(3.0, 5.0)));