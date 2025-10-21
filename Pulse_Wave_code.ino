#include <PulseSensorPlayground.h> // pulse sensor
#include <WiFi.h>
#include "ThingSpeak.h"
#include <DFRobot_MLX90614.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // LCD library

// LCD setup (I2C address 0x27 or 0x3F depending on your module)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "VodafoneMobileWiFi-B53841";   // WiFi
const char* password = "8387714391"; 

const int PulseWire = 34;  // Pulse sensor pin
int Threshold = 550;
int myBPM = 0;

WiFiClient  client;
PulseSensorPlayground pulseSensor;  // PulseSensor object
DFRobot_MLX90614_I2C sensor;        // Temp sensor object

unsigned long myChannelNumber = 1;  // ThingSpeak
const char * myWriteAPIKey = "E84C1QVAEVVBPPPV";
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void setup() {
  Serial.begin(115200);  
  pinMode(34, INPUT);

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Wire.begin();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");

  // Pulse sensor setup
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   

  if (pulseSensor.begin()) {
    Serial.println("PulseSensor initialized successfully!");
  } else {
    Serial.println("PulseSensor failed to initialize. Check wiring.");
  }

  // Temp sensor setup
  while (NO_ERR != sensor.begin()) {
    Serial.println("Temp sensor failed, check wiring");
    delay(3000);
  }
  Serial.println("Temp sensor OK!");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Reconnect WiFi if needed
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting WiFi reconnect...");
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password); 
        delay(500);     
      } 
      Serial.println("\nReconnected.");
    }

    // Pulse reading
    if (pulseSensor.sawStartOfBeat()) {  
      myBPM = pulseSensor.getBeatsPerMinute();

      if (myBPM > 40 && myBPM < 180) {
        Serial.println("♥ Normal heartbeat detected!");
        Serial.print("BPM: ");
        Serial.println(myBPM);
      } else {
        Serial.println("⚠ Abnormal/Noisy reading.");
        Serial.print("BPM: ");
        Serial.println(myBPM);
      }
    }

    // Temp reading
    float ambientTemp = sensor.getAmbientTempCelsius();
    float objectTemp  = sensor.getObjectTempCelsius();
    Serial.print("Ambient: ");
    Serial.print(ambientTemp);
    Serial.println(" °C");
    Serial.print("Object: ");
    Serial.print(objectTemp);
    Serial.println(" °C");

    // Send to ThingSpeak
    ThingSpeak.setField(1, myBPM);
    ThingSpeak.setField(2, objectTemp);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (x == 200) {
      Serial.println("Channel update successful.");
    } else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    // Show on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BPM: ");
    lcd.print(myBPM);

    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(objectTemp, 1); // 1 decimal place
    lcd.print("C");

    lastTime = millis();
  }

  delay(100);
}
