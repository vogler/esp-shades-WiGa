// functions with custom datastructures have to be in their own .h-file, see https://playground.arduino.cc/Code/Enum/

// each relais has 3 connectors (left, middle, right):
// normally 1 and 2 are connected
// once pulled low, 2 will change over to 3 (and the INx LED will light up)
// per motor we use 2 relais: 1. power on/off, 2. up/down

enum state { STOP, MDOWN, MUP };  // currently stopped, moving down or up

struct motor {
  const byte power_pin;
  const byte dir_pin;
  const byte down_pin;
  const byte up_pin;
  enum state state;
  unsigned long lastMove;
};

enum power { ON, OFF };
enum dir   { UP, DOWN };

void power(struct motor &m, enum power o) {
  digitalWrite(m.power_pin, o);
}

void ch_dir(struct motor &m, enum dir d) {
  digitalWrite(m.dir_pin, d);
}

void reset(struct motor &m) {
  ch_dir(m, UP);
  power(m, OFF);
  m.state = STOP;
  Serial.printf("motor with power_pin %u is reset\n", m.power_pin);
}

void move(struct motor &m, enum dir d) {
  ch_dir(m, d);
  power(m, ON);
  m.state = d == DOWN ? MDOWN : MUP;
  m.lastMove = millis();
  Serial.printf("motor with power_pin %u is moving %s\n", m.power_pin, (d == DOWN) ? "down" : "up");
}

bool is_pressed(byte pin) { // A0: analog, D8: pull-down, rest: pull-up
  if (pin == A0) {
    return analogRead(pin) > 1000;
  } else if (pin == D8) {
    return digitalRead(pin) == HIGH;
  } else {
    return digitalRead(pin) == LOW; // INPUT_PULLUP
  }
}

bool readMove(struct motor &m) {
  if (is_pressed(m.down_pin)) {
    Serial.println("down pressed");
    if (m.state == MUP)
       reset(m);
     else
       move(m, DOWN);
    return true;
  } else if (is_pressed(m.up_pin)) {
    Serial.println("up pressed");
    if (m.state == MDOWN)
       reset(m);
     else
       move(m, UP);
    return true;
  } else if (m.state != STOP && millis() - m.lastMove > T_OFF * 1000) {
    reset(m);
  }
  return false;
}
