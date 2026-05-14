using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project_climate_control_app
{
    public class CommunicationProtocol
    {
        //char protocol
        protected const char startCharacter = '#';
        protected const char splitCharacter = '&';
        protected const char payloadStartCharacter = '{';
        protected const char payloadSplitCharacter = '|';
        protected const char payloadEndCharacter = '}';
        protected const char stopCharacter = ';';

        //type of sensors.
        protected const string temperature = "TMP";
        protected const string humidity = "HUM";
        protected const string volatileOrganicCompounds = "VOC";
        protected const string carbonDioxyde = "CO2";
        protected const string carbonMonoxyde = "CO";

        //main app id
        protected const string mainAppID = "VB";

        //device id
        protected const string sensorDevice = "SENSOR";
        protected const string uiDevice = "UI";
        protected const string appDevice = "APP";

        //type of input/output
        protected const string newReadData = "READ";
        protected const string newWriteData = "WRITE";

        //type of ventilator data.
        protected const string fanSpeed = "FAN";
        protected const string error = "ERR";
        
        /*//type of manual setup.
        protected const string heating = "HEAT";
        protected const string cooling = "COOL";
        protected const string auto = "AUTO";*/

        //type of errors.
        protected const string valueIsNull = "404";             //when payload is null.
        protected const string typeIsInvalid = "400";           //when the type is unequal to any of the type of all sensors and the type of all ventilator data.
        protected const string dataIsInConflict = "409";        //when the data message is unreadable.
        protected const string expectationIsFailed = "417";     //when the ACK response not received before the timeOut.
        protected const string clientIsClosed = "499";          //when one of the rooms is suddenly unavailable during the run.
    }
}
