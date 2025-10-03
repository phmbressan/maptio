#pragma once

#include <maptio/polation.hpp>

#include <boost/math/interpolators/barycentric_rational.hpp>
#include <memory>

class Polynomial2DExtrapolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Polynomial2DExtrapolation(
        const std::vector<std::vector<double>>& dataset);

    void polation_setup() override;
    double polate(double x) override;
    double derivative(double x) override;
    double integral(double x_i, double x_f) override;

   private:
    std::unique_ptr<boost::math::interpolators::barycentric_rational<double>>
        extrapolator;
};