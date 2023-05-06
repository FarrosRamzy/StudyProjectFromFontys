#include <trial_system.h>

// output_text:
// home_page
NexText hTempVal = NexText(0, 4, "tbTmpval");
NexText hHumVal = NexText(0, 5, "tbHmdval");

NexText htempUnit = NexText(0, 11, "tuTmp");
NexText hhumUnit = NexText(0, 12, "tuHmd");

// room_page
NexText rTempVal = NexText(2, 5, "tbTmpval");
NexText rHumVal = NexText(2, 6, "tbHmdval");
NexText rtempUnit = NexText(2, 9, "tuTmp");
NexText rhumUnit = NexText(2, 8, "tuHmd");

// fan_page
NexNumber fFanSpeed = NexNumber(3, 4, "tbFanSpeed");

// input_text:
bool automaticFanSpeed = true;
bool autoTemperature = true;
uint32_t dsTempBtn = 0;
uint32_t dsFanBtn = 0;
uint32_t sldTemp = 0;
uint32_t sldFan = 0;

NexDSButton setTempBtn = NexDSButton(2, 10, "btTempSet");
NexSlider setTemp = NexSlider(2, 4, "hSetTmp");

NexDSButton setFanSpeedBtn = NexDSButton(3, 5, "btFanSet");
NexSlider setFanSpeed = NexSlider(3, 2, "hSetFanSpeed");

/////////////////////////////////////////////////////////////

char Temp[15];
char Humid[15];
// char CO[15];
// char CO2[15];
// char VOC[15];
// char Time[10];
char TmpUnit[5];
char HumUnit[5];
// char VOCUnit[5];
// char CO2Unit[5];
// char COUnit[5];

/////////////////////////////////////////////////////////////

NexTouch *nextion_listen_list[] = {&setTempBtn, &setTemp, &setFanSpeedBtn, &setFanSpeed};

void setupTouchScreen()
{
    nexInit();
    setTempBtn.attachPop(setTempCtrlButtonChange, &setTempBtn);
    setFanSpeedBtn.attachPop(setFanCtrlButtonChange, &setFanSpeedBtn);
    setTemp.attachPop(setTempManualSlider);
    setFanSpeed.attachPop(setFanManualSlider);
}

void readAutoManualState(bool *fanIsInAutoMode, bool *tempIsInAutoMode, uint32_t *manualFanSpeedVal, uint32_t *manualTempVal)
{
    *fanIsInAutoMode = automaticFanSpeed;
    *tempIsInAutoMode = autoTemperature;

    if (!automaticFanSpeed)
    {
        *manualFanSpeedVal = sldFan;
    }

    if (!autoTemperature)
    {
        *manualTempVal = sldTemp;
    }
}

void setFanCtrlButtonChange(void *ptr)
{
    if (setFanSpeedBtn.getValue(&dsFanBtn) != 0)
    {
        automaticFanSpeed = false;
    }
    else
    {
        automaticFanSpeed = true;
    }
}

void setTempCtrlButtonChange(void *ptr)
{
    if (setTempBtn.getValue(&dsTempBtn) != 0)
    {
        autoTemperature = false;
    }
    else
    {
        autoTemperature = true;
    }
}

void setTempManualSlider(void *ptr)
{
    if (!autoTemperature)
    {
        uint32_t temperature = sldTemp;
        if (!setTemp.getValue(&temperature))
        {
            sldTemp = temperature;
        }
        // sldTemp = temperature;
    }
}

void setFanManualSlider(void *ptr)
{
    if (!automaticFanSpeed)
    {
        uint32_t fanSpeed = 0;
        if (setFanSpeed.getValue(&fanSpeed))
        {
            sldFan = fanSpeed;
        }
        // sldFan = fanSpeed;
    }
}

void readTouchInput()
{
    nexLoop(nextion_listen_list);
    // setFanSpeedBtn.getValue(&dsFanBtn);
    // if (dsFanBtn != 0)
    // {
    //     automaticFanSpeed = false;
    // }
    // else
    // {
    //     automaticFanSpeed = true;
    // }
}

void sendTemperatureAndHumidityData(float humidity, float temperature)
{
    if (isnan(humidity))
    {
        strcpy(Humid, "none");
        strcpy(HumUnit, "");
    }
    else
    {
        dtostrf(humidity, 6, 1, Humid);
        strcpy(HumUnit, "%");
    }

    if (isnan(temperature))
    {
        strcpy(Temp, "none");
        strcpy(TmpUnit, "");
    }
    else
    {
        dtostrf(temperature, 6, 1, Temp);
        strcpy(TmpUnit, "C");
    }

    // home_page
    hTempVal.setText(Temp);
    hHumVal.setText(Humid);
    htempUnit.setText(TmpUnit);
    hhumUnit.setText(HumUnit);

    // room_page
    rTempVal.setText(Temp);
    rHumVal.setText(Humid);
    rtempUnit.setText(TmpUnit);
    rhumUnit.setText(HumUnit);
}