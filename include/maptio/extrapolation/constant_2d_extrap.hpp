#pragma once

#include <maptio/polation.hpp>

class Constant2DExtrapolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Constant2DExtrapolation(
        const std::vector<std::vector<double> >& dataset);

    void polation_setup() override;
    double polate(double x) override;
    double derivative(double x) override;
    double integral(double x_i, double x_f) override;

   private:
    double x_min, x_max, y_min, y_max;
};