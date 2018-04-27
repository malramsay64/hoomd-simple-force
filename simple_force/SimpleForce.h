// Copyright (c) 2009-2017 The Regents of the University of Michigan
// This file is part of the HOOMD-blue project, released under the BSD 3-Clause
// License.

// **********************
// This is a simple example code written for no function purpose other then to
// demonstrate the steps needed to write a c++ source code plugin for
// HOOMD-Blue. This example includes an example Updater class, but it can just
// as easily be replaced with a ForceCompute, Integrator, or any other C++ code
// at all.

// inclusion guard
#ifndef _EXAMPLE_UPDATER_H_
#define _EXAMPLE_UPDATER_H_

/*! \file ExampleUpdater.h
    \brief Declaration of ExampleUpdater
*/

#include <hoomd/ForceCompute.h>

// pybind11 is used to create the python bindings to the C++ object,
// but not if we are compiling GPU kernels
#ifndef NVCC
#include <hoomd/extern/pybind/include/pybind11/pybind11.h>
#endif

// (if you really don't want to include the whole hoomd.h, you can include
// individual files IF AND ONLY IF hoomd_config.h is included first) For
// example: #include <hoomd/Updater.h>

// Second, we need to declare the class. One could just as easily use any class
// in HOOMD as a template here, there are no restrictions on what a template can
// do

//! A nonsense particle updater written to demonstrate how to write a plugin
/*! This updater simply sets all of the particle's velocities to 0 when update()
 * is called.
 */
class SimpleForce : public ForceCompute {
   public:
    //! Constructor
    SimpleForce(std::shared_ptr<SystemDefinition> sysdef,
                std::shared_ptr<ParticleGroup> group);

    //! Take one timestep forward
    virtual void computeForces(unsigned int timestep);

    std::shared_ptr<ParticleGroup> m_group;

    unsigned int last_computed;
};

//! Export the ExampleUpdater class to python
void export_SimpleForce(pybind11::module& m);

// Third, this class offers a GPU accelerated method in order to demonstrate how
// to include CUDA code in pluins we need to declare a separate class for that
// (but only if ENABLE_CUDA is set)

#endif  // _EXAMPLE_UPDATER_H_
