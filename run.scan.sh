#!/bin/bash

maximumEnergy=1500
stepEnergy=25
numberIons=500
pressurePa=1.9 #(0.5 1.0 2.5 5.0 7.5 10.0)
simulationTime=1e-6
simType=1
G2=100
spacerStack=2332
plasmaDensity=1e16
plasmaPotential=2000
gridTransparency=50
radioFrequency=13.56e6

for pressure in ${pressurePa[@]}
do
	rm output/*.csv
	
	./rfea -max_eV $maximumEnergy -step_eV $stepEnergy -no._ion $numberIons -pressure_Pa $pressurePa -sim_time $simulationTime -sim_type $simType -G2 $G2 -spacerStack $spacerStack -plasmaDensity $plasmaDensity -plasmaPotential $plasmaPotential	-gridTransparency $gridTransparency -RF $radioFrequency

	cd output
	mkdir out$pressure 
	mv *.csv out$pressure
	cd .. 
done




