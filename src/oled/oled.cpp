#include "oled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);


void Oled::init()
{
    Serial.begin(115200);
    // Reset Oled Menggunakan Program
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW);
    delay(20);
    digitalWrite(OLED_RST, HIGH);

    // Inisialisasi Oled
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
    { // Alamat 0x3C untuk Oled Ukuran 128x32
        Serial.println(F("Gagal Mengakses SSD1306"));
        for (;;)
            ; // Terus looping selama Oled gagal diakses
    }
}

void Oled::clear()
{
    display.clearDisplay();
}

void Oled::text_color(uint16_t color)
{
    display.setTextColor(color);
}

void Oled::text_size(uint8_t size)
{
    display.setTextSize(size);
}

void Oled::set_cursor(int16_t x, int16_t y)
{
    display.setCursor(x,y);
}

void Oled::end()
{
    display.display();
}