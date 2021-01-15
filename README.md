# esp-shades-WiGa

This controls the shades in my parents' winter garden since the original control unit no longer works reliably.
There are 3 mains-powered motors (left/middle/right) with cables for PE/N/Up/Down each.
The idea was to control the 3 motors with 6 relays, i.e. per motor a relay to turn power on/off and another relay to switch up/down.

The motors can be controlled with
- the spawned webpage,
- via [Espalexa](https://github.com/Aircoookie/Espalexa) (automations in Alexa app (up/down on sunrise/sunset)),
- the 3 up/down wall switches (momentary/push).

The BOM was pretty small/cheap:
- 1.81$ Wemos D1 mini
- 4.47$ 8 channel relay
- 1.90$ HLK-PM01 power supply (or USB charger)
- ~1$ cables and screw terminals

The only tricky part was finding enough usable I/O pins (6 out for relays, 6 in for buttons).
The Wemos D1 mini (had no other ESP with me) has 9 GPIO pins, so I
- turned off serial after boot to use RX/TX as output pins,
- used A0 with a threshold as another digital input.

Photos/videos of the post-christmas ghetto repair: https://photos.app.goo.gl/DnHxpkeWf4EXeaCJ8

<img height=600 src="https://lh3.googleusercontent.com/pw/ACtC-3e5OgZFOk4WTNP6frYuehvYgO9rhEIAY_3M5PQixwPejI4KjUMpPIj20uapj4LYSGza5QwKKZCtb8VbGfKdS3G9VDnRp8ygaTlSu3jcIz1RA-Rr9afxIzTlp5zOdRYrmGbrtvDLRI14RaLZyVwNT41Jqg=w1013-h2192-no?authuser=0" />
<img height=600 src="https://lh3.googleusercontent.com/pw/ACtC-3etxhK9fRQzeHHaUjXg3QbBAP9p_U-_cknw7gIO0Cgf7IJVSR1RY9Tqn56-mfiLlBJpN_RCn2CtOOlhk8VVyrq-COIP-RZ5bA-tghkgTMsALhD2m-lWKGHuZs6QhWbupWBXDeIHfodbc1DkMYCowxHpNg=w1644-h2192-no?authuser=0" />
