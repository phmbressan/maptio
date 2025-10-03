#pragma once

#include <maptio/polation.hpp>
#include <memory>
#include <vector>

class Spline2DInterpolation : public Polation2D {
   public:
    using Polation::polate;
    using Polation2D::derivative;
    using Polation2D::integral;

    explicit Spline2DInterpolation(
        const std::vector<std::vector<double>>& dataset);

    void dataset(const std::vector<std::vector<double>>& dataset) override;

    void polation_setup() override;
    double polate(double x) override;
    double derivative(double x) override;
    double integral(double x_i, double x_f) override;

   private:
    std::size_t find_interval(double x) const;
    double integral_segment(std::size_t i) const;
    double eval_indefinite_integral(double x, std::size_t i) const;

    // Second derivatives (spline coefficients)
    std::vector<double> _m;
};
