#pragma once

#include <boost/math/interpolators/makima.hpp>
#include <maptio/polation.hpp>
#include <vector>

class Akima2DInterpolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Akima2DInterpolation(
        const std::vector<std::vector<double>>& dataset);

    void polation_setup() override;
    double polate(double x) override;
    double derivative(double x) override;
    double integral(double x_i, double x_f) override;

   private:
    std::unique_ptr<boost::math::interpolators::makima<std::vector<double>>>
        akima_spline;
};