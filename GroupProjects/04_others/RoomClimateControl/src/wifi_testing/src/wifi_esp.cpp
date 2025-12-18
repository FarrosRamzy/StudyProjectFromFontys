#include <wifi_esp.h>

AltSoftSerial ESPserial(8, 9);

bool connectionEstablished;
bool connectionStarted;
bool joinAP;
bool statusOK;

unsigned long respondTime = 5000;
unsigned long startTime = millis();

String deviceID;

void runWifi()
{
    if (connectionEstablished)
    {
        if (millis() - startTime > respondTime)
        {
            if (sendMessage())
            {
                Serial.println("SEND 0K");
                Serial.println("SEND 0K");
            }
            else
            {
                Serial.println("ERROR");
                Serial.println("CLOSED");
                ESPserial.print("AT+CIPCLOSE");
                connectionEstablished = false;
            }
            startTime = millis();
        }
    }
    else
    {
        while (!startConnection())
        {
            Serial.println("New connection is not established.");
        }
    }
}

bool setUpWifi()
{
    connectionEstablished = false;
    ESPserial.begin(9600);
    Serial.print(STOP_ECHO "\r\n");
    ESPserial.print(STOP_ECHO "\r\n");
    if (checkATresponse("\r\nOK"))
    {
        Serial.println("OK");
        if (setConnectionMode())
        {
            if (!checkAccessPoint())
            {
                if (!joinAccessPoint())
                {
                    if (checkConnectionStatus())
                    {
                        return true;
                    }
                    else
                    {
                        if (startConnection())
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (checkConnectionStatus())
                {
                    return true;
                }
                else
                {
                    if (startConnection())
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        Serial.println("ERROR");
        return false;
    }
}

bool setConnectionMode()
{
    Serial.print(SET_WIFI_MODE "\r\n");
    ESPserial.print(SET_WIFI_MODE "\r\n");
    bool modeChanged = checkATresponse("\r\nOK");
    if (modeChanged)
    {
        Serial.println("OK");
    }
    else if (!modeChanged)
    {
        Serial.println("MODE ERROR");
    }
    return modeChanged;
}

bool checkAccessPoint()
{
    Serial.print(CHECK_ACC_POINT "\r\n");
    ESPserial.print(CHECK_ACC_POINT "\r\n");
    bool apStatus = false;
    bool noAP = checkATresponse("No AP");
    if (noAP)
    {
        Serial.println("No AP");
        if (checkATresponse("\r\nOK"))
        {
            Serial.println("OK");
            apStatus = false;
        }
        else
        {
            Serial.println("ESP ERROR");
            apStatus = false;
        }
    }
    else if (!noAP)
    {
        Serial.println("AP Available");
        if (checkATresponse("\r\nOK"))
        {
            Serial.println("OK");
            apStatus = true;
        }
        else
        {
            Serial.println("ESP ERROR");
            apStatus = false;
        }
    }
    return apStatus;
}

bool joinAccessPoint()
{
    Serial.print(JOIN_ACC_POINT "\"" SSID "\",\"" PASSWORD "\"\r\n");
    ESPserial.print(JOIN_ACC_POINT "\"" SSID "\",\"" PASSWORD "\"\r\n");
    if (checkATresponse("WIFI CONNECTED"))
    {
        Serial.println("WIFI CONNECTED");
        if (checkATresponse("WIFI GOT IP"))
        {
            Serial.println("WIFI GOT IP");
            if (checkATresponse("\r\nOK"))
            {
                Serial.println("OK");
                joinAP = true;
            }
            else
            {
                Serial.println("WIFI ERROR");
                joinAP = false;
            }
        }
        else
        {
            Serial.println("IP FAIL");
            joinAP = false;
        }
    }
    else
    {
        Serial.println("WIFI FAIL");
        joinAP = false;
    }

    return joinAP;
}

bool checkConnectionStatus()
{
    Serial.print(CHECK_STATUS "\r\n");
    ESPserial.print(CHECK_STATUS "\r\n");
    bool correctStatus = checkATresponse("STATUS:3");
    if (correctStatus)
    {
        Serial.println("STATUS:3");
        if (checkATresponse("\r\nOK"))
        {
            Serial.println("OK");
            statusOK = true;
        }
        else
        {
            Serial.println("IP ERROR");
            statusOK = false;
        }
    }
    else if (!correctStatus)
    {
        Serial.println("STATUS:2");
        if (checkATresponse("\r\nOK"))
        {
            Serial.println("OK");
        }
        else
        {
            Serial.println("IP ERROR");
        }
        statusOK = false;
    }
    return statusOK;
}

bool startConnection()
{
    Serial.print(START_COMMUNICATION "\"" TCP "\",\"" SERVER_IP "\"," SERVER_PORT "\r\n");
    ESPserial.print(START_COMMUNICATION "\"" TCP "\",\"" SERVER_IP "\"," SERVER_PORT "\r\n");
    if (checkATresponse("CONNECT"))
    {
        Serial.println("CONNECT");
        if (checkATresponse("\r\nOK"))
        {
            Serial.println("OK");
            getDeviceID();
            connectionEstablished = true;
            connectionStarted = true;
        }
        else
        {
            Serial.println("CONNECT ERROR");
            connectionStarted = false;
            connectionEstablished = false;
        }
    }
    else
    {
        Serial.println("CONNECT FAIL");
        connectionStarted = false;
    }
    return connectionStarted;
}

bool sendMessage()
{
    String message;
    message += START_CHAR;
    message += deviceID;
    message += SPLIT_CHAR;
    message += SENSOR;
    message += SPLIT_CHAR;
    message += TYPE_TO_TRY;
    message += SPLIT_CHAR;
    message += PAYLOAD_START_CHAR;
    message += "READ";
    message += PAYLOAD_SEPARATOR;
    message += MESSAGE_TO_TRY;
    message += PAYLOAD_END_CHAR;
    message += END_CHAR;

    String completeMessage = message;

    int nrOfChar = completeMessage.length() + 2;
    String Command = SEND_MESSAGE;
    Command += nrOfChar;

    String sendCommand = Command;

    Serial.print(sendCommand + "\r\n");
    ESPserial.print(sendCommand + "\r\n");
    if (!checkATresponse("OK"))
    {
        return false;
    }
    else if (checkATresponse(">"))
    {
        Serial.print(completeMessage + "\r\n");
        ESPserial.print(completeMessage + "\r\n");
        return true;
    }
    else
    {
        return false;
    }
}

void getDeviceID()
{
    deviceID = "";
    bool getMacAddress = false;
    Serial.print(GET_MAC_ADDRESS "\r\n");
    ESPserial.print(GET_MAC_ADDRESS "\r\n");

    if (checkATresponse("+CIPSTAMAC:"))
    {
        while (!getMacAddress)
        {
            deviceID = ESPserial.readStringUntil('\n');
            deviceID.replace("\"", "");
            deviceID.trim();
            getMacAddress = true;
        }
    }
    Serial.print("ID:   ");
    Serial.println(deviceID);
}

bool checkATresponse(String message)
{
    unsigned long MessageStartTime = millis();
    int strlen = message.length() + 1;
    char espreply[strlen];

    message.toCharArray(espreply, strlen);
    int i = 0;

    while (true)
    {
        if (ESPserial.find(espreply[i]))
        {
            i++;
        }
        if (i == strlen - 1)
        {
            return true;
        }
        if (millis() - MessageStartTime > respondTime)
        {
            Serial.println("check_is_time_out!");
            MessageStartTime = millis();
            return false;
        }
    }
}

// void readInputMessage()
// {
//     static bool inputStartReceive = false;
//     static String inputLine;
//     if (ESPserial.available())
//     {
//         char inputChar = ESPserial.read();
//         if (inputChar == START_CHAR)
//         {
//             inputLine.remove(0);
//             inputStartReceive = true;
//         }
//         else if (inputChar == END_CHAR)
//         {
//             splitInputLine(inputLine);
//             inputStartReceive = false;
//         }
//         else if (inputStartReceive)
//         {
//             inputLine += inputChar;
//         }
//     }
// }

// void splitInputLine(String input)
// {
//     ;
// }