// Starten der setup() Funktion, weche ausschließlich einmal zu Begin abläuft
void setup() {
  
  // Starten des seriellen Monitors
  Serial.begin(115200);
  
}

// Starten der loop() Funktion, weche sich nach ablaufen der setup() Funktion dauerhaft wiederholt
void loop() {
  
  // Ausgabe der millis() Funktion auf dem seriellen Monitor
  Serial.println(millis());
  
  // Anweisung zum einsekündigen warten des Programs vor dem weiteren ablaufen
  delay(1000);
  
  // Erstellen einer String Variable mit dem Namen "ka" und Inhalt "Hallo "
  String ka = "Hallo ";
  
  // Erstellen einer Integer Variable mit dem Namen "a" und Inhalt "800"
  int a = 800;
  
  // Ausgabe der der Kombination aus dem String "ka" und der Integer a, welche zuvor in einen String konvertiert wird, auf dem seriellen Monitor
  Serial.println(ka + String(a));
  
}
