#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

#include "PingHandler.hpp"
#include "OledHandler.hpp"
#include "LoraHandler.hpp"
#include "FuzzyHandler.h"

#define RECEIVER // uncomment this if the task as TRANSMITTER

const char *ssid = "Raspberrypi";
const char *password = "1122334455";

// NTP server
const char *ntpServer = "pool.ntp.org";

// // object
PingHandler ping(13, 12); // trig, echo
OledHandler oled;
LoraHandler lora;

void lora_manager(void *pv);
void displayHandler(void *pv);
void get_distance(void *pv);
void FuzzyHandler(void *pv);

unsigned int jarak;
String jarak_;

unsigned int rec_val;

void setup()
{
  Serial.begin(115200);
  // delay(1000);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print IP address
  Serial.print("Connected to Wi-Fi network with IP address: ");
  Serial.println(WiFi.localIP());

  // NTP time sync
  configTime(0, 0, ntpServer);

  if (lora.begin() && oled.begin())
  {
    Serial.println("LoRa dan Oled aktif");

    oled.clear();
    oled.setCursor(0, 0);
    oled.print_text(WHITE, 1, "LoRa aktif");
    delay(3000);
    oled.clear(); //

#ifndef RECEIVER
    xTaskCreate(get_distance, "pingTask", 1024 * 10, NULL, 1, NULL); // Create display task with stack size of 5KB and priority of 1
#endif
    setup_fuzzy();

    xTaskCreate(displayHandler, "displayTask", 1024 * 10, NULL, 1, NULL); // Create display task with stack size of 5KB and priority of 1
    xTaskCreate(lora_manager, "LoRaTask", 1024 * 10, NULL, 10, NULL);     // Create LoRa task with stack size of 10KB and priority of 10
    xTaskCreate(FuzzyHandler, "FuzzyTask", 1024 * 10, NULL, 15, NULL);     // Create Fuzzy task with stack size of 10KB and priority of 15
  }
  else
  {
    Serial.println("Gagal mendeteksi Oled dan LoRa...");

    oled.clear();
    oled.setCursor(0, 0);
    oled.print_text(WHITE, 1, "Gagal mendeteksi LoRa");
  }
}
// String jarak;

void LoraHandler::lora_rec()
{
  if (LoRa.parsePacket())
  {
    // Paket  data di terima
    Serial.println("Menerima Data ...");

    // Membaca paket data
    while (LoRa.available())
    {
      jarak = LoRa.readString().toInt();
    }
  }
}

void loop()
{
  // lora.lora_rec();
  // Serial.printf("data: %d cm\n", jarak);
  // delay(500);
  vTaskDelete(NULL);
}

String get_time()
{
  time_t epoch_time = time(NULL) + 28800;
  struct tm *time_info = gmtime(&epoch_time);

  char buffer[80];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
  std::string str(buffer);

  return str.c_str();
}

void get_distance(void *pv)
{
  while (true)
  {
    jarak = ping.getDistance();
    // Serial.printf("Distance: %d cm\n", jarak);
    vTaskDelay(500);
  }
}

unsigned int jarak_prev{0};

void displayHandler(void *pv)
{
  for (;;)
  {
    if (jarak_prev != jarak)
    {
      jarak_prev = jarak;
      oled.clear();
    }

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

    oled.setCursor(78, 35);
    oled.print_text(WHITE, 1, jarak);

    oled.setCursor(85, 35);
    oled.print_text(WHITE, 1, " CM");

    vTaskDelay(500 / portTICK_PERIOD_MS);
    // vTaskDelay(50  0);
  }
}

int convertToInt(String payload);

void lora_manager(void *pv)
{
  while (true)
  {
#ifndef RECEIVER
    String payload;
    payload = String(jarak);
    Serial.println(payload + " cm");

    lora.lora_send(payload);
#else

    lora.lora_rec();
    String payload = get_time() + " distance: " + jarak + " cm";
    Serial.println(payload);

    rec_val = convertToInt(payload);

#endif
    vTaskDelay(500);
  }
}

int convertToInt(String payload)
{
  int count = 0;
  String substrings[10];

  for (int i = 0; i < payload.length(); i++)
  {
    if (payload[i] == ' ')
    {
      count++;
    }
    else
    {
      substrings[count] += payload[i];
    }
  }
  Serial.println("received data: " + substrings[1]); // Print the second substring of the received data

  return substrings[2].toInt(); // Convert the second substring of the received data to an integer
}

void FuzzyHandler(void *pv)
{
  while (true)
  {
    int input = rec_val;

    Serial.println("\n\n\nEntrance: ");
    Serial.print("\t\t\tDistance: ");
    Serial.println(input);

    fuzzy->setInput(1, input);
    fuzzy->fuzzify();

    int output = fuzzy->defuzzify(1);

    if (output <= 28)
      Serial.printf("Result:\n\t\t\taman (%d)\n", output);
    else if (output >= 25 && output <= 53)
      Serial.printf("Result:\n\t\t\tsiaga (%d)\n", output);
    else if (output >= 50 && output <= 78)
      Serial.printf("Result:\n\t\t\tbahaya (%d)\n", output);
    else if (output >= 75 && output <= 100)
      Serial.printf("Result:\n\t\t\tbanjir (%d)\n", output);
    else
      Serial.println("Result:\n\t\t\tout of range");

    // Serial.println("Result: ");
    // Serial.print("\t\t\tServo: ");
    // Serial.println(output);

    vTaskDelay(12000);
  }
}