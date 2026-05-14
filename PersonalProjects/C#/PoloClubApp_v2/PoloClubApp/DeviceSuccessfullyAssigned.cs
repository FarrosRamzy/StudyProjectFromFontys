using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class DeviceSuccessfullyAssigned : PoloClubAppException
    {
        private int deviceID;
        private string userName;

        public DeviceSuccessfullyAssigned(int deviceID, string userName)
        {
            this.deviceID = deviceID;
            this.userName = userName;
        }

        public override string GetDetails()
        {
            return $"Device {this.deviceID} is Successfully Assigned to {this.userName}.";
        }
    }
}
