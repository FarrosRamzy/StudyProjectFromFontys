using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project_climate_control_app
{
    class WeatherData
    {
        private WeatherAPI dataAPI;

        private string cityName;

        private double currentTemperature;
        private double maxTemperature;
        private double minTemperature;

        private double humidity;

        private double windSpeed;
        private string windDirection;

        private string weatherPhase;

        private string cloudPhase;

        private bool dataIsAvailable = false;

        public WeatherData(string city)
        {
            this.cityName = city;
        }

        public void GetWeather()
        {
            dataAPI = new WeatherAPI(cityName);
            dataIsAvailable = dataAPI.GetWeatherConnectionInfo;
            if (dataIsAvailable)
            {
                this.currentTemperature = dataAPI.GetTemperature();
                this.maxTemperature = dataAPI.GetMaxTemperature();
                this.minTemperature = dataAPI.GetMinTemperature();
                this.humidity = dataAPI.GetHumidity();
                this.windSpeed = dataAPI.GetWindSpeed();
                this.windDirection = dataAPI.GetWindDirection();
                this.weatherPhase = dataAPI.GetWeatherPhase();
                this.cloudPhase = dataAPI.GetCloudIcon();
            }
        }

        public bool GetWeatherConnectionInfo { get => dataIsAvailable; }
        public double CurrentTemperature { get => currentTemperature; }
        public double MaxTemperature { get => maxTemperature; }
        public double MinTemperature { get => minTemperature; }
        public double Humidity { get => humidity; }
        public double WindSpeed { get => windSpeed; }
        public string WindDirection { get => windDirection; }
        public string WeatherPhase { get => weatherPhase; }
        public string CloudPhase { get => cloudPhase; }
    }
}
