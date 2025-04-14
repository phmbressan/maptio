#pragma once

#include <gtest/gtest.h>
#include <maptio/polation.hpp>
#include <utils/test_utils.hpp>

// Fixture
class LinearSampleDataset : public ::testing::Test {
   protected:
    std::vector<std::vector<double>> dataset;

    void SetUp() override { dataset = {{0.0, 1.0}, {1.0, 3.0}, {2.0, 5.0}}; }
};

// Parameterized test interface
class Linear2DInterpolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Linear2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Constant2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Zero2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};

class Linear2DInterpolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};