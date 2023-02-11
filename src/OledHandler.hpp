#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Pin Oled
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // Lebar Tampilan Oled, dalam satuan pixels
#define SCREEN_HEIGHT 64 // Tinggi Tampilan Oled, dalam satuan pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

class OledHandler
{
public:
    bool begin(Adafruit_SSD1306 *);
};

bool OledHandler::begin(Adafruit_SSD1306 *display)
{
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
    { // Alamat 0x3C untuk Oled Ukuran 128x32
        Serial.println(F("Gagal Mengakses SSD1306"));
        for (;;)
            ; // Terus looping selama Oled gagal diakses
    }

    return true;
}