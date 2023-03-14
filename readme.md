# ERIKA: Simulation of Ar+ Ions Transported Across a Plasma Sheath and Through a Retarding Field Energy Analyzer

**E**mulating
**R**etarding-Field-Energy-Analyzer
**I**on
**K**inetic-transport-in
**A**rgon-gas

This software is a computer simulation that models the transport of Ar+ ions across a plasma sheath and into a retarding field energy analyzer (RFEA). The motion of the ions is integrated in the Z-axis, from the edge of the plasma sheath. The model includes Monte-Carlo ion collisions with the background gas (neutral argon). The collision frequency is determined by the background neutral gas concentration (determined by the pressure and temperature of gas), and collision cross sections for elastic collisions and charge exchange collisions.

The model can be used to simulate individual trajectories or the aggregate of multiple trajectories to produce an RFEA current, which can be used to produce an ion energy distribution function (IEDF) by taking the first derivative of the current. The model also keeps a record of the energy of ions crossing the first grid of the RFEA, G0, which can be used to determine the IEDF prior to ions entering the RFEA. 

These two distributions can be compared to determine potential effects due to the RFEA design. For example, effects due to background gas pressure which may distort the IEDF due to collisions within the RFEA. The model allows for trying different distances for the grids in the RFEA by using a standard thickness spacer of 100 um and a stack input. For example, 2332, meaning 2 spacers between G0 and G1, etc. 

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The simulation is designed for use by researchers and engineers who are interested in understanding the behavior of Ar+ ions in plasma sheaths and how they interact with retarding field energy analyzers. By providing detailed information on the trajectories of the ions and the effects of gas collisions, the simulation can help to optimize the performance of plasma-based devices and technologies.

## Features

- Models the transport of Ar+ ions across a plasma sheath and into a retarding field energy analyzer
- Includes collisions with background gas (neutral argon) based on input pressure
- Allows customization of plasma and analyzer parameters

## Installation

To install the software, you'll need to have a compatible C++ compiler installed on your system, such as g++ (GNU GCC). You'll also need to have a copy of the source code, which can be downloaded from the GitHub repository.

Once you have the source code and a compatible C++ compiler installed, you can compile the simulation by running the following command from the root directory:
`make`

This will compile the source code and generate an executable file called `rfea`. To recompile either do `make` or a `make clean` followed by `make`

## Usage

To use the simulation, use the shell script file `run.sh` (or similarly named) provided in the root directory. that specifies the input parameters for the plasma and the analyzer. This will run the simulation using the parameters specified in the shell file. The output will be written to folder `output`. The folder contains R scripts that can be used to plot the data. The R scripts were run in a Windows 10 computer with R 4.2.1 from RStudio. 

