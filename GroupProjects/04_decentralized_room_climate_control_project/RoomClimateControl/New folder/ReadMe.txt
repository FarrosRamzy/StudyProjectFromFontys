This project is about building a system that can read a room air climate condition such as humidity, temperature, and carbon dioxide level and keep it in a healthy condition using a multithread and automatic system structure, and also with a manual UI for the users to let them directly interact with the system workflow. In this version, some cloud servers are used to save the SQL data of the sensor and also to read a javascript data from the online weather forecast.

The device that are used:
- Arduino Uno
- ESP 8266
- BME280 sensor (Humidity & Temperature)
- CCS811 sensor (CO2 & Volatile Organic Compound)
- A Computer Fan
- Nextion Touchscreen UI

The program that are used for The UI:
- C# Application
- Nextion UI designer

The Cloud server that are used for the product:
- Climate SQL data saving: MongoDB
- Weather forecast data reader: OpenWeather