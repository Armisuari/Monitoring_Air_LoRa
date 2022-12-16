#pragma "once"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // Lebar Tampilan Oled, dalam satuan pixels
#define SCREEN_HEIGHT 64 // Tinggi Tampilan Oled, dalam satuan pixels

class Oled
{
    public:
        void init();
        void clear();
        void text_color(uint16_t color);
        void text_size(uint8_t size);
        void set_cursor(int16_t x, int16_t y);
        void end();
    
};