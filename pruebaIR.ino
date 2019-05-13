#include <IRremote.h>

/*Servo right_arm;
Servo left_arm;
Servo r_wh;
Servo l_wh;*/

IRrecv irrecv(11);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
  }
}
