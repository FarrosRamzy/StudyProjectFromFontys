#include <room_system.h>

DHT dht(DHT_PIN, DHT_TYPE);

void setupHumidTempSensor()
{
    dht.begin();
}

void readTempAndHumid(float *humidity, float *temperature)
{
    float humidityRead = dht.readHumidity();
    float temperatureRead = dht.readTemperature();

    if (isnan(humidityRead) || isnan(temperatureRead))
    {
        return;
    }
    else
    {
        *humidity = humidityRead;
        *temperature = temperatureRead;
    }
}