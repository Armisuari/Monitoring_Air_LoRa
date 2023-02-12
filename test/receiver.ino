//----------------------------------------------------Program Receiver-----------------------------------------------

// Library Lora
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Inisiailassi Pin yang digunakan Pada Modul Lora
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
// 433E6 Untuk Asia, 866E6 Untuk Eropa, 915E6 Untuk Amerika
// Atau bisa disesuaikan dengan frekuensia yang tertera pada modul Lora yang digunakan
// Inisialisasi Variabel BAND untuk menyimpan nilai frekuensi Modul Lora
#define BAND 433E6

// Pin Oled
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // Lebar Tampilan Oled, dalam satuan pixels
#define SCREEN_HEIGHT 64 // Tinggi Tampilan Oled, dalam satuan pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// Inisialisasi varibel penampung data dari transmitter
String LoRaData;

void setup() {
  Serial.begin(115200);

  // Reset Oled Menggunakan Program
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  // Inisialisasi Oled
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Alamat 0x3C untuk 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Terus looping selama Oled gagal diakses
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("RECEIVER");
  display.display();

  Serial.println("Pengujian Receiver");

  // Pin lora SPI
  SPI.begin(SCK, MISO, MOSI, SS);
  // Setup Modul Lora Transceiver
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Gagal Memulai Lora");
    while (1);
  }
  Serial.println("Berhasil Menjalankan Lora");
  display.setCursor(0,10);
  display.println("Berhasil Menjalankan Lora");
  display.display();
}

void loop() {

  // Memeriksa Paket data dari transmitter
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Paket  data di terima
    Serial.print("Menerima Data ...");

    // Membaca paket data
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

   // Tampilan Oled
  display.clearDisplay();
  display.setCursor(26,0);
  display.println("RECEIVER");
  display.setCursor(0,20);
  display.setTextSize(1);
  display.println("Menerima Data .....");
  display.setCursor(0,35);
  display.println("Ketinggian Air : ");
  display.setCursor(0,50);
  display.println(LoRaData);
  display.setCursor(20,50);
  display.print("cm");
  display.display();
  }

}