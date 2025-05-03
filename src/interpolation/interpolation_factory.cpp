#include <maptio/interpolation/interpolation_factory.hpp>
#include <maptio/utils/utils.hpp>

std::unordered_map<
    std::string,
    std::function<std::unique_ptr<Polation2D>(const std::vector<std::vector<double>>&)>>
    interpolation_map = {
        {"linear",
         [](const std::vector<std::vector<double>>& dataset) {
             return make_unique<Linear2DInterpolation>(dataset);
         }},
        {"spline",
         [](const std::vector<std::vector<double>>& dataset) {
             return make_unique<Spline2DInterpolation>(dataset);
         }},
        {"poly",
         [](const std::vector<std::vector<double>>& dataset) {
             return make_unique<Polynomial2DInterpolation>(dataset);
         }},
        {"akima",
         [](const std::vector<std::vector<double>>& dataset) {
             return make_unique<Akima2DInterpolation>(dataset);
         }}};

std::unique_ptr<Polation2D> interpolation_factory(
    const std::string& interpolation_type,
    const std::vector<std::vector<double>>& dataset) {
    
    auto it = interpolation_map.find(interpolation_type);
    if (it != interpolation_map.end()) {
        return it->second(dataset);
    } else {
        throw std::invalid_argument("Invalid interpolation type: " +
                                    interpolation_type);
    }
}