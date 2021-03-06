# Vending Machine Kata

## Introduction
A vending machine implementation that can accept coins, dispense products, and make change. Based on the requirements available here:
https://github.com/PillarTechnology/kata-vending-machine

This project was created using Test-Driven-Development. The project is written in C++ and will
build for XCode on OSX.

Future improvements may include CMake build management for multiple platform support.

## Requirements
XCode and XCode Command Line tools to run from directly from the terminal.

The test framework (Catch) is included as a standalone header file in the project


## Commands
to build project:
    xcodebuild clean install

to run unit tests:
    cd Build/Release/
    ./VendingMachineUnitTests

**the executable may be in a different location depending on your XCode settings. To check this in XCode go to Project Settings ->

Only unit test product is enabled to be built and run, the application itself is not configured. Future improvements may include addition of a command line interface to demo the vending machine functionality.


