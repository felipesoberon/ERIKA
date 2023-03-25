#!/bin/bash

maximumEnergy=1500
stepEnergy=50
numberIons=5000
pressurePa=2.0
simulationTime=1e-6
simType=0
G2=250
spacerStack=2332
plasmaDensity=1e16
plasmaPotential=1000
gridTransparency=100
radioFrequency=0 #13.56e6

rm output/*.csv

./rfea -max_eV $maximumEnergy -step_eV $stepEnergy -no._ion $numberIons -pressure_Pa $pressurePa -sim_time $simulationTime -sim_type $simType -G2 $G2 -spacerStack $spacerStack -plasmaDensity $plasmaDensity -plasmaPotential $plasmaPotential -gridTransparency $gridTransparency -RF $radioFrequency


