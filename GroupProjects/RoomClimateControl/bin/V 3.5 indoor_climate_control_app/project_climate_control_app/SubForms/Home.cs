using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;

namespace project_climate_control_app.SubForms
{
    public partial class Home : Form
    {
        private WeatherData weatherData;
        private string cityForWeather;
        private string weatherCloud;

        private bool warningShowed = false;

        public Home(string currentCity)
        {
            InitializeComponent();
            cityForWeather = currentCity;
        }

        private void Home_Load(object sender, EventArgs e)
        {
            changeTheme();
            load_timer.Start();
        }

        private void Home_VisibleChanged(object sender, EventArgs e)
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
            lblCityName.BackColor = Color.White;
            lblTime.ForeColor = FormThemeColor.Primary;
            lblDate.ForeColor = FormThemeColor.Secondary;
            pbCloud.BackColor = Color.White;
        }

        private void showWarningInfo()
        {
            if (warningShowed == false)
            {
                warningShowed = true;
                MessageBox.Show("Weather data is offline!");
            }
        }

        private void load_timer_Tick(object sender, EventArgs e)
        {
            lblTime.Text = DateTime.Now.ToString("hh:mm tt");
            lblDate.Text = DateTime.Now.ToString("dddd, MMMM dd, yyyy");
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

            if (weatherData.GetWeatherConnectionInfo == false)
            {
                showWarningInfo();
            }
            else
            {
                this.warningShowed = false;
                try
                {
                    weatherCloud = weatherData.CloudPhase;
                    pbCloud.Load(string.Format("http://openweathermap.org/img/w/{0}.png", weatherCloud));
                    lblCloud.Text = $"{weatherData.WeatherPhase}";
                    lblHumid.Text = $"{weatherData.Humidity:f2}";
                    lblTemp.Text = $"{weatherData.CurrentTemperature:f2}";
                    lblCityName.Text = cityForWeather;
                }
                catch (Exception)
                {
                    WeatherCity.SetCity = WeatherCity.GetDefaultCity;
                    MessageBox.Show($"{cityForWeather} City weather data is not available!");
                }
            }
        }
    }
}
