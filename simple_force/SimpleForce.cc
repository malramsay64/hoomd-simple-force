// Copyright (c) 2009-2017 The Regents of the University of Michigan
// This file is part of the HOOMD-blue project, released under the BSD 3-Clause
// License.

#include "SimpleForce.h"

/*! \file ExampleUpdater.cc
    \brief Definition of ExampleUpdater
*/

// ********************************
// here follows the code for ExampleUpdater on the CPU

/*! \param sysdef System to zero the velocities of
 */
SimpleForce::SimpleForce(std::shared_ptr<SystemDefinition> sysdef,
                         std::shared_ptr<ParticleGroup> group)
    : ForceCompute(sysdef), m_group(group) {
    unsigned int group_size = m_group->getNumMembersGlobal();
    unsigned int sys_size = m_pdata->getN();
    if (group_size >= sys_size) {
        m_exec_conf->msg->error()
            << "More particles in Group than in Simulation, group_size: " << group_size << std::endl;
        throw std::runtime_error("Error initializing SimpleForce");
    }
}

/*! Perform the needed calculations to zero the system's velocity
    \param timestep Current time step of the simulation
*/
void SimpleForce::computeForces(unsigned int timestep) {
    if (last_computed != timestep)
        {
            last_computed = timestep;
        }
}

/* Export the CPU updater to be visible in the python module
 */
void export_SimpleForce(pybind11::module& m) {
    pybind11::class_<SimpleForce, std::shared_ptr<SimpleForce> >(
        m, "SimpleForce", pybind11::base<ForceCompute>())
        .def(pybind11::init<std::shared_ptr<SystemDefinition>,
                            std::shared_ptr<ParticleGroup> >());
}
