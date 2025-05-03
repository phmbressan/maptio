#pragma once

#include <maptio/polation.hpp>
#include <memory>
#include <vector>

class Spline2DInterpolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Spline2DInterpolation(
        const std::vector<std::vector<double>>& dataset);

    void polation_setup() override;
    double polate(double x) override;
    double derivative(double x) override;
    double integral(double x_i, double x_f) override;

   private:
    std::vector<double> _a, _b, _c, _d, _h;
    bool is_ready = false;

    std::size_t find_segment(double x) const;
    double integrate_interval(std::size_t i, double x0, double dx) const;
};