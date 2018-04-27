#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 Malcolm Ramsay <malramsay64@gmail.com>
#
# Distributed under terms of the MIT license.

import hoomd
import hoomd.simple_force
import hoomd.md
import numpy as np

context = hoomd.context.initialize("--notice-level=10 --mode=cpu")
uc = hoomd.lattice.unitcell(
    N=1,
    a1=[3, 0, 0],
    a2=[0, 3, 0],
    a3=[0, 0, 3],
    dimensions=2,
    position=[[0, 0, 0]],
    type_name=["R"],
    mass=[1.0],
    moment_inertia=[[1, 1, 1]],
    orientation=[[0.9, 0, 0, 0.2]],
)

system = hoomd.init.create_lattice(unitcell=uc, n=10)
system.particles.types.add("A")
pairs = hoomd.md.pair.lj(2.5, nlist=hoomd.md.nlist.cell())
pairs.pair_coeff.set("A", "A", epsilon=1.0, sigma=1.0)
pairs.pair_coeff.set("R", "A", epsilon=1.0, sigma=1.0)
pairs.pair_coeff.set("R", "R", epsilon=1.0, sigma=1.0)

rigid = hoomd.md.constrain.rigid()
rigid.set_param("R", types=["A"], positions=[(-1, 0, 0)])
rigid.create_bodies()

snap_init = system.take_snapshot()

hoomd.md.update.enforce2d()

hoomd.md.integrate.mode_standard(dt=0.005)
hoomd.md.integrate.nvt(hoomd.group.rigid_center(), kT=1, tau=1)

nmols = min(max(snap_init.particles.body) + 1, snap_init.particles.N)
print(nmols)
rc = hoomd.group.rigid_center()
force = hoomd.simple_force.SimpleForce(rc)
print(rc.cpp_group.getNumMembersGlobal())
hoomd.run(1000)
