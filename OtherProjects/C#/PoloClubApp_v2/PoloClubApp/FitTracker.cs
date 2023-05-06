using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    public class FitTracker : Device, IWearable
    {
        private int waterResistanceMeter;
        private string color;

        /// <summary>
        /// Initialize the FitTracker class as the inherited class from Device.
        /// </summary>
        /// <param name="fitTrackerId">The unique ID of the FitTracker.</param>
        /// <param name="fitTrackerName">The name of the FitTracker device.</param>
        /// <param name="waterResistanceMeter">The water resistance of the FitTracker device.</param>
        /// <param name="color">The color of the FitTracker device.</param>
        public FitTracker(int fitTrackerId, 
                          string fitTrackerName, 
                          int waterResistanceMeter, 
                          string color)
        : base(fitTrackerId, fitTrackerName)
        {
            this.waterResistanceMeter = waterResistanceMeter;
            this.color = color;
        }

        /// <summary>
        /// Overriding the details of the Device class.
        /// </summary>
        /// <returns>A string of the detailed information of the device.</returns>
        public override string GetDetails()
        {
            return $"{base.GetDetails()}, res: {this.waterResistanceMeter} m, color: {this.color}";
        }

        /// <summary>
        /// Get the water resistance of the FitTracker.
        /// </summary>
        /// <returns>Water resistance value.</returns>
        int IWearable.GetWaterResistanceMeters()
        {
            return this.waterResistanceMeter;
        }
    }
}
