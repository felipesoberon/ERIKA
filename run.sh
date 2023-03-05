#!/bin/bash

maximumEnergy=1500
stepEnergy=50
numberIons=5000
pressurePa=1.0
simulationTime=1E-6

rm output/*.csv

./rfea -max_eV $maximumEnergy -step_eV $stepEnergy -no._ion $numberIons -pressure_Pa $pressurePa -sim_time $simulationTime


