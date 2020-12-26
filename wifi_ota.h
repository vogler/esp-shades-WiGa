// WiFi
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
WiFiClient wifi;

void setup_WiFi() {
  delay(5);
  Serial.printf("Connecting to AP %s", WIFI_SSID);
  const unsigned long start_time = millis();
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  for (int i = 0; WiFi.waitForConnectResult() != WL_CONNECTED && i < 10; i++) {
    #ifdef ESP32
      WiFi.begin(WIFI_SSID, WIFI_PASS); // for ESP32 also had to be moved inside the loop, otherwise only worked on every second boot, https://github.com/espressif/arduino-esp32/issues/2501#issuecomment-548484502
    #endif
    delay(200);
    Serial.print(".");
  }
  const float connect_time = (millis() - start_time) / 1000.;
  Serial.println();
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("Failed to connect to Wifi in %.3f seconds. Going to restart!", connect_time);
    ESP.restart();
  }
  Serial.printf("Connected in %.3f seconds. IP address: ", connect_time);
  Serial.println(WiFi.localIP());
}


// OTA update
#ifdef ESP32
  #include <ESPmDNS.h>
#else
  #include <ESP8266mDNS.h>
#endif
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void setup_OTA() {
  ArduinoOTA.onStart([]() {
    Serial.println("OTA: Start updating ");
    if (ArduinoOTA.getCommand() == U_FLASH) {
      Serial.println("sketch");
    } else { // U_SPIFFS
      Serial.println("filesystem");
    }
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    // OLED_stat("OTA start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA: Done");
    // OLED.clearDisplay(); OLED.display();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA: Progress: %u%%\r", (progress / (total / 100)));
    // OLED_stat("OTA: %u%%", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
    // OLED_stat("OTA fail: %u\n", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
}
