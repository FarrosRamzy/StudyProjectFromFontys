# I2C Communication Exercises

I created three embedded exercises to learn how I2C works with sensors and between microcontrollers.

## Assignments

### Assignment A — BME280 Sensor

I wrote an Arduino program that communicates with a BME280 sensor, reads its raw environmental values, and converts them into readable measurements. I also created helper code for register and bit handling.

### Assignment B — Master and Slave Comparison

I programmed two Arduino Uno boards. The master sends a number to the slave and requests a result indicating whether the value is below or above 100.

### Assignment C — Minimum and Maximum

I extended the master/slave setup so the master sends two values and the slave returns their minimum and maximum.

These exercises helped me understand I2C addressing, request/response communication, device roles, timing, and sensor-register processing.
