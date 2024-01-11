// Einbindung der verwendeten Bibliotheken
#include <SPI.h>
#include <SD.h>

// Erstellen einer Textdokument-Variable mit dem Namen "Textdokument"
File Textdatei;

// Erstellen einer konstanten Integer Variable mit dem Namen "chipSelect" und Inhalt "4", den Pin referenzierend an dem die SD-Karte angeschlossen ist
const int chipSelect = 4;

// Starten der setup() Funktion, weche ausschließlich einmal zu Begin abläuft
void setup() {

  // Starten des seriellen Monitors
  Serial.begin(9600);

  // Starten der Kommunikation mit der SD-Karte, Zuweisung ihres Pins und warten auf dessen Start
  Serial.println("Initialisiere SD-Karte");
  if (!SD.begin(chipSelect)){
    Serial.println("Initialisierung fehlgeschlagen!");
    return;
  }
  Serial.println("Initialisierung abgeschlossen");

  // Löschen der Textdatei "test.txt" von der SD-Karte
  SD.remove("test.txt");

  // Erstellen und öffnen der Textdatei "test.txt" von der SD-Karte sowie Speicherung dieser in der Textdokument-Variable "Textdokument"
  Textdatei = SD.open("test.txt", FILE_WRITE);

  // Abfrage der Verbindung zum Textdokument "test.txt"
  if (Textdatei) 
  {
    // Beschreiben des Textdokument "test.txt" mit dem  in Anführungzeichen zu sehenden Textes bei erfolgreicher Verbindung
    Textdatei.println("TEST");
  } 
  else 
  {
    // Ausgabe des in den Anführungzeichen zu sehenden Textes auf dem seriellen Monitor bei fehlgeschlagener Verbindung
    Serial.println("Textdatei konnte nicht erstellt oder geöffnet werden");
  }

  // Schließen der Textdatei "test.txt"
  Textdatei.close();
}

// Starten der loop() Funktion, weche sich nach ablaufen der setup() Funktion dauerhaft wiederholt
void loop(){
  
}
