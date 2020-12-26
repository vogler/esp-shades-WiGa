// This controls the shades in my parents' winter garden since the original control unit no longer works reliably.
// There are 3 mains-powered motors (left/middle/right) with cables for PE/N/Up/Down.

#include "secrets.h" // defines WIFI_SSID, WIFI_PASS
#include "wifi_ota.h"

// Control 3 motors with 6 relays. Arduino limitation: 'all functions that require custom datatstructures have to be placed in an additional .h file'
#define T_OFF 80 // turn off relays after this time (s), takes ~60s
#include "motors.h"
struct motor m1 = { D2, D0, D5, D1 };
struct motor m2 = { RX, TX, D8, A0 };
struct motor m3 = { D4, D3, D7, D6 };
struct motor ms[] = { m1, m2, m3 };

#include "server.h"

void setup() {
  Serial.begin(38400);
  Serial.println("setup");
  setup_WiFi();
  setup_OTA();
  setup_WebServer();

  // Need 6 output and 6 input pins, but there are only 9 GPIO on Wemos D1 mini.
  // -> Use RX/TX as GPIO -> no more serial after setup.
  // -> Use A0 as input. Goes low over time -> pull high.
  // D8 is pulled down -> pair with A0.
  // Other pins (except D0 which floats) are high with INPUT_PULLUP.

  // output: 6 relays, 2 for each motor: 1. power on/off, 2. up/down
  // change the UART pins to GPIO, https://arduino.stackexchange.com/questions/29938/how-to-i-make-the-tx-and-rx-pins-on-an-esp-8266-01-into-gpio-pins
  // won't be able to use serial monitor after this, change back with FUNCTION_0
  pinMode(1, FUNCTION_3); // TX
  pinMode(3, FUNCTION_3); // RX
  int output_pins[] = { D4, D3, D2, D0, RX, TX };
  for (int i = 0; i < 6; i++) {
    pinMode(output_pins[i], OUTPUT);
    digitalWrite(output_pins[i], HIGH);
  }

  // input: 6 pins for 3 up/down switches
  // pull down with GND:
  pinMode(D1, INPUT_PULLUP); // 1
  pinMode(D5, INPUT_PULLUP); // 1
  pinMode(D6, INPUT_PULLUP); // 1
  pinMode(D7, INPUT_PULLUP); // 1
  // pull high with 3V3:
  pinMode(D8, INPUT); // 0
  // A0: 8-14, 1024 when shorted to 3V3
}

#define printRead(pin) Serial.printf("%s: %u, ", #pin, digitalRead(pin));

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  
//  printRead(D1);
//  printRead(D5);
//  printRead(D6);
//  printRead(D7);
//  Serial.printf("A0: %u\n", analogRead(A0));

  readMove(m1);
  readMove(m2);
  readMove(m3);
  
  delay(100);
}
