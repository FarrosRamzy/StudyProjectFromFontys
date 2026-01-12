This project is about creating a wheeled mobile robot that can detect an obstacle, slowly brake the wheel to stop, and evade the obstacle automatically using a sensor. The entire project is using the C++ program and the calculation to slow down the wheel of the robot is prototyped in the MATLAB program. Other than that, a Node-red design and MQTT protocol is also being used to printout the distance of the robot to its detected obstacle, and also to input the minimum distance of the robot to detect the obstacle to evade it.

The device that are mainly used in this project:
1. ESP32
2. STM32 F303RE Nucleo
3. 360 Servo Motors
4. Ultrasonic Sensor

Remarks:
1. The Json file in node-red is needed to open the web dashboard simulator.