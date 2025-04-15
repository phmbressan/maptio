#pragma once

#include <maptio/polation.hpp>

#include <boost/math/interpolators/barycentric_rational.hpp>
#include <memory>

class Polynomial2DInterpolation : public Polation2D {
   public:
    explicit Polynomial2DInterpolation(
        const std::vector<std::vector<double>>& dataset);

    void polation_setup() override;
    double polate(double x) override;

   private:
    std::unique_ptr<boost::math::interpolators::barycentric_rational<double>>
        interpolator;
};
