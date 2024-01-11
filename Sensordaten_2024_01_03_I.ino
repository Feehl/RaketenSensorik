// Einbindung der verwendeten Bibliotheken
#include <SPI.h>
#include <SD.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Umbenennung des Sensors zu mpu
Adafruit_MPU6050 mpu;

// Erstellen einer Textdokument-Variable mit dem Namen "Textdokument"
File Textdatei;

// Erstellen einer konstanten Integer Variable mit dem Namen "chipSelect" und Inhalt "4", den Pin referenzierend an dem die SD-Karte angeschlossen ist
const int chipSelect = 4;

// Starten der setup() Funktion, weche ausschließlich einmal zu Begin abläuft
void setup(void) {

  // Starten des seriellen Monitors und warten auf dessen Start
  Serial.begin(2000000);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // Starten der Kommunikation mit der SD-Karte, Zuweisung ihres Pins und warten auf dessen Start
  Serial.println("Initialisiere SD-Karte");
  if (!SD.begin(chipSelect)){
    Serial.println("Initialisierung fehlgeschlagen!");
    return;
  }
  Serial.println("Initialisierung abgeschlossen");

  // Löschen der Textdatei "test.txt" von der SD-Karte
  SD.remove("test.txt");
  
  // Ausgabe des in den Anführungzeichen zu sehenden Textes auf dem seriellen Monitor
  Serial.println("Adafruit MPU6050 test!");

  // Starten der Messungen des Sensors und warten auf dessen Start
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Festlegung der Genauigkeit des Beschleunigungssensors
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // Festlegung der Genauigkeit des Gyroskops
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  // Festlegung der Messfrequenz
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
  Serial.println("");

  // Anweisung zum hundertmillisekündigen warten des Programs vor dem weiteren ablaufen
  delay(100);
}

// Starten der loop() Funktion, weche sich nach ablaufen der setup() Funktion dauerhaft wiederholt
void loop() {

  // Erstellen und öffnen der Textdatei "test.txt" von der SD-Karte sowie Speicherung dieser in der Textdokument-Variable "Textdokument"
  Textdatei = SD.open("test.txt", FILE_WRITE);

  // Initialisierung und Benennung der Messungen
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Abfrage der Verbindung zum Textdokument "test.txt"
  if (Textdatei)
  {
    // Ausgabe des in den Anführungzeichen zu sehenden Textes und der dazugehörigen Sensorwerte auf dem seriellen Monitor bei erfolgreicher Verbindung
    Serial.println(millis()); 
    Serial.print(String(a.acceleration.x) + ";" + String(a.acceleration.y) + ";");
    Serial.println(String(a.acceleration.z));
    Serial.print(String(g.gyro.x) + ";" + String(g.gyro.y) + ";");
    Serial.println(String(g.gyro.z));

    // Beschreiben des Textdokument "test.txt" mit dem  in Anführungzeichen zu sehenden Textes und der dazugehörigen Sensorwerte bei erfolgreicher Verbindung
    Textdatei.println(millis());
    Textdatei.print(String(a.acceleration.x) + ";" + String(a.acceleration.y) + ";");
    Textdatei.println(String(a.acceleration.z));
    Textdatei.print(String(g.gyro.x) + ";" + String(g.gyro.y) + ";");
    Textdatei.println(String(g.gyro.z));
  }
  else 
  {
    // Ausgabe des in den Anführungzeichen zu sehenden Textes auf dem seriellen Monitor bei fehlgeschlagener Verbindung
    Serial.println("Textdatei konnte nicht erstellt oder geöffnet werden");
  }

  // Schließen der Textdatei "test.txt"
  Textdatei.close();
}
