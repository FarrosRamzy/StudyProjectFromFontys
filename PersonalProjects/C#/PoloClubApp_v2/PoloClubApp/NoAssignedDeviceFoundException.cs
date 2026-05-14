using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class NoAssignedDeviceFoundException : PoloClubAppException
    {
        private string userName;
        public NoAssignedDeviceFoundException(string userName)
        {
            this.userName = userName;
        }

        public override string GetDetails()
        {
            return $"There is no device assigned to {this.userName}!";
        }
    }
}
