// This controls the shades in my parents' winter garden since the original control unit no longer works reliably.
// There are 3 mains-powered motors (left/middle/right) with cables for PE/N/Up/Down.

#include "secrets.h" // defines WIFI_SSID, WIFI_PASS
#include "wifi_ota.h"

// Control 3 motors with 6 relays. Arduino limitation: 'all functions that require custom datatstructures have to be placed in an additional .h file'
#include "motors.h"

void setup() {
  Serial.begin(38400);
  Serial.println("setup");
  setup_WiFi();
  setup_OTA();

  // output: 6 relays, 2 for each motor: 1. power on/off, 2. up/down
  // change the UART pins to GPIO, https://arduino.stackexchange.com/questions/29938/how-to-i-make-the-tx-and-rx-pins-on-an-esp-8266-01-into-gpio-pins
  // won't be able to use serial monitor after this, change back with FUNCTION_0
  //pinMode(1, FUNCTION_3); // TX
  //pinMode(3, FUNCTION_3); // RX
  // int output_pins[6] = { D3, D4, TX, RX, D0, D8 };
//  int output_pins[] = { D3, D4, D0, D8 };
//  for (int i = 0; i < 4; i++) {
//    pinMode(output_pins[i], OUTPUT);
//    digitalWrite(output_pins[i], HIGH);
//  }

  // input: 6 pins for 3 up/down switches
  pinMode(D0, INPUT_PULLUP); // 0 floating
  pinMode(D8, INPUT_PULLUP); // 0 pull-down
  pinMode(D1, INPUT_PULLUP); // 1
  pinMode(D2, INPUT_PULLUP); // 1
  pinMode(D5, INPUT_PULLUP); // 1
  pinMode(D6, INPUT_PULLUP); // 1
  pinMode(D7, INPUT_PULLUP); // 1
  // A0: 8-14
}

struct motor m1 = { D4, D3 };
struct motor m2 = { D0, D8 };
struct motor m3 = { RX, TX };

#define printRead(pin) Serial.printf("%s: %u, ", #pin, digitalRead(pin));

void loop() {
  ArduinoOTA.handle();
  
  printRead(D0);
  printRead(D1);
  printRead(D2);
  printRead(D5);
  printRead(D6);
  printRead(D7);
  printRead(D8);
  Serial.printf("A0: %u\n", analogRead(A0));
  
  delay(500);

//  delay(5000);
//
//  power(m1, ON);
//  delay(1000);
//  power(m1, OFF);
//  delay(1000);
}
