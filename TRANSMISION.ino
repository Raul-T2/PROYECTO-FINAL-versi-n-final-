TRANSMISION LED FIJO

#include "DHT.h"
#include <Wire.h>
#include <SSD1306Wire.h> // Librería para display OLED

#define DHTPIN 16 // Pin para el sensor DHT11
#define DHTTYPE DHT11 // Tipo de sensor DHT

DHT dht(DHTPIN, DHTTYPE);
SSD1306Wire display(0x3c, 21, 22); // Configuración para OLED 0.96" con dirección I2C 0x3C

int manualTemp = 25; // Temperatura inicial
int manualHumi = 50; // Humedad inicial

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10); // Fuente pequeña para más información
  display.display();
  display.clear();
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command.startsWith("temp ")) {
      manualTemp = command.substring(5).toInt();
    } else if (command.startsWith("humi ")) {
      manualHumi = command.substring(5).toInt();
    } else if (command == "soplar") {
      manualTemp += 5;
      manualHumi += 10;
    }
  }

  String tempBinary = String(manualTemp, BIN);
  String humiBinary = String(manualHumi, BIN);

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Temp: " + String(manualTemp) + " C");
  display.drawString(0, 14, "Hum: " + String(manualHumi) + "%");
  display.drawString(0, 28, "Bin Temp: " + tempBinary);
  display.drawString(0, 42, "Bin Hum: " + humiBinary);
  display.display();

  delay(1000); // Tiempo de espera entre actualizaciones
}