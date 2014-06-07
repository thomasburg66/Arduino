
#define KNOB1  0
#define KNOB2  1

#define BUTTON1  2
#define BUTTON2  3
#define BUTTON3  4



#define STAT1  7
#define STAT2  6



void setup();
void loop ();
void noteOn(byte cmd, byte data1, byte data2);
void blink();
void playNote(byte note, byte velocity);
char button(char button_num);
byte incomingByte;
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

midi
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


void noteOn(byte cmd, byte data1, byte data2) {
  Serial.print(cmd);
  Serial.print(data1);
  Serial.println(data2);
}

void blink(){
  digitalWrite(STAT1, HIGH);
  delay(100);
  digitalWrite(STAT1, LOW);
  delay(100);
}


void playNote(byte note, byte velocity)
{
  int value=LOW;
  if (velocity >10){ 
    value=HIGH; 
  }
  else{ 
    value=LOW; 
  }

  //since we don't want to "play" all notes we wait for a note between 36 & 44
  if(note>=36 && note<44)
  { 
    byte myPin=note-34; // to get a pinnumber between 2 and 9
    digitalWrite(myPin, value);
  }

}

char button(char button_num)
{
  return (!(digitalRead(button_num)));
}

void loop () {

  pot = analogRead(1);
  note = pot/8;  // convert value to value 0-127
  if(button(BUTTON1) || button(BUTTON2) || button(BUTTON3))
  {
    
    noteOn(0x95,0x3C,0x45);
    digitalWrite(STAT2,LOW);
    while(button(BUTTON1) || button(BUTTON2) || button(BUTTON3));
  }

}

