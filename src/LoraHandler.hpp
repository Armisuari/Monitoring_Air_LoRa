#pragma once

#include <SPI.h>
#include <LoRa.h>

// Define pin connections to the LoRa module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
// Define frequency for LoRa module, either 433E6 for Asia, 866E6 for Europe, or 915E6 for America. Can also be adjusted to match the frequency of the LoRa module used.
const uint32_t BAND = 433E6;

// Class to handle communication with the LoRa module
class LoraHandler
{

public:
    // Initialize LoRa module and check if successful
    bool begin();

    // Send data over LoRa network
    void lora_send(unsigned int &);
    String lora_rec();
};

bool LoraHandler::begin()
{
    SPI.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DIO0);

    if (!LoRa.begin(BAND))
    {
        Serial.println("Gagal memulai LoRa!");
        return false;
    }

    Serial.println("Berhasil Menjalankan LoRa!");
    return true;
}

void LoraHandler::lora_send(unsigned int &n)
{
    if (LoRa.beginPacket())
    {                     // Check to make sure the packet was started successfully before writing data
        LoRa.write(n);    // Write the data to the packet
        LoRa.endPacket(); // End and send the packet
    }
    else
    { // If there was an error starting the packet, print an error message
        Serial.println("Error sending packet");
    }
}

String LoraHandler::lora_rec()
{
    if (LoRa.parsePacket())
    {
        Serial.print("Menerima data ...");

        String data = "";

        while (LoRa.available())
        {
            data += (char)LoRa.read();
        }

        return data;
    }
    else
    {
        return "";
    }
}