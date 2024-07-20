# ChemNose:An Automated Gas Detection and Statistical Analysis Platform

## Table of Contents
- [Overview](#overview)

## Overview
ChemNose is an arduino based gas detection and chemical reaction observation platform. It is designed to be a low cost, portable, and easy to use platform for detecting gases and observing chemical reactions. The platform is built around an Arduino Uno and uses a variety of sensors to detect gases and observe chemical reactions. The platform is designed to be modular and expandable, allowing users to add additional sensors and modules as needed.
It was primarily designed for and used in simulated Mars and Moon exploration science missions for the Anatolian Rover Challenge 2024 by Uludağ University Rover Team (ULUROVER).
Their science team, under my leadership had a hypothesis investigating the habitability of Mars and Moon for Methanogenic bacteria. With this in mind, I designed the platform and data analysis pipeline to fit this task.



## Future Directions For the Project
- Add a VEML6070 UV Sensor to the Weather Station to measure UV Index.
- Add a BME280 Sensor to the Weather Station for more accurate temperature and humidity readings as well as barometric pressure readings.
- Automate the data analysis process with a bash script.
- Add a pipeline explanatory diagram to the README.md file.
- Add a section to the README.md file that explains how to use the platform.
- Add a CSV reading function to the arduino sketch to transfer data to the computer.
- Add SENose: An under U$50 electronic nose for the monitoring of soil gas emissions as the inspiration 
- also add the fact that it is deisgned for efficient significance testing with small datasets
- add the whole change load resistance in the main file or whatever
-  Maybe go over the limitations of the project
- why willow signed rank test
- Maybe change the weather station to also sample every 2 seconds if it doesn't already
- give MERT his design creds
- add the fact that the boxes need to have the soil in them 3 mins before taking readings
- add the fact that the soil moisture sensor needs to have the soil poured over it in a petri dish. Maybe make a diagram
- TimeTempSD Concections
DHT11 connections - D2

RTC connections:
RST- D8
DAT - D6
CLK- D7
RTC uses 3.3V
SD connections:
CS- D4
SCK- D13
MOSI- D11
MISO- D12

- collect and cut empty plastic bottle bottoms to make petri dishes for the cas chambers
- add the fact that the gas sensors need to be warmed up for 24 hours before use