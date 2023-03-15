#!/bin/bash

maximumEnergy=1500
stepEnergy=25
numberIons=5000
pressurePa=(0.5 1.0 2.5 5.0 7.5 10.0)
simulationTime=1e-6
ionTrajectory=0
RFEAscan=1
G2=100
spacerStack=2332
plasmaDensity=1e16

for pressure in ${pressurePa[@]}
do
	rm output/*.csv
	
	./rfea -max_eV $maximumEnergy -step_eV $stepEnergy -no._ion $numberIons -pressure_Pa $pressure -sim_time $simulationTime -ion_traj $ionTrajectory -RFEA_scan $RFEAscan -G2 $G2 -spacerStack $spacerStack -plasmaDensity $plasmaDensity

	cd output
	mkdir out$pressure 
	mv *.csv out$pressure
	cd .. 
done




