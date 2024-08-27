

#include "PS2Shield.h"
#include "HardwareSerial.h"

PS2Shield::PS2Shield() {}

void PS2Shield::begin(uint32_t baudrate) {
  Serial1.begin(baudrate);
  while (!Serial1)
    ;

  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
}

void PS2Shield::write(uint8_t data) {
  while (Serial1.available() > 0) {
    Serial1.read();
  }
  Serial1.write(data);
  Serial1.flush(); // Wait for all data transmitted
}

uint8_t PS2Shield::read(void) {
  uint8_t rec_data;
  long waitcount = 0;

  while (true) {
    if (Serial1.available() > 0) {
      rec_data = Serial1.read();
      SERIAL_ERR = false;
      return (rec_data);
    }
    waitcount++;
    if (waitcount > 50000) {
      SERIAL_ERR = true;
      return (0xFF);
    }
  }
}

uint8_t PS2Shield::readButton(uint8_t key) {
  write(key);
  return read();
}

boolean PS2Shield::readAllButton() {
  uint8_t nbyte;

  write(PS2_BUTTON_JOYSTICK);

  nbyte = Serial1.readBytes(ps_data, 6);

  if (nbyte == 6)
    return (true);
  else
    return (false);
}

void PS2Shield::vibrate(uint8_t motor, uint8_t value) {
  uint8_t _motor;

  if (motor == 1)
    _motor = PS2_MOTOR_1;
  else
    _motor = PS2_MOTOR_2;

  write(_motor);
  write(value);
}

void PS2Shield::reset(uint8_t reset) {
  if (reset == 1)
    digitalWrite(A1, LOW);
  else
    digitalWrite(A1, HIGH);
}