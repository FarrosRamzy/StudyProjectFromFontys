#include "sprinkler.h"

void ledOn(int pin)
{
  LedCommand command = {pin, true};
  xQueueSend(scenarioQueue, &command, portMAX_DELAY);
}

void ledOff(int pin)
{
  LedCommand command = {pin, false};
  xQueueSend(scenarioQueue, &command, portMAX_DELAY);
}

void taskLEDcontrol(void *parameter)
{
  while (1)
  {
    LedCommand command;
    if (xQueueReceive(scenarioQueue, &command, portMAX_DELAY) == pdTRUE)
    {
      // Execute LED control command
      digitalWrite(command.pin, command.turnOn ? HIGH : LOW);
    }
  }
}

/**
 * @brief first scenario which blinks the first and the fourth LED
 *        by order.
 *
 * @param parameter input parameter for the thread.
 */
void taskScenario1(void *parameter)
{
  while (1)
  {
    for (size_t i = 0; i < NR_OF_BLINKS; i++)
    {
      executeScenes(my_scenes[0], operations[0]);
    }
    vTaskDelete(NULL);
  }
}

/**
 * @brief second scenario which blinks the second and the third LED
 *        by order.
 *
 * @param parameter input parameter for the thread.
 */
void taskScenario2(void *parameter)
{
  while (1)
  {
    for (size_t i = 0; i < NR_OF_BLINKS; i++)
    {
      executeScenes(my_scenes[1], operations[1]);
    }
    vTaskDelete(NULL);
  }
}

/**
 * @brief third scenario where LED 1 blinks before LED 3.
 *
 * @param parameter input parameter for the thread.
 */
void taskScenario3(void *parameter)
{
  while (1)
  {
    for (size_t i = 0; i < NR_OF_BLINKS; i++)
    {
      executeScenes(my_scenes[2], operations[2]);
    }
    vTaskDelete(NULL);
  }
}

/**
 * @brief fourth scenario where all LEDs blink by order.
 *
 * @param parameter input parameter for the thread.
 */
void taskScenario4(void *parameter)
{
  while (1)
  {
    for (size_t i = 0; i < NR_OF_BLINKS; i++)
    {
      executeScenes(my_scenes[3], operations[3]);
    }
    vTaskDelete(NULL);
  }
}

void taskSerialRead(void *parameter)
{
  while (1)
  {
    // Read input from Serial
    if (Serial.available() > 0)
    {
      String input_data = "";

      input_data = Serial.readStringUntil('\n');
      input_data.trim();
      Serial.print("input: ");

      if (input_data == INPUT_1)
      {
        Serial.println(input_data);
        xTaskCreate(taskScenario1, "Scenario1", 1000, NULL, 1, NULL);
      }
      if (input_data == INPUT_2)
      {
        Serial.println(input_data);
        xTaskCreate(taskScenario2, "Scenario2", 1000, NULL, 1, NULL);
      }
      if (input_data == INPUT_3)
      {
        Serial.println(input_data);
        xTaskCreate(taskScenario3, "Scenario3", 1000, NULL, 1, NULL);
      }
      if (input_data == INPUT_4)
      {
        Serial.println(input_data);
        xTaskCreate(taskScenario4, "Scenario4", 1000, NULL, 1, NULL);
      }
    }

    vTaskDelay(50);
  }
}

void executeScenes(String scene[], int operations_per_scene)
{
  for (int i = 0; i < operations_per_scene; i++)
  {
    String operation = scene[i];

    if (operation.startsWith("LED"))
    {
      int pin = nr_of_leds[operation.charAt(3) - '0' - 1];

      if (operation.endsWith("on"))
        ledOn(pin);
      else
        ledOff(pin);
    }
    else if (operation.startsWith("wait"))
    {
      int ms_delay = operation.charAt(5) - '0';
      vTaskDelay(pdMS_TO_TICKS(ms_delay * 100));
    }
  }
}
