#ifndef POLATION_HPP
#define POLATION_HPP

#include <vector>

class Polation {
   public:
    explicit Polation(const std::vector<std::vector<double> >& dataset)
        : _dataset(dataset) {}

    virtual void dataset(const std::vector<std::vector<double> >& dataset) = 0;
    virtual void polation_setup() = 0;
    virtual double polate(double x) = 0;

    std::vector<double> polate(const std::vector<double>& x) {
        std::vector<double> results;
        for (double val : x) {
            results.push_back(polate(val));
        }
        return results;
    }

   protected:
    std::vector<std::vector<double> > _dataset;
    std::size_t _data_length;
};

class Polation2D : public Polation {
   public:
    Polation2D(const std::vector<std::vector<double> >& dataset)
        : Polation(dataset) {
        this->dataset(dataset);
    }

    void dataset(const std::vector<std::vector<double> >& dataset) override {
        _dataset = dataset;
        _data_length = dataset.size();
        _x.resize(dataset.size());
        _y.resize(dataset.size());

        for (std::size_t i = 0; i < dataset.size(); ++i) {
            _x[i] = dataset[i][0];
            _y[i] = dataset[i][1];
        }
    }

   protected:
    std::vector<double> _x, _y;
};

class PolationND : public Polation {
   public:
    PolationND(const std::vector<std::vector<double> >& dataset)
        : Polation(dataset) {
        this->dataset(dataset);
    }

    void dataset(const std::vector<std::vector<double> >& dataset) override {
        _dataset = dataset;
        _data_length = dataset.size();
        _domain.resize(dataset.size());
        _image.resize(dataset.size());

        for (std::size_t i = 0; i < dataset.size(); ++i) {
            _domain[i] = dataset[i];
            _image[i] = dataset[i].back();
        }
    }

   protected:
    std::vector<std::vector<double> > _domain;
    std::vector<double> _image;
};

class Linear2DInterpolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Linear2DInterpolation(
        const std::vector<std::vector<double> >& dataset);

    void polation_setup() override;
    double polate(double x) override;
};

class Zero2DExtrapolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Zero2DExtrapolation(
        const std::vector<std::vector<double> >& dataset);

    void polation_setup() override;
    double polate(double x) override;
};

class Linear2DExtrapolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Linear2DExtrapolation(
        const std::vector<std::vector<double> >& dataset);

    void polation_setup() override;
    double polate(double x) override;

   private:
    double initial_slope, final_slope;
    double x_min, x_max, y_min, y_max;
};

class Constant2DExtrapolation : public Polation2D {
   public:
    using Polation::polate;
    explicit Constant2DExtrapolation(
        const std::vector<std::vector<double> >& dataset);

    void polation_setup() override;
    double polate(double x) override;

   private:
    double x_min, x_max, y_min, y_max;
};

#endif