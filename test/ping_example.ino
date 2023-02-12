//----------------------------------------------------Program Ultrasonic-----------------------------------------------
// Inisialisasi Pin trig dan echo
#define trig 12
#define echo 13
// Inisialisasi varibel penampung durasi pemancaran sinyal
long durasi;
// Inisialisasi varibel penampung pembacaan data
int jarak;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  durasi = pulseIn(echo, HIGH);
  jarak = durasi * 0.034 / 2;

  Serial.print("jarak = ");
  Serial.print(jarak);
  Serial.println(" cm");
  delay(100);
}