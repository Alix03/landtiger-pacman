# Pac-Man for LandTiger LPC1768

## Abstract

This project implements Pac-Man game on the LandTiger LPC1768 development board, featuring an ARM Cortex-M3 processor. Developed using Keil µVision IDE with software debugging capabilities, the game leverages embedded systems programming principles to deliver classic arcade gameplay on a microcontroller platform.

### Key Features

- **Complete maze navigation system** with 240 standard pills and 6 randomly generated power pills
- **Joystick-controlled movement** with continuous directional input and wall collision detection  
- **Real-time scoring system** with life management (extra life every 1000 points)
- **60-second countdown timer** creating time-pressure gameplay mechanics
- **Teleportation system** between opposite sides of the central maze area
- **Pause/resume functionality** using external interrupt (INT0)
- **Victory and Game Over screens** based on completion status
- **Optimized display rendering** for 240x320 pixel LCD screen with 8-pixel cell matrix

### Technical Implementation

- **Interrupt handling** for user input and game timing
- **Real-time system management** with precise timing controls  
- **Memory-efficient graphics rendering** on resource-constrained hardware
- **Peripheral integration** (LCD display, joystick, external interrupts)
- **Modular code architecture** with separate game logic and hardware abstraction layers


Embedded implementation of the classic Pac-Man arcade game on the LandTiger LPC1768 development board using ARM Cortex-M3 microcontroller. 
Created for the Computer Architectures coursework at Politecnico di Torino's MSc in Computer Engineering.
