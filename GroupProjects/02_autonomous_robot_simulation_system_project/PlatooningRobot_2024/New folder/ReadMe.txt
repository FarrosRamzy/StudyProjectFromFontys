This project is upgrading the swarm robot system to control the robot in a track, adding the obstacle avoidance maneuver into a platoon control. The entire project is using the C++ program and the calculation to slow down the wheel of the robot is prototyped in the MATLAB program. Other than that, a Node-red design and MQTT protocol is also being used to printout the distance of the robot to its detected obstacle, and also to input the minimum distance of the robot to detect the obstacle to evade, or a moving object in front of it to keep a safe distance while following the track.

The device that are mainly used in this project:
1. ESP32
2. STM32 F303RE Nucleo
3. 360 Servo Motors
4. Ultrasonic Sensor
5. Infrared Sensor

Remarks:
1. The Json file in node-red folder is needed to open the node-red dashboard simulator on website.