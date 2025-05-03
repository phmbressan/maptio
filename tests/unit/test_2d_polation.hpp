#pragma once

#include <gtest/gtest.h>
#include <maptio/polation.hpp>
#include <utils/test_utils.hpp>

// Fixture
class LinearSampleDataset : public ::testing::Test {
   protected:
    std::vector<std::vector<double>> dataset;

    void SetUp() override {
        dataset = {{0.0, 1.0}, {0.5, 2.0}, {1.0, 3.0}, {2.0, 5.0}};
    }
};

// Parameterized test interface
class Linear2DInterpolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Linear2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Linear2DInterpolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Linear2DExtrapolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Linear2DInterpolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};
class Linear2DExtrapolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};

class Polynomial2DInterpolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Polynomial2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Polynomial2DInterpolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Polynomial2DExtrapolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Polynomial2DInterpolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};
class Polynomial2DExtrapolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};

class Akima2DInterpolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};

class Akima2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Akima2DInterpolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Akima2DExtrapolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Akima2DInterpolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};
class Akima2DExtrapolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};

class Spline2DInterpolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};

class Spline2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};

class Spline2DInterpolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Spline2DExtrapolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Spline2DInterpolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};
class Spline2DExtrapolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};

class Constant2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Constant2DExtrapolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Constant2DExtrapolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};

class Zero2DExtrapolationScalarDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Zero2DExtrapolationDerivativeDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<std::tuple<double, double>> {};
class Zero2DExtrapolationIntegralDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::tuple<double, double>, double>> {};

class Linear2DInterpolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};

class Linear2DExtrapolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};

class Polynomial2DInterpolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};

class Polynomial2DExtrapolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};

class Akima2DInterpolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};

class Akima2DExtrapolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};

class Spline2DInterpolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};

class Spline2DExtrapolationVectorDataset
    : public LinearSampleDataset,
      public ::testing::WithParamInterface<
          std::tuple<std::vector<double>, std::vector<double>>> {};
