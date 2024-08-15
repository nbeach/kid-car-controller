#include "PS2Shield.h"
#include "HardwareSerial.h"

void PS2Shield::begin(uint32_t baudrate) {
  Serial2.begin(baudrate);
  while (!Serial2)
    ;
}

void PS2Shield::write(uint8_t data) {
  while (Serial2.available() > 0) {
    Serial2.read();
  }
  Serial2.write(data);
  Serial2.flush();
}

uint8_t PS2Shield::read(void) {
  uint8_t rec_data;
  long waitcount = 0;

  while (true) {
    if (Serial2.available() > 0) {
      rec_data = Serial2.read();
      return (rec_data);
    }
    waitcount++;
    if (waitcount > 50000) {
      return (128);
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

  nbyte = Serial2.readBytes(ps_data, 6);

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