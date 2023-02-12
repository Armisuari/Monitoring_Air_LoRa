// ----------------------------------------------------Program Oled-----------------------------------------------
// Library Oled Display
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

void setup() {

  Serial.begin(115200);
  // Reset Oled Menggunakan Program
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  // Inisialisasi Oled
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Alamat 0x3C untuk Oled Ukuran 128x32
    Serial.println(F("Gagal Mengakses SSD1306"));
    for(;;);    // Terus looping selama Oled gagal diakses
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Testing Oled");
  display.display();
  Serial.println("Pengujian Oled");
}

void loop() {

  display.clearDisplay();
  display.setCursor(28,0);
  display.println("TRANSIMITTER");
  display.setCursor(0,20);
  display.setTextSize(1);
  display.println("Mengirim Data .....");
  display.setCursor(0,35);
  display.println("Ketinggian Air : ");
  display.setCursor(0,50);
  display.println(" ");
  display.setCursor(20,50);
  display.print("cm");
  display.display();
  delay(500);
}