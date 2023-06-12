#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin Oled
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // Lebar Tampilan Oled, dalam satuan pixels
#define SCREEN_HEIGHT 64 // Tinggi Tampilan Oled, dalam satuan pixels

// Adafruit_SSD1306 *display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

class OledHandler
{

private:
    Adafruit_SSD1306 *display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

public:
    bool begin();

    void clear();

    void setCursor(int8_t, int8_t);

    void print_text(uint16_t, uint8_t, const char *);

    void print_text(uint16_t, uint8_t, unsigned int &);
};

bool OledHandler::begin()
{
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW);
    delay(20);
    digitalWrite(OLED_RST, HIGH);

    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
    {
        Serial.println("Failed to access SSD1306");
        return false;
    }

    return true;
}

void OledHandler::clear()
{
    display->clearDisplay();
    display->setCursor(0, 0); // Set the cursor to the top left corner of the screen
}

void OledHandler::setCursor(int8_t x, int8_t y)
{
    display->setCursor(x, y);
}

void OledHandler::print_text(uint16_t color, uint8_t size, const char *text)
{
    display->setTextColor(color);
    display->setTextSize(size);
    display->print(text);
    display->display();
}

void OledHandler::print_text(uint16_t color, uint8_t size, unsigned int &text)
{
    display->setTextColor(color);
    display->setTextSize(size);
    display->print(text);
    display->display();
}
