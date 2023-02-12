//----------------------------------------------------Program Lora-----------------------------------------------
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
#define BAND 433E6

void setup() {

  Serial.begin(115200);
  // Pin SPI
  SPI.begin(SCK, MISO, MOSI, SS);
  // Setup Modul Lora
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Gagal Memulai Lora!");
    while (1);
  }

  Serial.println("Berhasil Menjalankan Lora");
  delay(2000);
}

void loop() {

  int jarak;

  // Menampilkan Pembacaan data di serial monitor
  Serial.println();
  Serial.println("Mengirim Data : ");
  Serial.print("Ketinggian Air = ");
  Serial.print(jarak);
  Serial.print(" cm");
  Serial.println();

  // Mengirim Data Lora ke Receiver
  LoRa.beginPacket();
  LoRa.print(jarak);
  LoRa.endPacket();
  jarak++;
  delay(500);
}