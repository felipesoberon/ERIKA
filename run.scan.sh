#!/bin/bash

maximumEnergy=1500
stepEnergy=50
numberIons=5000
pressurePa=1.0
simulationTime=1e-6
ionTrajectory=0
RFEAscan=1
G2=100
spacerStack=2332
plasmaDensity=1e16

rm output/*.csv

./rfea -max_eV $maximumEnergy -step_eV $stepEnergy -no._ion $numberIons -pressure_Pa $pressurePa -sim_time $simulationTime -ion_traj $ionTrajectory -RFEA_scan $RFEAscan -G2 $G2 -spacerStack $spacerStack -plasmaDensity $plasmaDensity


