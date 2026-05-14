using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class UnacceptedResistanceMeterException : PoloClubAppException
    {
        private int deviceID;

        public UnacceptedResistanceMeterException(int deviceID)
        {
            this.deviceID = deviceID;
        }

        public override string GetDetails()
        {
            return $"Sorry! You are Not Allowed to Borrow Device {this.deviceID} Because its Water Resistance Meter is Below 3 Meters!";
        }
    }
}
