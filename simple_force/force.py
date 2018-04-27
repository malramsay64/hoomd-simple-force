# Copyright (c) 2009-2017 The Regents of the University of Michigan
# This file is part of the HOOMD-blue project, released under the BSD 3-Clause License.

# this simple python interface just actiavates the c++ ExampleUpdater from cppmodule
# Check out any of the python code in lib/hoomd-python-module/hoomd_script for moreexamples

# Next, since we are extending an updater, we need to bring in the base class updater and some other parts from
# hoomd_script
import hoomd
import hoomd.md
from hoomd.md.force import _force

# First, we need to import the C++ module. It has the same name as this module (example_plugin) but with an underscore
# in front
from hoomd.simple_force import _simple_force

## Zeroes all particle velocities
#
# Every \a period time steps, particle velocities are modified so that they are all zero
#


class SimpleForce(_force):
    ## Initialize the velocity zeroer
    #
    # \param period Velocities will be zeroed every \a period time steps
    #
    # \b Examples:
    # \code
    # example_plugin.update.example()
    # zeroer = example_plugin.update.example(period=10)
    # \endcode
    #
    # \a period can be a function: see \ref variable_period_docs for details

    def __init__(self, group=None):
        hoomd.util.print_status_line()

        # initialize base class
        _force.__init__(self)

        if group is None:
            group = hoomd.group.all()

        # initialize the reflected c++ class
        self.cpp_force = _simple_force.SimpleForce(
            hoomd.context.current.system_definition, group.cpp_group
        )
        hoomd.context.current.system.addCompute(self.cpp_force, self.force_name)

    def update_coeffs(self):
        pass
