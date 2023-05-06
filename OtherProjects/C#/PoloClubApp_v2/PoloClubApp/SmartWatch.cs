using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    public class SmartWatch : Device, IWearable
    {
        private int waterResistanceMeter;
        private int size;

        /// <summary>
        /// Initialize the SmartWatch class as the inherited class from Device.
        /// </summary>
        /// <param name="smartWatchId">The unique ID of the SmartWatch.</param>
        /// <param name="smartWatchName">The name of the SmartWatch device.</param>
        /// <param name="waterResistanceMeter">The water resistance of the SmartWatch device.</param>
        /// <param name="size">The size of the SmartWatch device.</param>
        public SmartWatch(int smartWatchId, 
                          string smartWatchName, 
                          int waterResistanceMeter, 
                          int size) 
        : base(smartWatchId,smartWatchName)
        {
            this.waterResistanceMeter = waterResistanceMeter;
            this.size = size;
        }

        /// <summary>
        /// Overriding the details of the Device class.
        /// </summary>
        /// <returns>A string of the detailed information of the device.</returns>
        public override string GetDetails()
        {
            return $"{base.GetDetails()}, res: {this.waterResistanceMeter} m, size: {this.size}";
        }

        /// <summary>
        /// Get the water resistance of the SmartWatch.
        /// </summary>
        /// <returns>Water resistance value.</returns>
        int IWearable.GetWaterResistanceMeters()
        {
            return this.waterResistanceMeter;
        }
    }
}
