#pragma once

#include <maptio/polation.hpp>
#include <memory>
#include <vector>

class Spline2DInterpolation : public Polation2D {
   public:
    explicit Spline2DInterpolation(
        const std::vector<std::vector<double>>& dataset);

    void polation_setup() override;
    double polate(double x) override;

   private:
    std::vector<double> a, b, c, d, h;
    bool is_ready = false;

    int find_segment(double x) const;
};