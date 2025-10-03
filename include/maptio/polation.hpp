#pragma once

#include <vector>

class Polation {
   public:
    explicit Polation(const std::vector<std::vector<double>>& dataset);

    virtual void dataset(const std::vector<std::vector<double>>& dataset) = 0;
    virtual double polate(double x) = 0;

    std::vector<double> polate(const std::vector<double>& x);
    virtual void polation_setup() = 0;

   protected:
    std::vector<std::vector<double>> _dataset;
    std::size_t _data_length;
};

class Polation2D : public Polation {
   public:
    Polation2D(const std::vector<std::vector<double>>& dataset);

    void dataset(const std::vector<std::vector<double>>& dataset) override;

    virtual double derivative(double x) = 0;
    std::vector<double> derivative(const std::vector<double>& x);

    virtual double integral(double x_i, double x_f) = 0;
    std::vector<double> integral(const std::vector<double>& a,
                                 const std::vector<double>& b);

   protected:
    std::vector<double> _x, _y;
};

class PolationND : public Polation {
   public:
    PolationND(const std::vector<std::vector<double>>& dataset);

    void dataset(const std::vector<std::vector<double>>& dataset) override;

   protected:
    std::vector<std::vector<double>> _domain;
    std::vector<double> _image;
};