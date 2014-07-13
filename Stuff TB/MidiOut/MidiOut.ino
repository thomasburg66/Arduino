
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

void setup();
void loop ();
void noteOn(byte cmd, byte note, byte velocity);
char button(char button_num);

byte note;
byte velocity;
int pot;

byte byte1;
byte byte2;
byte byte3;


int action=2; //0 =note off ; 1=note on ; 2= nada

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

  pot = analogRead(1);
  note = pot/8;  // convert value to value 0-127
  if(button(BUTTON1) || button(BUTTON2) || button(BUTTON3))
  {
    
    noteOn(0x95,note,0x45);
    digitalWrite(STAT2,LOW);
    while(button(BUTTON1) || button(BUTTON2) || button(BUTTON3));
  }
}

void noteOn(byte cmd, byte note, byte velocity) {
   Serial.write(cmd);
   Serial.write(note);
   Serial.write(velocity);
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

