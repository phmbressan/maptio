#include <pybind11/pybind11.h>
#include "maptio/polation.hpp"

namespace py = pybind11;

PYBIND11_MODULE(maptio, m) {
    m.doc() = "Python bindings for maptio";

    m.def("interpolate", &maptio::interpolate, "Linear interpolation");
    m.def("extrapolate", &maptio::extrapolate, "Linear extrapolation");
}