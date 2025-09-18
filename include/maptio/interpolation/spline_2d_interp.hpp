#pragma once

#include <maptio/polation.hpp>
#include <memory>
#include <vector>

class Spline2DInterpolation : public Polation2D {
public:
    using Polation::polate; // Make vector overload visible
    using Polation2D::derivative; // Make vector overload visible
    using Polation2D::integral;   // Make vector overload visible

    explicit Spline2DInterpolation(const std::vector<std::vector<double>>& dataset);

    void dataset(const std::vector<std::vector<double>>& dataset) override;

    void polation_setup() override;
    double polate(double x) override;
    double derivative(double x) override;
    double integral(double x_i, double x_f) override;

private:
    std::size_t find_interval(double x) const;
    double integral_segment(std::size_t i) const;
    double eval_indefinite_integral(double x, std::size_t i) const;

    // Store the second derivatives (spline coefficients)
    std::vector<double> _m; 
};
