# Advanced Asset Tracker

GPS Asset tracker for Particle Electron using accelerometer wake-on-move.

Project configured for [Particle Workbench](https://docs.particle.io/tutorials/developer-tools/workbench/) on Visual Studio Code.

Based on Ben Agricola's [Tracker](https://github.com/benagricola/tracker), which itself was based on David Middlecamp's [fancy-asset-tracker](https://github.com/dmiddlecamp/fancy-asset-tracker) demo for the Particle Electron with the Asset Tracker Shield.

## Features

The basic implementation provides a combined GPS and Mobile network location system that will:

- Wake up when accelerometer detects motion
- If more motion is detected
  - Reset 'no motion' shutdown timer
  - Initialize GPS module
  - Attempt to connect to Particle cloud

- If no status has been sent in more than 6 hours
  - Send `idle_checkin` status
- Read new NMEA sentences from the GPS module
- If we connected to the cloud but do NOT have a GPS fix
  - Retrieve an approximate location using the UBlox CellLocate feature (ULOC)
  - Use the GSM based location to hint the GPS module in hopes of a quicker fix timer using the PMTK740 and PMTK741 commands

- Publish the most accurate location we have to the Particle cloud.
  - If we have a GPS fix then use that, otherwise submit the approximate GSM location

- If GPS module has not gained a fix in 10 minutes (accelerometer will keep the tracker running permanently if it is in motion)
  - Turn off the GPS module for 10 minutes to save battery (yay active antenna)
  
- TODO: If battery SoC is less than 20%
  - Disable accelerometer based interrupts that keep the device awake
  - Rely on idle checkin every 6 hours (or longer? configurable maybe) to report location

- If we've not detected motion in more than 3 minutes
  - Put the Electron into deep sleep mode for 6 hours (or until woken by motion)

## Particle Project Info

Every new Particle project is composed of 3 important elements that you'll see have been created in your project directory for scoot-track.

#### ```/src``` folder:  
This is the source folder that contains the firmware files for your project. It should *not* be renamed. 
Anything that is in this folder when you compile your project will be sent to our compile service and compiled into a firmware binary for the Particle device that you have targeted.

If your application contains multiple files, they should all be included in the `src` folder. If your firmware depends on Particle libraries, those dependencies are specified in the `project.properties` file referenced below.

#### ```.ino``` file:
This file is the firmware that will run as the primary application on your Particle device. It contains a `setup()` and `loop()` function, and can be written in Wiring or C/C++. For more information about using the Particle firmware API to create firmware for your Particle device, refer to the [Firmware Reference](https://docs.particle.io/reference/firmware/) section of the Particle documentation.

#### ```project.properties``` file:  
This is the file that specifies the name and version number of the libraries that your project depends on. Dependencies are added automatically to your `project.properties` file when you add a library to a project using the `particle library add` command in the CLI or add a library in the Desktop IDE.

## Adding additional files to your project

#### Projects with multiple sources
If you would like add additional files to your application, they should be added to the `/src` folder. All files in the `/src` folder will be sent to the Particle Cloud to produce a compiled binary.

#### Projects with external libraries
If your project includes a library that has not been registered in the Particle libraries system, you should create a new folder named `/lib/<libraryname>/src` under `/<project dir>` and add the `.h`, `.cpp` & `library.properties` files for your library there. Read the [Firmware Libraries guide](https://docs.particle.io/guide/tools-and-features/libraries/) for more details on how to develop libraries. Note that all contents of the `/lib` folder and subfolders will also be sent to the Cloud for compilation.

## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
