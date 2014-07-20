
/*
   Documentation on Midi (German): http://de.wikipedia.org/wiki/Musical_Instrument_Digital_Interface#Nachrichtentypen
   
   based on sample program for Arduino Midi Shield : https://www.sparkfun.com/products/9595


*/

#define KNOB1  0
#define KNOB2  1

#define BUTTON1  2
#define BUTTON2  3
#define BUTTON3  4


#define STAT1  7
#define STAT2  6

//setup: declaring iputs and outputs and begin serial
void setup() {

  pinMode(STAT1,OUTPUT);   // declare the LED's pin as output
  pinMode(STAT2,OUTPUT);

  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);


  digitalWrite(BUTTON1,HIGH);
  digitalWrite(BUTTON2,HIGH);
  digitalWrite(BUTTON3,HIGH);


  for(int i = 0;i < 10;i++)
  {
    digitalWrite(STAT1,HIGH);  
    digitalWrite(STAT2,LOW);
    delay(30);
    digitalWrite(STAT1,LOW);  
    digitalWrite(STAT2,HIGH);
    delay(30);
  }
  digitalWrite(STAT1,HIGH);   
  digitalWrite(STAT2,HIGH);
 
 //start serial with midi baudrate 31250 or 38400 for debugging
  Serial.begin(31250);     
//  Serial.begin(38400); 
  //Serial.println("MIDI Board");  
}

// scale from voltage 1 .. 4 V to aftertouch of 0 .. 127
// Arduino will map input voltages between 0 and 5 volts into integer values between 0 and 1023.
/*

- let's call the voltage U
- let's call the reading or the analog port a
- let's call the aftertouchvalue v

Advanced Math yields:

U=a * 5 / 1023

v= (U - 1) * 127 / 3

v= (5 * a / 1023 - 1) * 127 /3

*/
byte voltageToAftertouchvalue(int analog_read) {
  float a,v;
  a=analog_read;
 
  v=(5.0 * a / 1023.0 - 1.0) * 127.0 / 3.0;

  if (v<0) return 0;
  if (v>127) return 127;
  byte result=v;
  return v;  
}

int debug=0;

int aftertouch_old=1000;

//loop: wait for serial data, and interpret the message
void loop () {

  // need to connect the output of the organ pedal to Analog 4
  // for testing, use Analog 1 which is the potentiometer
  int pot_pedal = analogRead(0);
  int pot_knob = analogRead(1);

  int aftertouch_sensitivity=pot_knob/8;
  
  // we read a value from 0 ... 127 representing 0 ... 5 V
  // however, we have measured the minimum value to be 1 V and the maximum value to be 4 V
  // therefore we scale this
  byte aftertouch=pot_pedal / 8; // voltageToAftertouchvalue(pot);

  if (debug) {
    Serial.print("pot_pedal ");
    Serial.println(pot_pedal);
  }
  
 
  if ( abs(aftertouch - aftertouch_old) >= aftertouch_sensitivity) {
    if (debug) {
      Serial.print("new aftertouch ");
      Serial.println(aftertouch);
    } else {
      channelAftertouch(15,aftertouch);
    }
    aftertouch_old=aftertouch;
  } 
  
  //  delay(100);
}

/*

Note On	Beginnt das Spielen einer Note kk. 
Zusätzlich wird die Anschlagsdynamik v (engl. Velocity) angegeben, die der Druckstärke auf die
Taste in 127 Schritten von 1 (sehr schwach) bis 127 (sehr stark) entspricht. 
Der Wert 0 ist als Note-Off-Befehl definiert.

Statusbyte: 9n	- n=0 --> Note off // otherwise n=channerl
Byte 1: k = note
Byte 2:	v = velocity	

*/
void noteOn(byte cmd, byte note, byte velocity) {
   Serial.write(cmd);
   Serial.write(note);
   Serial.write(velocity);
}

/*
Monophonic bzw. Channel Aftertouch

Beschreibt das Ändern des Tastendrucks vv während die Tasten bereits gedrückt sind, 
für alle Tasten gemeinsam.
Genau wie bei Polyphonic Aftertouch sind diese Daten neutral.

Statusbyte: Dn	 - n = Channel
Byte 1: vv			


*/

void channelAftertouch(byte channel, byte value) {
   byte cmd=0xD0 + channel - 1;
   Serial.write(cmd);
   Serial.write(value);
}

char button(char button_num)
{
  return (!(digitalRead(button_num)));
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

