int led=13;   
int pin_in=12;
int pin_out=7;
int value_in=0;
int value_out=LOW;
int value_out_old=LOW;
  
void setup()  
{  
  
  Serial.begin(9600); 
  Serial.println("TBs Taster"); 
  Serial.println(); 
   
  pinMode(led,OUTPUT);    
  pinMode(pin_in,INPUT);
  pinMode(pin_out,OUTPUT);
  digitalWrite(pin_in, HIGH);
  digitalWrite(pin_out,value_out);  
}  
  
void loop()  
{ 
  // read value on IN pin 
  // because of usage of no external pull-up this is inverse of value of
  // taster
  value_in=digitalRead(pin_in);

  // write it to internal LED  
  digitalWrite(led,value_in);
  
  // flip it 
  if (value_in==HIGH) value_out=LOW; else value_out=HIGH;
  
  // if value out changed, display it
  if (value_out != value_out_old) {
    Serial.print("New value of OUT is ..");
    Serial.println(value_out);
  }
  value_out_old=value_out;
  

  // Action!
  if (value_out==HIGH) {
    Serial.println("waiting");
    delay(2000);
    // write it to out PIN
    digitalWrite(pin_out,value_out);
    Serial.println("waiting");
    delay(2000);
    // write it to out PIN
    digitalWrite(pin_out,LOW);
    
  }
}                            



