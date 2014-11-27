
/* Attiny 13a Breathing */

#include <EEPROM.h>
#include <avr/sleep.h>
#include <util/delay.h>

/** pwm pin, digital pin 0
 *  this is hardware IC pin 5
 */
const static int led = 0;
const static int btn = 5;

/** number of steps for  increasing breath speed */
const static int p = 2;

/** initial breath constant */
const static int r = 5;
  
byte programState = 1;
byte lastProgramState = 0;
byte buttonState = 0;
  
/** the setup routine runs once when you press reset: */
void setup() {                
  pinMode(led, OUTPUT);
  analogWrite(led, 0);
  pinMode(btn, INPUT);
  initState();
  toggleState();
  saveState();
}

void loop() {
  if(programState == 1) {
    runBreathing();
  }
  else if(programState == 0) {
    stopBreathing();
  }
  else {
    programState = 1;
    lastProgramState = 0;
    saveState();
  }
  
}

void runBreathing() {
  for(int j=1; j<p; j++) {
    breath(r, j);
  }
  for(int j=p; j>1; j--) {
    breath(r, j);
  }
}

void stopBreathing() {
  analogWrite(led, 0);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
  analogWrite(led, 5);
}

void breath(int r, int p) {
  int lowTime = 1000;
  int highTime = 1000;
  
  for(int i=0; i<255; i++) {
    analogWrite(led, i);
    delay((255-i)/(r*p) + 1);
  }
  while(highTime--) _delay_ms(1);
  for(int i=255; i>=0; i--) {
    analogWrite(led, i);
    delay((255-i)/(r*p) + 1);
  }
  
  while(lowTime--) _delay_ms(1);
}

void initState() {
  byte stateSaved = EEPROM.read(12);
  if(stateSaved == 17) {
    programState = EEPROM.read(10) - 10;
    lastProgramState = EEPROM.read(11) - 10;
  }
  else {
    saveState();
  }
}

void saveState() {
  EEPROM.write(12, 17);
  EEPROM.write(10, programState + 10);
  EEPROM.write(11, lastProgramState + 10);
}

void toggleState() {
  byte tmp = lastProgramState;
  lastProgramState = programState;
  programState = tmp;
}
