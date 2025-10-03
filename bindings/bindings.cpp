#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/unique_ptr.h>
#include <nanobind/stl/vector.h>
#include <nanobind/trampoline.h>
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

namespace nb = nanobind;

class PyPolation2D : public Polation2D {
   public:
    NB_TRAMPOLINE(Polation2D, 4);

    void polation_setup() override { NB_OVERRIDE_PURE(polation_setup); }
    double polate(double x) override { NB_OVERRIDE_PURE(polate, x); }
    double derivative(double x) override { NB_OVERRIDE_PURE(derivative, x); }
    double integral(double x_i, double x_f) override {
        NB_OVERRIDE_PURE(integral, x_i, x_f);
    }
};

NB_MODULE(maptio, m) {
    nb::class_<Polation2D, PyPolation2D>(m, "Polation2D")
        .def(nb::init<const std::vector<std::vector<double>>&>())
        .def("polation_setup", &Polation2D::polation_setup)
        .def("polate", nb::overload_cast<double>(&Polation2D::polate))
        .def("polate",
             nb::overload_cast<const std::vector<double>&>(&Polation2D::polate))
        .def("derivative", nb::overload_cast<double>(&Polation2D::derivative))
        .def("derivative", nb::overload_cast<const std::vector<double>&>(
                               &Polation2D::derivative))
        .def("integral",
             nb::overload_cast<double, double>(&Polation2D::integral))
        .def("integral", nb::overload_cast<const std::vector<double>&,
                                           const std::vector<double>&>(
                             &Polation2D::integral));

    nb::class_<Linear2DInterpolation, Polation2D>(m, "Linear2DInterpolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Spline2DInterpolation, Polation2D>(m, "Spline2DInterpolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Polynomial2DInterpolation, Polation2D>(
        m, "Polynomial2DInterpolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Akima2DInterpolation, Polation2D>(m, "Akima2DInterpolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Linear2DExtrapolation, Polation2D>(m, "Linear2DExtrapolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Spline2DExtrapolation, Polation2D>(m, "Spline2DExtrapolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Polynomial2DExtrapolation, Polation2D>(
        m, "Polynomial2DExtrapolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Akima2DExtrapolation, Polation2D>(m, "Akima2DExtrapolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Constant2DExtrapolation, Polation2D>(m,
                                                    "Constant2DExtrapolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());
    nb::class_<Zero2DExtrapolation, Polation2D>(m, "Zero2DExtrapolation")
        .def(nb::init<const std::vector<std::vector<double>>&>());

    m.def("interpolation_factory", &interpolation_factory,
          nb::arg("interpolation_type"), nb::arg("dataset"),
          "Factory function for interpolation");

    m.def("extrapolation_factory", &extrapolation_factory,
          nb::arg("extrapolation_type"), nb::arg("dataset"),
          "Factory function for extrapolation");
}
