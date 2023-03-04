#!/bin/bash

maximumEnergy=1500
stepEnergy=25
numberIons=50
pressurePa=1.0
simulationTime=1E-6

rm output/*.csv

./rfea -max_eV $maximumEnergy -step_eV $stepEnergy -no._ion $numberIons -pressure_Pa $pressurePa -sim_time $simulationTime


