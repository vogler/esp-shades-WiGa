# esp-shades-WiGa

This controls the shades in my parents' winter garden since the original control unit no longer works reliably.
There are 3 mains-powered motors (left/middle/right) with cables for PE/N/Up/Down each.
The idea was to control the 3 motors with 6 relays, i.e. per motor a relay to turn power on/off and another relay to switch up/down.

The motors can be controlled with
- the spawned webpage,
- via [Espalexa](https://github.com/Aircoookie/Espalexa) (automations in Alexa app (up/down on sunrise/sunset)),
- the 3 up/down wall switches (momentary/push).

The BOM is pretty small/cheap:
- Wemos D1 mini
- 8 channel relay
- cables and screw terminals

The only tricky part was finding enough usable I/O pins (6 out for relays, 6 in for switches).
The Wemos D1 mini (had no other ESP with me) has 9 GPIO pins, so I
- turned off serial after boot to use RX/TX as output pins,
- used A0 with a threshold as another digital input.
