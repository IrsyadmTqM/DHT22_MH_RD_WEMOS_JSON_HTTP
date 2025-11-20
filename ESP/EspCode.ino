#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define DHTPIN 5        // D5
#define DHTTYPE DHT22
#define RAIN_SENSOR A0  // Pin analog ESP8266

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "----_ATAS";
const char* password = "0702061509";
const char* serverUrl = "http://---.---.---.3:3000/simpan_data"; // dari ip address laptop  di ipconfig

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(2000);

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung!");
  Serial.print("IP ESP8266: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // === BACA SENSOR HUJAN ===
  int sensorValue = analogRead(RAIN_SENSOR);
  String statusHujan;

  if (sensorValue < 400) statusHujan = "Hujan Lebat";
  else if (sensorValue < 700) statusHujan = "Hujan Ringan";
  else statusHujan = "Tidak Hujan";

  Serial.print("Rain Value: ");
  Serial.print(sensorValue);
  Serial.print(" -> ");
  Serial.println(statusHujan);

  // === BACA SENSOR DHT ===
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("❌ Gagal baca sensor DHT!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Hum: ");
  Serial.print(hum);
  Serial.println(" %");

  // === KIRIM DATA KE SERVER ===
  if (WiFi.status() == WL_CONNECTED) {
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["temperature"] = temp;
    jsonDoc["humidity"] = hum;
    jsonDoc["rain_value"] = sensorValue;
    jsonDoc["rain_status"] = statusHujan;

    String jsonData;
    serializeJson(jsonDoc, jsonData);

    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(jsonData);

    Serial.print("📤 Kirim JSON: ");
    Serial.println(jsonData);
    Serial.print("📡 Status HTTP: ");
    Serial.println(httpCode);

    if (httpCode > 0) {
      Serial.println("✔️ Data terkirim!");
      Serial.println(http.getString());
    } else {
      Serial.println("❌ Gagal kirim data!");
    }

    http.end();
  } else {
    Serial.println("⚠️ WiFi tidak terhubung!");
  }

  delay(5000);
}
