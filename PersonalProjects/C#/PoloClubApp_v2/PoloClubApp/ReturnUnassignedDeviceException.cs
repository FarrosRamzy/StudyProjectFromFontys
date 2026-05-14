using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class ReturnUnassignedDeviceException : PoloClubAppException
    {
        private int deviceID;
        public ReturnUnassignedDeviceException(int deviceID)
        {
            this.deviceID = deviceID;
        }

        public override string GetDetails()
        {
            return $"This Device {this.deviceID} is Actually Not Assigned to Anyone Yet!";
        }
    }
}
