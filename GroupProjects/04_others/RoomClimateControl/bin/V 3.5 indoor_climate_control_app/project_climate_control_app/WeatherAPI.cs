using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace project_climate_control_app
{
    class WeatherAPI
    {
        private const string APIkey = "14b3ca2f1234053fc59c324b8fcb78a3";
        private string url;
        private XmlDocument xmlDocument;

        private bool weatherConnected = false;

        public WeatherAPI(string city)
        {
            try
            {
                SetURL(APIkey, city);
                this.xmlDocument = GetXml(url);
                if (xmlDocument != null)
                {
                    weatherConnected = true;
                }
            }
            catch (Exception)
            {
                weatherConnected = false;
            }
        }

        private void SetURL(string APIkey, string city)
        {
            this.url = string.Format("https://api.openweathermap.org/data/2.5/weather?q={0}&mode=xml&appid={1}", city, APIkey);
        }

        private XmlDocument GetXml(string url)
        {
            using (var client = new WebClient())
            {
                var xmlContent = client.DownloadString(url);
                var newXmlDocument = new XmlDocument();
                newXmlDocument.LoadXml(xmlContent);
                return newXmlDocument;
            }
        }

        public double GetTemperature()
        {
            double tempValue = 0;
            XmlNode temperature = this.xmlDocument.SelectSingleNode("/current/temperature");
            XmlAttribute value = temperature.Attributes["value"];
            if (value != null)
            {
                string tempInString = value.Value;
                tempValue = double.Parse($"{tempInString:f2}");
                tempValue = tempValue - 273.15;
            }
            return tempValue;
        }

        public double GetMaxTemperature()
        {
            double maxTempValue = 0;
            XmlNode maxTemperature = this.xmlDocument.SelectSingleNode("/current/temperature");
            XmlAttribute value = maxTemperature.Attributes["max"];
            if (value != null)
            {
                string maxTempInString = value.Value;
                maxTempValue = double.Parse($"{maxTempInString:f2}");
                maxTempValue = maxTempValue - 273.15;
            }
            return maxTempValue;
        }

        public double GetMinTemperature()
        {
            double minTempValue = 0;
            XmlNode minTemperature = this.xmlDocument.SelectSingleNode("/current/temperature");
            XmlAttribute value = minTemperature.Attributes["min"];
            if (value != null)
            {
                string minTempInString = value.Value;
                minTempValue = double.Parse($"{minTempInString:f2}");
                minTempValue = minTempValue - 273.15;
            }
            return minTempValue;
        }

        public double GetHumidity()
        {
            double humValue = 0;
            XmlNode humidity = this.xmlDocument.SelectSingleNode("/current/humidity");
            XmlAttribute value = humidity.Attributes["value"];
            if (value != null)
            {
                string humidInString = value.Value;
                humValue = double.Parse($"{humidInString:f2}");
            }
            return humValue;
        }

        public double GetWindSpeed()
        {
            double windSpeedValue = 0;
            XmlNode windSpeed = this.xmlDocument.SelectSingleNode("/current/wind/speed");
            XmlAttribute value = windSpeed.Attributes["value"];
            if (value != null)
            {
                string windSpeedInString = value.Value;
                windSpeedValue = double.Parse($"{windSpeedInString:f2}");
            }
            return windSpeedValue;
        }

        public string GetWindDirection()
        {
            string windDirectionInString;
            XmlNode windDirection = this.xmlDocument.SelectSingleNode("/current/wind/direction");
            XmlAttribute value = windDirection.Attributes["name"];
            if (value != null)
            {
                windDirectionInString = value.Value;
            }
            else
            {
                windDirectionInString = "none";
            }
            return windDirectionInString;
        }

        public string GetWeatherPhase()
        {
            string weatherInString;
            XmlNode weather = this.xmlDocument.SelectSingleNode("/current/weather");
            XmlAttribute value = weather.Attributes["value"];
            if (value != null)
            {
                weatherInString = value.Value;
            }
            else
            {
                weatherInString = "unknown";
            }
            return weatherInString;
        }

        public string GetCloudIcon()
        {
            string cloudInString;
            XmlNode cloud = this.xmlDocument.SelectSingleNode("/current/weather");
            XmlAttribute value = cloud.Attributes["icon"];
            if (value != null)
            {
                cloudInString = value.Value;
            }
            else
            {
                cloudInString = "01d";
            }
            return cloudInString;
        }
        public bool GetWeatherConnectionInfo { get => weatherConnected; }
    }
}
