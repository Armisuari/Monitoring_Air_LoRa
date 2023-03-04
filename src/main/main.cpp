#include <Arduino.h>
#include <Wire.h>

#include "PingHandler.hpp"
#include "OledHandler.hpp"
#include "LoraHandler.hpp"
// #include "FuzzyHandler.hpp"

// #define RECEIVER // uncomment this if the task as TRANSMITTER

// NTP server
const char *ntpServer = "pool.ntp.org";

// // object
PingHandler ping(13, 12); // trig, echo
OledHandler oled;
LoraHandler lora;
// // FuzzyHandler fuzzy();

void lora_manager(void *pv);
void displayHandler(void *pv);
void get_distance(void *pv);

void setup()
{
  Serial.begin(115200);
  // delay(1000);

  // NTP time sync
  configTime(0, 0, ntpServer);

  // lora.begin();
  // oled.begin();

  // oled.clear();
  // oled.setCursor(0, 0);
  // oled.print_text(WHITE, 1, "OLED TEST...");

  if (lora.begin() && oled.begin())
  {
    Serial.println("LoRa dan Oled aktif");

    oled.clear();
    oled.setCursor(0, 0);
    oled.print_text(WHITE, 1, "LoRa aktif");

    xTaskCreate(get_distance, "pingTask", 1024 * 10, NULL, 10, NULL);      // Create display task with stack size of 5KB and priority of 1
    xTaskCreate(displayHandler, "displayTask", 1024 * 10, NULL, 10, NULL); // Create display task with stack size of 5KB and priority of 1
    // xTaskCreate(lora_manager, "LoRaTask", 1024 * 10, NULL, 1, NULL);       // Create LoRa task with stack size of 10KB and priority of 1
  }
  else
  {
    Serial.println("Gagal mendeteksi Oled dan LoRa...");

    oled.clear();
    oled.setCursor(0, 0);
    oled.print_text(WHITE, 1, "Gagal mendeteksi LoRa");
  }
}

unsigned int jarak{0};

void loop()
{
  vTaskDelete(NULL);
}

// String get_time()
// {
//   time_t epoch_time = time(NULL);
//   struct tm *time_info = localtime(&epoch_time);

//   char buffer[80];
//   strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
//   std::string str(buffer);

//   return str.c_str();
// }

void get_distance(void *pv)
{
  while (true)
  {
    jarak = ping.getDistance();
    Serial.printf("Distance: %d cm\n", jarak);
    vTaskDelay(500);
  }
}

void displayHandler(void *pv)
{
  for (;;)
  {
    oled.clear();
    oled.setCursor(28, 0);

#ifndef RECEIVER
    oled.print_text(WHITE, 1, "TRANSMITTER");

    oled.setCursor(0, 20);
    oled.print_text(WHITE, 1, "Sending data .....");
#else
    oled.print_text(WHITE, 1, "RECEIVER");

    oled.setCursor(0, 20);
    oled.print_text(WHITE, 1, "Receiving data .....");
#endif

    oled.setCursor(0, 35);
    oled.print_text(WHITE, 1, "Water Level: ");

    oled.setCursor(0, 50);
    oled.print_text(WHITE, 1, jarak + " cm");

    vTaskDelay(500 / portTICK_PERIOD_MS);
    // vTaskDelay(500);
  }
}

// void lora_manager(void *pv)
// {
//   while (true)
//   {
// #ifndef RECEIVER
//     String payload;
//     payload = get_time() + " " + String(jarak);

//     lora.lora_send(payload);
// #else

//     String rec_data = lora.lora_rec();
//     int count = 0;
//     String substrings[10];

//     for (int i = 0; i < rec_data.length(); i++)
//     {
//       if (rec_data[i] == ' ')
//       {
//         count++;
//       }
//       else
//       {
//         substrings[count] += rec_data[i];
//       }
//     }
//     Serial.println("received data: " + substrings[1]); // Print the second substring of the received data
//     unsigned int rec_val = substrings[1].toInt();      // Convert the second substring of the received data to an integer

// #endif
//     vTaskDelay(500);
//   }
// }