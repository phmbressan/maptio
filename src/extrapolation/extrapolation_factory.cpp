#include <maptio/extrapolation/extrapolation_factory.hpp>
#include <memory>

std::unordered_map<std::string,
                   std::function<std::unique_ptr<Polation2D>(
                       const std::vector<std::vector<double>>&)>>
    extrapolation_map = {
        {"linear",
         [](const std::vector<std::vector<double>>& dataset) {
             return std::make_unique<Linear2DExtrapolation>(dataset);
         }},
        {"spline",
         [](const std::vector<std::vector<double>>& dataset) {
             return std::make_unique<Spline2DExtrapolation>(dataset);
         }},
        {"poly",
         [](const std::vector<std::vector<double>>& dataset) {
             return std::make_unique<Polynomial2DExtrapolation>(dataset);
         }},
        {"akima",
         [](const std::vector<std::vector<double>>& dataset) {
             return std::make_unique<Akima2DExtrapolation>(dataset);
         }},
        {"constant",
         [](const std::vector<std::vector<double>>& dataset) {
             return std::make_unique<Constant2DExtrapolation>(dataset);
         }},
        {"zero", [](const std::vector<std::vector<double>>& dataset) {
             return std::make_unique<Zero2DExtrapolation>(dataset);
         }}};

std::unique_ptr<Polation2D> extrapolation_factory(
    const std::string& extrapolation_type,
    const std::vector<std::vector<double>>& dataset) {
    auto it = extrapolation_map.find(extrapolation_type);
    if (it != extrapolation_map.end()) {
        return it->second(dataset);
    } else {
        throw std::invalid_argument("Invalid extrapolation type: " +
                                    extrapolation_type);
    }
}