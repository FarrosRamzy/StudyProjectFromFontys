This project is about building a decentralized gate system for a buliding
by using the Embedded System, Node-Red Network, and a C++ Program language.
The main goal of this project is to make a system that can be multiplied in a cheap way, but must still be able to handle both communication
and action process without depending on one master device.

There are three main system in this project, which are:
- The Gate System
- The Display System
- The Queue Detector

The main devices that are used in this project are:
- ESP32
- 360 Servo
- LCD
- some number of buttons

And the main actions that the product can do are:
- open a gate when the entry button is pressed for a certain seconds, depending on the length of a queue before getting closed by automatically and indicate an entity just passed it.
- open all gate if the emergency button is pressed and close it again after the reset button is pressed.
- keep track the number of entities that have passed the gate.
- display the emergency state.
- display the number of entities that already passed the gate. (for example, the number of people that currently inside the building)