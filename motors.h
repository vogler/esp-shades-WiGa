// functions with custom datastructures have to be in their own .h-file, see https://playground.arduino.cc/Code/Enum/

// each relais has 3 connectors (left, middle, right):
// normally 1 and 2 are connected
// once pulled low, 2 will change over to 3 (and the INx LED will light up)
// per motor we use 2 relais: 1. power on/off, 2. up/down
struct motor { unsigned int power_pin; unsigned int dir_pin; };

enum on_off { ON, OFF};

void power(struct motor m, enum on_off o) {
  digitalWrite(m.power_pin, o);
}
