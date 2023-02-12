//----------------------------------------------------Program Transmitter-----------------------------------------------

// Inisialisai Pin TRIG dan ECHO dari sensor Ultrasonic
#define trig 12
#define echo 13
// Inisialisasi Variabel penampung durasi pemancaran gelombang
long durasi;
int jarak;

// Inisialisasi Pin Selenoid
#define selenoid 2
//packet counter
int counter = 0;

// Library LoRa
#include <SPI.h>
#include <LoRa.h>
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
#define BAND 866E6

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
  display.print("Transimitter");
  display.display();

  Serial.println("Pengujian Transmitter");

  // Pin Lora SPI
  SPI.begin(SCK, MISO, MOSI, SS);
  // Setup Modul Lora
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Gagal Memulai Lora!");
    while (1);
  }
  Serial.println("Berhasil Menjalankan Lora");
  display.setCursor(0,10);
  display.print("Berhasil Menjalankan Lora");
  display.display();
  delay(2000);

  // Inisialisasi pin selenoid menjadi OUTPUT
  pinMode(selenoid, OUTPUT);

  // Inisialisasi pin trig, dan echo menjadi Input dan Output
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {

  // Proses pembacaan data sensor ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  durasi = pulseIn(echo, HIGH);
  jarak = durasi * 0.034 / 2;

  // Menampilkan Pembacaan data di serial monitor
  Serial.println();
  Serial.println("Mengirim Data : ");
  Serial.print("Ketinggian Air = ");
  Serial.print(jarak);
  Serial.print(" CM");
  Serial.println();

  // Mengirim Data Lora ke Receiver
  LoRa.beginPacket();
  LoRa.print(jarak);
  LoRa.endPacket();

  display.clearDisplay();
  display.setCursor(28,0);
  display.println("TRANSIMITTER");
  display.setCursor(0,20);
  display.setTextSize(1);
  display.println("Mengirim Data .....");
  display.setCursor(0,35);
  display.println("Ketinggian Air : ");
  display.setCursor(0,50);
  display.println(jarak);
  display.setCursor(20,50);
  display.print("cm");
  display.display();

  if (jarak > 50){
    Serial.println("Banjir");
    digitalWrite(selenoid, HIGH);
  }

  else{
    digitalWrite(selenoid, LOW);
  }

  delay(500);

}