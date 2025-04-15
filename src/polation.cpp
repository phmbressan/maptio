#include <maptio/polation.hpp>

// ----- Polation -----
Polation::Polation(const std::vector<std::vector<double>>& dataset)
    : _dataset(dataset) {}

// Default implementation for vector polation (delegates to scalar)
std::vector<double> Polation::polate(const std::vector<double>& x) {
    std::vector<double> results;
    for (double val : x) {
        results.push_back(polate(val));
    }
    return results;
}

// ----- Polation2D -----
Polation2D::Polation2D(const std::vector<std::vector<double>>& dataset)
    : Polation(dataset) {
    this->dataset(dataset);
}

void Polation2D::dataset(const std::vector<std::vector<double>>& dataset) {
    _dataset = dataset;
    _data_length = dataset.size();
    _x.resize(dataset.size());
    _y.resize(dataset.size());

    for (std::size_t i = 0; i < dataset.size(); ++i) {
        _x[i] = dataset[i][0];
        _y[i] = dataset[i][1];
    }
}

// ----- PolationND -----
PolationND::PolationND(const std::vector<std::vector<double>>& dataset)
    : Polation(dataset) {
    this->dataset(dataset);
}

void PolationND::dataset(const std::vector<std::vector<double>>& dataset) {
    _dataset = dataset;
    _data_length = dataset.size();
    _domain.resize(dataset.size());
    _image.resize(dataset.size());

    for (std::size_t i = 0; i < dataset.size(); ++i) {
        _domain[i] = dataset[i];
        _image[i] = dataset[i].back();
    }
}
