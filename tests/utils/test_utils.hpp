#pragma once

#include <cstddef>
#include <functional>
#include <vector>

inline std::vector<double> linspace(double start, double end, std::size_t num) {
    std::vector<double> result;
    if (num == 0)
        return result;
    if (num == 1) {
        result.push_back(start);
        return result;
    }

    double step = (end - start) / static_cast<double>(num - 1);
    result.reserve(num);

    for (std::size_t i = 0; i < num; ++i) {
        result.push_back(start + i * step);
    }

    return result;
}

inline std::vector<double> transform_vector(
    const std::vector<double>& input,
    const std::function<double(double)>& func) {
    std::vector<double> output;
    output.reserve(input.size());

    for (double x : input) {
        output.push_back(func(x));
    }

    return output;
}
