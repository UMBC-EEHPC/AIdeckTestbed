# Peripherals

This document specifically covers peripherals that come with the AI-deck rather than with the GAP8 itself and which have support implemented within this project.

## Camera

![](InlineImages/himax_camera.png)

The AI-deck 1.1 targetted by this project comes with a Himax HM01B0-MNA grayscale camera mounted on the front of the device. It natively captures images at 324x324, although its effective resolution is only 320x320. The camera provides native acceleration for QVGA and QQVGA window scaling, vertical flip, and horizontal mirroring, offloading these tasks from the GAP8. It offers various programmable settings such as black level calibration, frame rates, exposure, and analog/digital gain. In addition, there's a motion sensor circuit which enables sending interrupts to the Fabric Controller once a certain threshold has been crossed. 

The GAP SDK contains bindings for the most generic and common features such as turning on the camera, setting the resolution to QVGA/QQVGA, and taking pictures. Anything more though will likely require reading the vendor manual and manipulating hardware registers by hand since the Himax driver within the GAP SDK is rather barebones.

## WiFi

![](InlineImages/nina_module.png)

The AI-deck can both either open up a WiFi access point or connect to an external WiFi access point over the NINA-W102 module. This project currently uses the NINA as a WiFi access point, as that is what the NINA module has flashed by default, switching between whether to connect to an external WiFi access point or to open up a WiFi access point requires reflashing the NINA.

As with the camera, the GAP SDK contains bindings for setting up the WiFi connection, as well as some additional libraries for encoding images and sending them over the WiFi stream to another device. 