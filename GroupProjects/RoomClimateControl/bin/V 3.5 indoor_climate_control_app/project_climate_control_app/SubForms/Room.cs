//using MongoDB.Driver;
//using MongoDB.Bson;
using System;
using MongoDB.Bson;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project_climate_control_app.SubForms
{

    public class Room
    {
        private float temperature;
        private float humidity;
        private int vocValue;
        private int co2Value;
        private float coValue;

        public int manualOverrideFanSpeed { get; private set; }
        public float preferedTemperature { get; private set; }
        public float preferedHumidity { get; private set; }
        public int preferedvocValue { get; private set; }
        public int preferedCo2Value { get; private set; }
        public float preferedCoValue { get; private set; }
        public string roomName { get; private set; }
        public string roomId { get; }

        public Room(string roomId)
        {
            this.roomId = roomId;
            this.humidity = 0;
            this.vocValue = 0;
            this.co2Value = 0;
            this.temperature = 0;
            this.preferedCo2Value = 600;
            this.preferedCoValue = 0.2f;
            this.preferedHumidity = 40;
            this.preferedTemperature = 19;
            this.preferedvocValue = 350;

            roomName = roomId;
            manualOverrideFanSpeed = 0;
        }

        public void UpDateTemperature(float newTemp)
        {
            temperature = newTemp;
        }
        public void UpDateHumidity(float newHumidity)
        {
            humidity = newHumidity;
        }
        public void UpDateCo2(int newCo2)
        {
            co2Value = newCo2;
        }
        public void UpDateCo(float newCo)
        {
            coValue = newCo;
        }

        public void UpDateVoc(int newVoc)
        {
            vocValue = newVoc;
        }

        public float GetTemperature()
        {
            return temperature;
        }

        public float GetHumidity()
        {
            return humidity;
        }

        public int GetCo2()
        {
            return co2Value;
        }
        public float GetCo()
        {
            return coValue;
        }

        public int GetVoc()
        {
            return vocValue;
        }
        public void UpdatePreferedTemperature(float newTemp)
        {
            if (newTemp < 31 && newTemp > 15)
            {
                preferedTemperature = newTemp;
            }
        }
        public void UpdatePreferedHumidity(float newHumidity)
        {
            preferedHumidity = newHumidity;
        }
        public void UpdatePreferedCo2(int newCo2)
        {
            if (newCo2 < 1000)
            {
                preferedCo2Value = newCo2;
            }
        }
        public void UpdatePreferedVoc(int newVoc)
        {
            if (newVoc < 800)
            {
                preferedvocValue = newVoc;
            }
        }
        public void SetManualFanSpeedSpeed(int speed)
        {
            if (speed <= 100)
            {
                manualOverrideFanSpeed = speed;
            }
            else
            {
                manualOverrideFanSpeed = 100;
            }
        }
        public void SetName(string name)
        {
            roomName = name;
        }

        /// <summary>
        /// Creating the input value as Bson data format and save it to the room data.
        /// </summary>
        /// <returns>document value that contains data that could be stored to the database.</returns>
        public BsonDocument GetInfo()
        {
            var doc = new BsonDocument
        {
            {"Date", DateTime.Now.ToString("dd/MM/yyyy")},
            {"Time", DateTime.Now.ToString("HH:mm:ss")},
            {"Room", roomName},
            {"Temperature", temperature},
            {"Humidity", humidity},
            {"CO2", co2Value},
            {"CO", coValue},
            {"TVOC", vocValue}
        };
            return doc;
        }


    }
}


