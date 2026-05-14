using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class DeviceIsAlreadyAssignedException : PoloClubAppException
    {
        private int deviceID;
        public DeviceIsAlreadyAssignedException(int deviceID)
        {
            this.deviceID = deviceID;
        }

        public override string GetDetails()
        {
            return $"Sorry! Device {this.deviceID} is Already Assigned to Someone Else.";
        }
    }
}
