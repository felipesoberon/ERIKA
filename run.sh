#!/bin/bash

maximumEnergy=1500
stepEnergy=50
numberIons=5000
pressurePa=5.0
simulationTime=1e-6
simType=2
G2=25
spacerStack=2332
plasmaDensity=1e16
plasmaPotential=1000
gridTransparency=75

rm output/*.csv

./rfea -max_eV $maximumEnergy -step_eV $stepEnergy -no._ion $numberIons -pressure_Pa $pressurePa -sim_time $simulationTime -sim_type $simType -G2 $G2 -spacerStack $spacerStack -plasmaDensity $plasmaDensity -plasmaPotential $plasmaPotential -gridTransparency $gridTransparency


