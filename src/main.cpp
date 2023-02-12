#include <Arduino.h>
#include <Wire.h>

#include "PingHandler.hpp"
#include "OledHandler.hpp"
#include "LoraHandler.hpp"

#define RECEIVER // uncomment this if the task as TRANSMITTER

// NTP server
const char *ntpServer = "pool.ntp.org";

// object
PingHandler ping(12, 13);
OledHandler oled;
LoraHandler lora;

void lora_manager(void *pv);
void displayHandler(void *pv);
void get_distance(void *pv);

unsigned int jarak;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  // NTP time sync
  configTime(0, 0, ntpServer);

  if (lora.begin() && oled.begin())
  {
    Serial.println("LoRa dan Oled aktif");

    oled.clear();
    oled.setCursor(0, 0);
    oled.print_text(WHITE, 1, "LoRa aktif");

    xTaskCreate(get_distance, "pingTask", 1024 * 10, NULL, 15, NULL);      // Create display task with stack size of 5KB and priority of 1
    xTaskCreate(displayHandler, "displayTask", 1024 * 10, NULL, 10, NULL); // Create display task with stack size of 5KB and priority of 1
    xTaskCreate(lora_manager, "LoRaTask", 1024 * 10, NULL, 1, NULL);       // Create LoRa task with stack size of 10KB and priority of 1
  }
  else
  {
    Serial.println("Gagal mendeteksi Oled dan LoRa...");
  }
}

void loop()
{
  vTaskDelete(NULL);
}

void get_distance(void *pv)
{
  while (true)
  {
    jarak = ping.getDistance();
    vTaskDelay(500);
  }
}

void displayHandler(void *pv)
{
  for (;;)
  {
    oled.clear();
    oled.setCursor(28, 0);
    oled.print_text(WHITE, 1, "TRANSMITTER");

    oled.setCursor(0, 20);
    oled.print_text(WHITE, 1, "Sending data .....");

    oled.setCursor(0, 35);
    oled.print_text(WHITE, 1, "Water Level: ");

    oled.setCursor(0, 50);
    oled.print_text(WHITE, 1, jarak + " cm");

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void lora_manager(void *pv)
{
  while (true)
  {
    #ifndef RECEIVER
    lora.lora_send(jarak);
    #else
    lora.lora_rec();
    #endif
    vTaskDelay(500);
  }
}