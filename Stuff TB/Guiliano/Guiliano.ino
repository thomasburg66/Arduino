
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
  //Serial.begin(38400); 
  //Serial.println("MIDI Board");  
}

//loop: wait for serial data, and interpret the message
void loop () {

  int pot = analogRead(1);
  byte note = pot/8;  // convert value to value 0-127
  if(button(BUTTON1) || button(BUTTON2) || button(BUTTON3))
  {
    
    channelAftertouch(15,note);
    digitalWrite(STAT2,LOW);
    while(button(BUTTON1) || button(BUTTON2) || button(BUTTON3));
  }
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

