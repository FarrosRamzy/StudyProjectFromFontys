using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class EmptyNameInputException : PoloClubAppException
    {
        public EmptyNameInputException() : base($"Please Add The Player Name First!") 
        {
            ;
        }

        public override string GetDetails()
        {
            return base.GetDetails();
        }
    }
}
