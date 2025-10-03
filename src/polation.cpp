#include <maptio/polation.hpp>

Polation::Polation(const std::vector<std::vector<double>>& dataset)
    : _dataset(dataset) {}

std::vector<double> Polation::polate(const std::vector<double>& x) {
    std::vector<double> results;
    for (double val : x) {
        results.push_back(polate(val));
    }
    return results;
}

std::vector<double> Polation2D::derivative(const std::vector<double>& x) {
    std::vector<double> results;
    for (double val : x) {
        results.push_back(derivative(val));
    }
    return results;
}

std::vector<double> Polation2D::integral(const std::vector<double>& a,
                                         const std::vector<double>& b) {
    std::vector<double> results;
    for (std::size_t i = 0; i < a.size(); ++i) {
        results.push_back(integral(a[i], b[i]));
    }
    return results;
}

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
