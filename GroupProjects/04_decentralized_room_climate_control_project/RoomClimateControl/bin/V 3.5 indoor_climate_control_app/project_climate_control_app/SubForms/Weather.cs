using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Windows.Forms;

namespace project_climate_control_app.SubForms
{
    public partial class Weather : Form
    {
        private WeatherData weatherData;
        private string cityForWeather;
        private string weatherCloud;

        private bool cityChanged;

        public Weather(string currentCity)
        {
            InitializeComponent();
            cityForWeather = currentCity;
        }

        private void Weather_Load(object sender, EventArgs e)
        {
            changeTheme();
            cityChanged = false;
            weather_timer.Start();
        }

        private void Weather_VisibleChanged(object sender, EventArgs e)
        {
            changeTheme();
        }

        private void changeTheme()
        {
            foreach (Control buttons in this.Controls)
            {
                if (buttons.GetType() == typeof(Button))
                {
                    Button button = (Button)buttons;
                    button.BackColor = FormThemeColor.Primary;
                    button.ForeColor = Color.White;
                    button.FlatAppearance.BorderColor = FormThemeColor.Secondary;
                }
            }
            tbCityName.BackColor = Color.White;
            pbCloud.BackColor = Color.White;
        }

        private void weather_timer_Tick(object sender, EventArgs e)
        {
            if (WeatherCity.GetNewCity == "" || WeatherCity.GetNewCity == null)
            {
                cityForWeather = WeatherCity.GetDefaultCity;
            }
            else
            {
                cityForWeather = WeatherCity.GetNewCity;
            }

            weatherData = new WeatherData(cityForWeather);
            weatherData.GetWeather();

            WeatherCity.SetServerInfo = weatherData.GetWeatherConnectionInfo;

            if (weatherData.GetWeatherConnectionInfo == true)
            {
                try
                {
                    weatherCloud = weatherData.CloudPhase;
                    pbCloud.Load(string.Format("http://openweathermap.org/img/w/{0}.png", weatherCloud));
                    lblCloud.Text = $"{weatherData.WeatherPhase}";
                    lblHumid.Text = $"{weatherData.Humidity:f2}";
                    lblCurrentTemp.Text = $"{weatherData.CurrentTemperature:f0}";
                    lblHighestTemp.Text = $"{weatherData.MaxTemperature:f2}";
                    lblLowestTemp.Text = $"{weatherData.MinTemperature:f2}";

                    if (weatherData.WindDirection == "none")
                    {
                        lblWindStatus.Text = $"Today, the wind blows with {weatherData.WindSpeed} m/s speed.";
                    }
                    else
                    {
                        lblWindStatus.Text = $"Today, the wind blows with {weatherData.WindSpeed} m/s speed to the {weatherData.WindDirection}.";
                    }
                    if (cityChanged == false)
                    {
                        tbCityName.Text = cityForWeather;
                    }
                }
                catch
                {
                    WeatherCity.SetCity = WeatherCity.GetDefaultCity;
                    tbCityName.Text = WeatherCity.GetDefaultCity;
                    MessageBox.Show($"{cityForWeather} City weather data is not available!");
                }
            }
        }

        private void btnChangeCity_Click(object sender, EventArgs e)
        {
            if (cityChanged == false)
            {
                tbCityName.Text = "";
                tbCityName.ReadOnly = false;
                cityChanged = true;
                btnChangeCity.Text = "Add";
            }
            else
            {
                if (tbCityName.Text == "")
                {
                    MessageBox.Show("Please Type The City First!");
                }
                else
                {
                    WeatherCity.SetCity = tbCityName.Text;
                    tbCityName.ReadOnly = true;
                    cityChanged = false;
                    btnChangeCity.Text = "Change";
                }
            }
        }
    }
}
