using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class NoUserDataFoundException : PoloClubAppException
    {
        private string userName;
        public NoUserDataFoundException(string userName)
        {
            this.userName = userName;
        }

        public override string GetDetails()
        {
            return $"The data of user {this.userName} is unavailable!";
        }
    }
}
