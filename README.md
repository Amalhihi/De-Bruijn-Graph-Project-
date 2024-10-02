###
# Disjoint Cycles in De Bruijn Graphs

This project investigates disjoint cycles in De Bruijn graphs, contributing to optimized database design and algorithmic improvements. The main focus is on building cycles from given polynomials and generating blocks from series in De Bruijn graphs of varying degrees.

# Table of Contents
## -Introduction
## -Database
## -Project Structure
## -Getting Started

# Introduction
De Bruijn graphs are a type of directed graph that represent overlaps between sequences of symbols. They are widely used in bioinformatics for sequence assembly, in coding theory, and in the design of communication networks. In this project, we explore the construction of disjoint cycles within De Bruijn graphs using polynomials of specific degrees.

Understanding the structure of these cycles can lead to optimized database designs and improvements in algorithms that rely on De Bruijn graphs.

## Database
We have a database containing polynomials of the following degrees:

### - Degree 6
### - Degree 8
### - Degree 10
### - Degree 12
These polynomials are used to build cycles within De Bruijn graphs of corresponding orders. Each polynomial represents a specific feedback function that generates sequences with desirable properties.

# Project Structure
 .BuildCycles.cpp & BuildCycles.h: C++ source and header files that contain functions to build cycles from the given polynomials in a De Bruijn graph.

 .BuildBlocksFromSeries: A file (likely a script or executable) that generates blocks from a series within the De Bruijn graph. This helps in analyzing and constructing the building blocks of the graph.

 .database/: A directory containing the polynomial databases for degrees 6, 8, 10, and 12.

 .docs/: Documentation and additional resources.

# Getting Started
## Prerequisites
 A C++ compiler that supports C++11 or higher (e.g., GCC, Clang)
 
 CMake (optional, for building the project)
 
 Git (for cloning the repository)
