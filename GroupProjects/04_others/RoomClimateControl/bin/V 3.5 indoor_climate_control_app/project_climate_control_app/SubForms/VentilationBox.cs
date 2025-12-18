using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project_climate_control_app.SubForms
{
    class VentilationBox
    {
        public VentilationBox()
        {

        }

        private int CalcutateFanSpeedForTemperature(float prefered, float current)
        {
            double x = (current - prefered);
            double y = Math.Pow(2, x);
            y = y * 10;

            if (y > 100)
            {
                return 100;
            }
            return (int)(y);

        }
        private int CalculateFanSpeedForHumidity(float prefered, float current)
        {
            double x = (current - prefered) / 10.00;
            double y = Math.Pow(2, x);
            y = y * 10;

            if (y > 100)
            {
                return 100;
            }
            return (int)(y);

        }
        public int CalculateFanSpeedForCo2(int prefered, int current)
        {
            double x = (current - prefered) / 100.00;
            double y = Math.Pow(2, x);
            y = y * 10;

            if (y > 100)
            {
                return 100;
            }
            return (int)(y);

        }
        public int CalculateFanSpeedForVOC(int prefered, int current)
        {
            double x = (current - prefered) / 100.00;
            double y = Math.Pow(2, x);
            y = y * 10;

            if (y > 100)
            {

                return 100;
            }
            return (int)(y);

        }

        public int CalculateFanSpeed(Room room)
        {
            int vocfanSpeed = 0;
            int co2fanSpeed = 0;
            int humidityfanSpeed = 0;
            int temperaturefanSpeed = 0;
            if (room.GetVoc() > room.preferedvocValue)
            {
                vocfanSpeed = CalculateFanSpeedForVOC(room.preferedvocValue, room.GetVoc());
            }
            if (room.GetCo2() > room.preferedCo2Value)
            {
                co2fanSpeed = CalculateFanSpeedForCo2(room.preferedCo2Value, room.GetCo2());
            }
            if (room.GetHumidity() > room.preferedHumidity)
            {
                humidityfanSpeed = CalculateFanSpeedForHumidity(room.preferedHumidity, room.GetHumidity());
            }
            if (room.GetTemperature() > room.preferedTemperature)
            {
                temperaturefanSpeed = CalcutateFanSpeedForTemperature(room.preferedTemperature, room.GetTemperature());
            }

            return GetMaximum(vocfanSpeed, co2fanSpeed, humidityfanSpeed, temperaturefanSpeed);
        }

        /// <summary>
        /// gets highest value of 4 differnt values;
        /// </summary>
        /// <param name="i">first value</param>
        /// <param name="j">second value</param>
        /// <param name="k">third value</param>
        /// <param name="l">fourth value</param>
        /// <returns>highest value</returns>
        private int GetMaximum(int i, int j, int k, int l)
        {
            List<int> values = new List<int> { i, j, k, l };
            return values.Max();
        }
        public int SetManualFanSpeed(Room room, int fanspeed)
        {
            int calculatedFanSpeed = CalculateFanSpeed(room);
            if (fanspeed > calculatedFanSpeed)
            {
                return fanspeed;
            }
            return calculatedFanSpeed;
        }

    }
}
