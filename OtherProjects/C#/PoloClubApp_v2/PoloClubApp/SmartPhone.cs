using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    public class SmartPhone : Device
    {

        /// <summary>
        /// Initialize the SmartPhone class as the inherited class from Device.
        /// </summary>
        /// <param name="phoneId">The unique ID of the Phone.</param>
        /// <param name="phoneName">The name of the Phone device.</param>
        public SmartPhone(int phoneId, 
                          string phoneName) 
        : base(phoneId, phoneName)
        {
            ;//Empty because it is similar with the basic device or the parent class.
        }

        /// <summary>
        /// Overriding the details of the Device class.
        /// </summary>
        /// <returns>A string of the detailed information of the device.</returns>
        public override string GetDetails()
        {
            return $"{base.GetDetails()}";
        }
    }
}
