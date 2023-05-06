using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    class PoloClubAppException : Exception
    {
        private string message;

        public PoloClubAppException()
        {
            ;
        }

        public PoloClubAppException(string message) : base(message)
        {
            this.message = message;
        }

        public virtual string GetDetails()
        {
            return $"{this.message}";
        }
    }
}
