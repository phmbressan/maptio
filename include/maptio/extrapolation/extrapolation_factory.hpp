#pragma once

#include <maptio/extrapolation/akima_2d_extrap.hpp>
#include <maptio/extrapolation/linear_2d_extrap.hpp>
#include <maptio/extrapolation/poly_2d_extrap.hpp>
#include <maptio/extrapolation/spline_2d_extrap.hpp>
#include <maptio/extrapolation/constant_2d_extrap.hpp>
#include <maptio/extrapolation/zero_2d_extrap.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <functional>

std::unique_ptr<Polation2D> extrapolation_factory(
    const std::string& extrapolation_type,
    const std::vector<std::vector<double>>& dataset);
