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

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);
Adafruit_SSD1306 *display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

class OledHandler
{
public:
    bool begin();
    void clear();
    void setCursor(int8_t, int8_t);
    void print_text(uint16_t, uint8_t, const char *);
};

bool OledHandler::begin()
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

void OledHandler::clear() { display->clearDisplay(); }

void OledHandler::setCursor(int8_t x, int8_t y) { 
    display->setCursor(x, y); 
}

void OledHandler::print_text(uint16_t color, uint8_t size, const char *text)
{
    display->setTextColor(color);
    display->setTextSize(size);
    display->print(text);
    display->display();
}
