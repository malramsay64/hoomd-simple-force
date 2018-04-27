// Copyright (c) 2009-2017 The Regents of the University of Michigan
// This file is part of the HOOMD-blue project, released under the BSD 3-Clause
// License.

// Include the defined classes that are to be exported to python
#include "SimpleForce.h"

#include <hoomd/extern/pybind/include/pybind11/pybind11.h>

// specify the python module. Note that the name must expliclty match the
// PROJECT() name provided in CMakeLists (with an underscore in front)
PYBIND11_PLUGIN(_simple_force) {
    pybind11::module m("_simple_force");
    export_SimpleForce(m);

    return m.ptr();
}
