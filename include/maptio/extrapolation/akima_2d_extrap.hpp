#pragma once

#include <algorithm>
#include <cmath>
#include <maptio/polation.hpp>
#include <stdexcept>
#include <vector>

class Akima2DExtrapolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Akima2DExtrapolation(
        const std::vector<std::vector<double>>& dataset);

    void polation_setup() override;
    double polate(double x) override;
    double derivative(double x) override;
    double integral(double x_i, double x_f) override;

   private:
   double _x0, _x1, _xn1, _xn;
   double _a_l, _b_l, _c_l, _d_l;
   double _a_r, _b_r, _c_r, _d_r;
};