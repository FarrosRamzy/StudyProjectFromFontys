using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class EmptyDeviceReturnInputException : PoloClubAppException
    {
        public EmptyDeviceReturnInputException() : base($"Please select the device ID first!") 
        {
            ;
        }

        public override string GetDetails()
        {
            return base.GetDetails();
        }
    }
}
