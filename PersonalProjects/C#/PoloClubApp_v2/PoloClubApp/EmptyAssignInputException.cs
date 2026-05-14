using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class EmptyAssignInputException : PoloClubAppException
    {
        private int selectedDevice;
        private string userName;
        private string message;
        public EmptyAssignInputException(int selectedDevice, string userName)
        {
            this.selectedDevice = selectedDevice;
            this.userName = userName;
        }

        public override string GetDetails()
        {
            if (this.selectedDevice == -1 && this.userName == "")
            {
                this.message = $"Error! Please Fill Out The Name And Choose The Device First!";
            }
            else if (this.selectedDevice != -1 && this.userName == "")
            {
                this.message = $"Error! Please Fill Out The Name First!";
            }
            else if (this.selectedDevice == -1 && this.userName != "")
            {
                this.message = $"Error! Please Choose The Device First!";
            }
            return this.message;
        }
    }
}
