#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <memory>

#include <maptio/extrapolation/akima_2d_extrap.hpp>
#include <maptio/extrapolation/constant_2d_extrap.hpp>
#include <maptio/extrapolation/extrapolation_factory.hpp>
#include <maptio/extrapolation/linear_2d_extrap.hpp>
#include <maptio/extrapolation/poly_2d_extrap.hpp>
#include <maptio/extrapolation/spline_2d_extrap.hpp>
#include <maptio/extrapolation/zero_2d_extrap.hpp>
#include <maptio/interpolation/akima_2d_interp.hpp>
#include <maptio/interpolation/interpolation_factory.hpp>
#include <maptio/interpolation/linear_2d_interp.hpp>
#include <maptio/interpolation/poly_2d_interp.hpp>
#include <maptio/interpolation/spline_2d_interp.hpp>
#include <maptio/polation.hpp>

namespace py = pybind11;

class PyPolation2D : public Polation2D {
   public:
    using Polation2D::Polation2D;

    void polation_setup() override {
        PYBIND11_OVERRIDE_PURE(void, Polation2D, polation_setup);
    }
    double polate(double x) override {
        PYBIND11_OVERRIDE_PURE(double, Polation2D, polate, x);
    }
    double derivative(double x) override {
        PYBIND11_OVERRIDE_PURE(double, Polation2D, derivative, x);
    }
    double integral(double x_i, double x_f) override {
        PYBIND11_OVERRIDE_PURE(double, Polation2D, integral, x_i, x_f);
    }
};

PYBIND11_MODULE(maptio, m) {
    py::class_<Polation2D, PyPolation2D, std::unique_ptr<Polation2D>>(
        m, "Polation2D")
        .def(py::init<const std::vector<std::vector<double>>&>())
        .def("polate",
             static_cast<double (Polation2D::*)(double)>(&Polation2D::polate),
             "Interpolate at a single point")
        .def("polate",
             static_cast<std::vector<double> (Polation2D::*)(
                 const std::vector<double>&)>(&Polation2D::polate),
             "Interpolate at a vector of points")
        .def("derivative",
             static_cast<double (Polation2D::*)(double)>(
                 &Polation2D::derivative),
             "Derivative at a single point")
        .def("derivative",
             static_cast<std::vector<double> (Polation2D::*)(
                 const std::vector<double>&)>(&Polation2D::derivative),
             "Derivative at a vector of points")
        .def("integral",
             static_cast<double (Polation2D::*)(double, double)>(
                 &Polation2D::integral),
             "Integral over an interval")
        .def("integral",
             static_cast<std::vector<double> (Polation2D::*)(
                 const std::vector<double>&, const std::vector<double>&)>(
                 &Polation2D::integral),
             "Integral over multiple intervals");

    py::class_<Linear2DInterpolation, Polation2D,
               std::unique_ptr<Linear2DInterpolation>>(m,
                                                       "Linear2DInterpolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Spline2DInterpolation, Polation2D,
               std::unique_ptr<Spline2DInterpolation>>(m,
                                                       "Spline2DInterpolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Polynomial2DInterpolation, Polation2D,
               std::unique_ptr<Polynomial2DInterpolation>>(
        m, "Polynomial2DInterpolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Akima2DInterpolation, Polation2D,
               std::unique_ptr<Akima2DInterpolation>>(m, "Akima2DInterpolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Linear2DExtrapolation, Polation2D,
               std::unique_ptr<Linear2DExtrapolation>>(m,
                                                       "Linear2DExtrapolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Spline2DExtrapolation, Polation2D,
               std::unique_ptr<Spline2DExtrapolation>>(m,
                                                       "Spline2DExtrapolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Polynomial2DExtrapolation, Polation2D,
               std::unique_ptr<Polynomial2DExtrapolation>>(
        m, "Polynomial2DExtrapolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Akima2DExtrapolation, Polation2D,
               std::unique_ptr<Akima2DExtrapolation>>(m, "Akima2DExtrapolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Constant2DExtrapolation, Polation2D,
               std::unique_ptr<Constant2DExtrapolation>>(
        m, "Constant2DExtrapolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    py::class_<Zero2DExtrapolation, Polation2D,
               std::unique_ptr<Zero2DExtrapolation>>(m, "Zero2DExtrapolation")
        .def(py::init<const std::vector<std::vector<double>>&>());

    m.def("interpolation_factory", &interpolation_factory,
          "Factory function for interpolation", py::arg("interpolation_type"),
          py::arg("dataset"));

    m.def("extrapolation_factory", &extrapolation_factory,
          "Factory function for extrapolation", py::arg("extrapolation_type"),
          py::arg("dataset"));
}