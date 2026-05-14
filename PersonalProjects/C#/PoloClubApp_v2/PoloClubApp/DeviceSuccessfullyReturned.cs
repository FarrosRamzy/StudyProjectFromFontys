using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class DeviceSuccessfullyReturned : PoloClubAppException
    {
        private int deviceID;
        public DeviceSuccessfullyReturned(int deviceID)
        {
            this.deviceID = deviceID;
        }

        public override string GetDetails()
        {
            return $"Device {this.deviceID} Has Returned!";
        }
    }
}
