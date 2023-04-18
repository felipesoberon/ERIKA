#!/bin/bash

maximumEnergy=1500
stepEnergy=50
numberIons=1250
pressurePa=0.5
simulationTime=1e-6
simType=3
G2=0
spacerStack=2332
plasmaDensity=1e16
plasmaPotential=2000
gridTransparency=100
radioFrequency=13.56e6
electronTemperature=3

rm output/*.csv

start_time=$(date +%s)

./rfea -max_eV $maximumEnergy -step_eV $stepEnergy -no._ion $numberIons -pressure_Pa $pressurePa -sim_time $simulationTime -sim_type $simType -G2 $G2 -spacerStack $spacerStack -plasmaDensity $plasmaDensity -plasmaPotential $plasmaPotential -gridTransparency $gridTransparency -RF $radioFrequency -Te $electronTemperature

end_time=$(date +%s)

time_diff=$((end_time - start_time))
echo "  >> COMPLETED IN $time_diff seconds"
