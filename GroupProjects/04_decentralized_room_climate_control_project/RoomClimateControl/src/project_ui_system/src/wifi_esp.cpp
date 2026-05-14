#include <room_system.h>

AltSoftSerial ESPserial(8, 9);

void setupEspWifi()
{
    ESPserial.begin(9600);
}

void runWifi(String deviceID, String payloadType, String payloadState, char payload[])
{
    String message = "";
    message += SPLIT_CHAR;
    message += deviceID;
    message += SPLIT_CHAR;
    message += payloadType;
    message += SPLIT_CHAR;
    message += PAYLOAD_START_CHAR;
    message += payloadState;
    message += PAYLOAD_SEPARATOR;
    message += payload;
    message += PAYLOAD_END_CHAR;
    message += END_CHAR;

    String completeMessage = message;

    sendMessage(completeMessage);
}

void sendMessage(String messageLine)
{
    ESPserial.println(messageLine);
}

bool readInputMessage(String *payloadType, String *payloadState, uint32_t *payload)
{
    static bool inputStartReceive = false;
    static String inputLine;

    bool inputReceived = false;

    if (ESPserial.available())
    {
        char inputChar = ESPserial.read();
        if (inputChar == START_CHAR)
        {
            inputLine.remove(0);
            inputStartReceive = true;
        }
        else if (inputChar == END_CHAR)
        {
            inputReceived = splitInputLine(inputLine, payloadType, payloadState, payload);
            inputStartReceive = false;
        }
        else if (inputStartReceive)
        {
            inputLine += inputChar;
        }
    }

    return inputReceived;
}

bool splitInputLine(String receivedInput, String *payloadType, String *payloadState, uint32_t *payload)
{
  String splittedInputLine[INPUT_SEGMENT_LIMIT];

  int separated = 0;
  int nextSeparation = 0;
  nextSeparation = receivedInput.indexOf(SPLIT_CHAR, separated + 1);
  splittedInputLine[0] = receivedInput.substring(separated, nextSeparation);
  separated = nextSeparation;

  for (uint8_t i = 1; i < INPUT_SEGMENT_LIMIT && separated != -1; i++)
  {
    nextSeparation = receivedInput.indexOf(SPLIT_CHAR, separated + 1);
    splittedInputLine[i] = receivedInput.substring(separated + 1, nextSeparation);
    separated = nextSeparation;
  }

  return identifyInputID(splittedInputLine, payloadType, payloadState, payload);
}

bool identifyInputID(String inputLine[], String *payloadType, String *payloadState, uint32_t *payload)
{
  String inputID = inputLine[0];
  if (inputID == MAIN_SYSTEM_SERVER_ID)
  {
    return identifyDevice(inputLine, payloadType, payloadState, payload);
  }

  return false;
}

bool identifyDevice(String inputLine[], String *payloadType, String *payloadState, uint32_t *payload)
{
  String deviceID = inputLine[1];
  if (deviceID == APP_DEVICE)
  {
    return identifyPayload(inputLine, payloadType, payloadState, payload);
  }

  return false;
}

bool identifyPayload(String inputLine[], String *payloadType, String *payloadState, uint32_t *payload)
{
  *payloadType = inputLine[2];
  String payloadData = inputLine[3];
  int payloadParamStart = payloadData.indexOf(PAYLOAD_START_CHAR);
  int payloadParamSeparator = payloadData.indexOf(PAYLOAD_SEPARATOR);
  int payloadParamEnd = payloadData.indexOf(PAYLOAD_END_CHAR);

  if ((payloadParamStart > -1) && (payloadParamSeparator > -1) && (payloadParamEnd > -1))
  {
    String readPayloadState = payloadData.substring(payloadParamStart + 1, payloadParamSeparator);
    String readPayloadVal = payloadData.substring(payloadParamSeparator + 1, payloadParamEnd);

    *payloadState = readPayloadState;

    return identifyPayloadType(payloadType, payloadState, readPayloadVal, payload);
  }

  return false;
}

bool identifyPayloadType(String *inputType, String *inputState, String inputValue, uint32_t *value)
{
  if (*inputType == TEMPERATURE_TYPE)
  {
    return identifyTemperaturePayload(inputState, inputValue, value);
  }
  else if (*inputType == FAN_TYPE)
  {
    return identifyFanPayload(inputState, inputValue, value);
  }

  return false;
}

bool identifyTemperaturePayload(String *inputState, String inputValue, uint32_t *value)
{
  if (*inputState == WRITE_DATA)
  {
    uint32_t retrievedValue = inputValue.toInt();
    *value = retrievedValue;
    return true;
  }

  return false;
}

bool identifyFanPayload(String *inputState, String inputValue, uint32_t *value)
{
  if (*inputState == WRITE_DATA)
  {
    uint32_t retrievedValue = inputValue.toInt();
    *value = retrievedValue;
    return true;
  }

  return false;
}