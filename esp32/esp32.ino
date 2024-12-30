#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
#include <MFRC522.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

#define RST_PIN   22
#define SS_PIN    21
#define LED_PIN   2
#define BUZZER_PIN 13

// MFRC522 -> RFID MODEL
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create an MFRC522 instance
byte storedCard[4];   // Store the registered card ID
bool isRegistered = false;
bool cardDetected = false;

WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  
  SPI.begin(18, 19, 23, 21);  // SCK, MISO, MOSI, SS
  mfrc522.PCD_Init();         // Initialize the MFRC522

  // Conecta no WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/ON", HTTP_GET, []() {
    digitalWrite(LED_PIN, HIGH);
    server.send(200, "text/plain", "LED ON");
  });

  server.on("/OFF", HTTP_GET, []() {
    digitalWrite(LED_PIN, LOW);
    server.send(200, "text/plain", "LED OFF");
  });

  server.on("/rfid", HTTP_GET, []() {
    server.send(200, "text/plain", cardDetected ? "1" : "0");
    cardDetected = false;
  });

  server.begin();
}

// Success beep function
void successBeep() {
  tone(BUZZER_PIN, 1000);  // 1kHz beep
  delay(200);
  noTone(BUZZER_PIN);
}

// Error beep function
void errorBeep() {
  tone(BUZZER_PIN, 400);  // Error beep has lower frequency
  delay(100);
  noTone(BUZZER_PIN);
  delay(100);
  tone(BUZZER_PIN, 400);
  delay(100);
  noTone(BUZZER_PIN);
}

// Register beep function
void registrationBeep() {
  tone(BUZZER_PIN, 800);
  delay(500);
  noTone(BUZZER_PIN);
}

void loop() {
  server.handleClient();

  // Search for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // If no card is registered, register this one
  if (!isRegistered) {
    for (byte i = 0; i < 4; i++) {
      storedCard[i] = mfrc522.uid.uidByte[i];
    }
    isRegistered = true;
    Serial.println("Card registered!");
    digitalWrite(LED_PIN, HIGH);
    registrationBeep();  // Long beep for registration
    digitalWrite(LED_PIN, LOW);
  }
  // If a card is already registered, check if it is the correct card
  else {
    bool authorized = true;
    for (byte i = 0; i < 4; i++) {
      if (mfrc522.uid.uidByte[i] != storedCard[i]) {
        authorized = false;
        break;
      }
    }

    if (authorized) {
      Serial.println("Access granted!");
      cardDetected = true;
      digitalWrite(LED_PIN, HIGH);
      successBeep();  // Single beep for success
      digitalWrite(LED_PIN, LOW);
    } else {
      Serial.println("Access denied!");
      digitalWrite(LED_PIN, HIGH);
      errorBeep();    // Double beep for error
      digitalWrite(LED_PIN, LOW);
    }
  }

  // Stop PICC
  mfrc522.PICC_HaltA();
}