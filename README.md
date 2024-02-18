# An E-Paper Display Based Desk-clock.

## Overview

This project documents and contains the code for an E-paper based Desk Clock made as a final project for the Course ECEN5613 - Embedded Systems Design.  
Features : <br>
* Display and configure current day, date and time.
* Display the current room temperature and humidty.
* 4 user-configurable alarms.


## Motivation
I had wanted to work with e-paper displays for quite some time now and the final project for my graduate course in Embedded Systems Design provided me with the perfect opportunity to do so.
I wanted to learn how to write a basic text/image rendering library and E-paper displays seemed to be the perfect place to start. <br> You can read more about the project and the groundwaork in the [Project Report](/FinalReport.pdf).

## [Link to Video Demonstration](https://drive.google.com/drive/folders/16hQ_8MMb17Ao2Q70kuz9eXQXmRNZ9ggW?usp=sharing)

## Hardware.

I designed a PCB fot his porject which housed the temperature sensor and the real-time clock module.
This board was battery powered, which means it can keep track of time even when disconnected. The battery itself is rechargable and the board houses a charger for the same. 

The initial plan was to have the microcontroller on the same board instead of using a development board but I had to change plans due to time constraints.
![alt text](/Photos/BoardTop.jpg "PCB Top")

The board was desinged in Eagle and assembled by me using a pick-and-place machine and a reflow oven. Much thanks to [ITLL](https://itlp.colorado.edu/) for the equipment and help with assembly.

## Software

### The Software Stack
![alt text](/Photos/SoftwareStack.jpg)

```
.
├── DeviceDrivers
│   ├── display.c
│   ├── hdc2022.c
│   └── mcp7940.c
├── Graphics
│   ├── clockface.c   
│   └── render.c      
├── PeripheralDrivers 
│   ├── clocks.c      
│   ├── gpio.c        
│   ├── i2c.c
│   ├── mux.c
│   ├── spi.c
│   └── timer.c       
├── SystemModel       
│   ├── alarms.c      
│   ├── statemachine.c
│   └── timeanddate.c 
├── assets
│   ├── fonts
│   │   ├── coolvetica30.c
│   │   ├── coolveticacrammed180.c      
│   │   ├── coolveticacrammed200.c      
│   │   ├── fonts.c
│   │   ├── helvetica120.c
│   │   └── helvetica90.c
│   └── icons
│       ├── battery_icons.c
│       └── misc_icons.c
├── main.c
├── syscalls.c
├── sysmem.c
└── systick.c
```
<br>
As evident the software can be divided into 4 major components.

[Peripheral Drivers](/Src/PeripheralDrivers/)<br>
These files contain the code for initialising and utilising the microcontroller peripherals such as I2C and SPI.<br>
[Device Drivers](/Src/DeviceDrivers/)<br>
The Device drivers use the APIs exposed by the Peripheral drivers to communicate with the off-chip peripherals such as the E-Paper display, Real-time clock and the temperature sensor.<br>
[Graphics](/Src/Graphics/)<br>
The graphics library deals with modifying the image buffer to render images, texts and lines.<br>
[System Model](/Src/SystemModel/)<br>
The system model code defines how the clock reacts to button presses from the user. Depending on what view the user is currently in, each button is mapped to a different function.<br>

## The Resulting Clockface

![alt text](/Photos/Clockface.jpg)





