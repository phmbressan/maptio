#pragma once

#include <maptio/interpolation/akima_2d_interp.hpp>
#include <maptio/interpolation/linear_2d_interp.hpp>
#include <maptio/interpolation/poly_2d_interp.hpp>
#include <maptio/interpolation/spline_2d_interp.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <functional>

std::unique_ptr<Polation2D> interpolation_factory(
    const std::string& interpolation_type,
    const std::vector<std::vector<double>>& dataset);

