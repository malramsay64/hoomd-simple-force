simple_force
============

This repository is the simplest example of a hoomd plugin computing a force.
It does nothing other than check the number of particles in the group passed to it
are no larger than the total number of particles in a simulation.
Currently this fails on linux,
with the groups having an absurdly large number of molecules on the order of 2 billion.

Install and Setup
-----------------

This install procedure assumes you have conda or miniconda installed on your system,
see the [conda user guide][conda install guide] for installation instructions.

To install and setup this module first clone this repository

```shell
$ git clone https://github.com/malramsay64/hoomd-simple-force
```

then to setup the conda environment run

```shell
$ conda env update
```

which will install all the prerequisites for compiling the plugin
as well as installing hoomd. 
Once this is completed the environment needs to be activated

```shell
$ conda activate hoomd-plugins
```

followed by the installation of the plugin with the command

```shell
$ make install
```

A demonstration of the failure can be run with

```shell
$ make test
```

which will result in the following error message

```python-traceback
**ERROR**: More particles in Group than in Simulation, group_size: 1318697904
Traceback (most recent call last):
  File "test/test_group.py", line 50, in <module>
    force = hoomd.simple_force.SimpleForce(rc)
  File "/home/malcolm/.miniconda/envs/hoomd-plugins/lib/python3.6/site-packages/hoomd/simple_force/force.py", line 47, in __init__
    hoomd.context.current.system_definition, group.cpp_group
RuntimeError: Error initializing SimpleForce
```

[conda install guide]: https://conda.io/docs/user-guide/install/index.html
