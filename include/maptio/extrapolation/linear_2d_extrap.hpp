#pragma once

#include <maptio/polation.hpp>

class Linear2DExtrapolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Linear2DExtrapolation(
        const std::vector<std::vector<double> >& dataset);

    void polation_setup() override;
    double polate(double x) override;
    double derivative(double x) override;
    double integral(double x_i, double x_f) override;

   private:
    double initial_slope, final_slope;
    double x_min, x_max, y_min, y_max;
};