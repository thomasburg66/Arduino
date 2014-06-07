int pin_out_magnet=6;
int pin_out_flash=7;


int delay_start=1000,delay_after_magnet=0,delay_after_flash=0,d;
int flash_duration=10;
int magnet_duration=50;



#define INLENGTH 20
char inString[INLENGTH+1];
int inCount;

#define INTERMINATOR 13

void setup()  
{  
  
  Serial.begin(9600); 
  Serial.println("TBs Relais Test V1.01"); 
  Serial.println(); 
   
  pinMode(pin_out_magnet,OUTPUT);
  pinMode(pin_out_flash,OUTPUT);
}  



void readInt(char *what, int old_value, int *p_new_value) {
  Serial.print("Enter "); 
  Serial.print(what); 
  Serial.print("old value is: "); 
  Serial.print(old_value);  
  
  // read string until EOF
  inCount=0;
  do {
    while (Serial.available()==0);
    inString[inCount]=Serial.read();
    if (inString[inCount]==INTERMINATOR) 
      break;
  } while (++inCount<INLENGTH);
  // if empty string, return old value
  if (inCount==0) {
    *p_new_value=old_value;
  } else {
    // convert string to number
    *p_new_value=atoi(inString);
  }
  Serial.println();
  
} // readInt

void my_delay(int ms) {
  Serial.print("waiting for ");
  Serial.print(ms);
  Serial.println();
  delay(ms);
} // my_delay
  
  
  
void loop()  
{ 
  
  // Action!
  Serial.println("here we go again...");

  // read values  
  readInt("delay_start",delay_start,&delay_start);
  readInt("delay_after_magnet",delay_after_magnet,&delay_after_magnet);
  readInt("delay_after_flash",delay_after_flash,&delay_after_flash);
  readInt("flash_duration",flash_duration,&flash_duration);
  readInt("magnet_duration",magnet_duration,&magnet_duration);
  
  // Display values
  Serial.print("--- Starting with delay_start=");
  Serial.print(delay_start);
  Serial.print(", delay_after_magnet=");
  Serial.print(delay_after_magnet);
  Serial.print(" delay_after_flash=");
  Serial.println(delay_after_flash);
  
  // start delay
  Serial.println("start delay...");
  my_delay(delay_start);
  
  // Start Relay 1
  Serial.println("firing magnet...");
  digitalWrite(pin_out_magnet,HIGH);
  my_delay(magnet_duration);  
  digitalWrite(pin_out_magnet,LOW);  
  d=delay_after_magnet-magnet_duration;
  if (d>0) my_delay(d);
  
  // Start Relay 2
  Serial.println("firing flash...");
  int i=0;
  for (i=0; i<1; i++) {
    digitalWrite(pin_out_flash,HIGH);
    my_delay(flash_duration);
    digitalWrite(pin_out_flash,LOW);  
    my_delay(flash_duration);
  }

  

  
}                            



