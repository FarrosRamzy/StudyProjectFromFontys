//using MongoDB.Driver;
using MongoDB.Bson;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project_climate_control_app.SubForms
{
    public class RoomClimateData : CommunicationProtocol
    {
        private string data;
        private string id;
        private string deviceId;
        private string payloadType;
        private string payloadLine;
        private string payloadState;
        private string payloadValue;

        private string temperatureValue;
        private string humidityValue;
        private string co2Value;
        private string tvocValue;
        private string manualFanSpeedInput;
        /*private string manualControl;*/

        public List<Room> listOfRooms = new List<Room>();

        public Room addDefaultRoom()
        {
            Room room = new Room("default");
            room.UpDateCo2(840);
            room.UpDateCo(0.18f);
            room.UpDateHumidity(37);
            room.UpDateTemperature(19);
            room.UpDateVoc(300);
            listOfRooms.Add(room);
            Room room1 = new Room("default1");
            room1.UpDateCo2(500);
            room.UpDateCo(0.1f);
            room1.UpDateHumidity(55);
            room1.UpDateVoc(650);
            room1.UpDateTemperature(20);
            listOfRooms.Add(room1);
            return room;
        }

        public void readInputMessage(string input)
        {
            this.data = input;
            string inputData = string.Empty;
            bool readData = false;

            foreach (char tempChar in data)
            {
                if (tempChar == startCharacter)
                {
                    readData = true;
                    inputData = string.Empty;
                }
                else if (tempChar == stopCharacter && readData == true)
                {
                    readData = false;
                    splitInputMessage(inputData);
                }
                else if (readData == true)
                {
                    inputData += tempChar;
                }
            }
        }

        private void splitInputMessage(string readMessage)
        {
            string tempString = readMessage;
            tempString = tempString.Trim(startCharacter, stopCharacter, '\r');
            string[] splittedString = tempString.Split(splitCharacter);
            defineMessage(splittedString);
        }

        private void defineMessage(string[] message)
        {
            this.id = message[0];
            this.deviceId = message[1];
            this.payloadType = message[2];
            this.payloadLine = message[3];
            defineId(id, deviceId, payloadType, payloadLine);
        }

        private void defineId(string roomId, string deviceID, string payloadType, string payload)
        {
            bool roomApplied = false;
            Room roomModule = null;
            foreach (Room room in listOfRooms)
            {
                if (room.roomId == roomId)
                {
                    roomApplied = true;
                    roomModule = room;
                }
            }

            if (!roomApplied)
            {
                Room newRoomModule = new Room(roomId);
                listOfRooms.Add(newRoomModule);
                definePayload(newRoomModule, payloadType, payload);
            }
            else
            {
                definePayload(roomModule, payloadType, payload);
            }
        }

        private void defineDevice(Room roomModule, string deviceID, string payloadType, string payload) 
        {
            if (deviceID == sensorDevice)
            {
                identifyPayload(roomModule, payloadType, payload);
            }
            else if (deviceId == uiDevice)
            {
                identifyPayload(roomModule, payloadType, payload);
            }
        }

        private void identifyPayload(Room roomModule, string payloadType, string payload) 
        {
            string newPayload = payload;
            string payloadData = string.Empty;
            bool readPayload = false;

            foreach (char tempChar in newPayload)
            {
                if (tempChar == payloadStartCharacter)
                {
                    readPayload = true;
                    payloadData = string.Empty;
                }
                else if (tempChar == payloadEndCharacter && readPayload == true)
                {
                    readPayload = false;
                    splitPayloadData(roomModule, payloadType, payloadData);
                }
                else if (readPayload == true)
                {
                    payloadData += tempChar;
                }
            }
        }

        private void splitPayloadData(Room roomModule, string payloadType, string payload) 
        {
            string tempPayloadString = payload;
            tempPayloadString = tempPayloadString.Trim(payloadStartCharacter, payloadEndCharacter, '\r');
            string[] splittedPayload = tempPayloadString.Split(payloadSplitCharacter);

            if (splittedPayload[0] == newReadData)
            {
                definePayload(roomModule, payloadType, splittedPayload[1]);
            }
            else if (splittedPayload[0] == newWriteData)
            {
                definePayload(roomModule, payloadType, splittedPayload[1]);
            }
        }

        private void definePayload(Room roomModule, string payloadType, string payload)
        {
            foreach (Room room in listOfRooms)
            {
                if (roomModule.roomId == room.roomId)
                {
                    switch (payloadType)
                    {
                        case temperature:
                            temperatureValue = $"{payload:f2}";
                            float tempVal = float.Parse(temperatureValue);
                            room.UpDateTemperature(tempVal);
                            break;
                        case humidity:
                            humidityValue = $"{payload:f2}";
                            float humVal = float.Parse(humidityValue);
                            room.UpDateHumidity(humVal);
                            break;
                        case carbonDioxyde:
                            co2Value = payload;
                            int co2Val = int.Parse(co2Value);
                            room.UpDateCo2(co2Val);
                            break;
                        case volatileOrganicCompounds:
                            tvocValue = payload;
                            int vocVal = int.Parse(tvocValue);
                            room.UpDateVoc(vocVal);
                            break;
                        case fanSpeed:
                            manualFanSpeedInput = payload;
                            int speed = int.Parse(manualFanSpeedInput);
                            room.SetManualFanSpeedSpeed(speed);
                            break;
                        /*case control:
                            manualControl = payload;
                            if (manualControl == heating)
                            {
                                int stopFan = 0;
                                room.SetManualFanSpeedSpeed(stopFan);
                            }
                            else if (manualControl == cooling)
                            {
                                int fullSpeed = 100;
                                room.SetManualFanSpeedSpeed(fullSpeed);
                            }
                            break;*/
                        default:
                            break;
                    }
                }
            }
        }
        public BsonDocument setData(Room room)
        {
            return room.GetInfo();
        }
    }
}
