# Simulation of Ar+ Ions Transported Across a Plasma Sheath and Through a Retarding Field Energy Analyzer

This software is a computer simulation that models the transport of Ar+ ions across a plasma sheath and into a retarding field energy analyzer. The motion of the ions is tracked, and collisions with the background gas (neutral argon) are allowed based on the input pressure.

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

To use the simulation, use the shell script file `run.sh` provided in the root directory. that specifies the input parameters for the plasma and the analyzer. This will run the simulation using the parameters specified in the shell file. The output will be written to folder `output`. The folder contains an R script that can be used to plot the data. 

