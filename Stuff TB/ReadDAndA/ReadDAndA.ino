int   g_last_val_digital[10];
float g_last_val_analog[10];

void TB_SetAsInput(int pin) {
  pinMode(pin,INPUT);
  digitalWrite(pin,HIGH);
}

void TB_ReadPin(int pin, int *p_newval, int *p_is_newval) {
  // read value
  *p_newval=1-digitalRead(pin); // need to inverse because of no use of external pull-up
  
  // set "this is not a new value" as default
  *p_is_newval=0;
  
  // check for changed value, if so return in p_is_newval
  if (*p_newval!=g_last_val_digital[pin]) {
    g_last_val_digital[pin]=*p_newval;
    *p_is_newval=1;
  } 
} // TB_ReadPin

void TB_ReadAndDisplayIfChangedDigital(int pin) {
  int val,isnew;

  TB_ReadPin(pin,&val,&isnew);
  
  if (isnew) 
  {
    Serial.print("New digital value of D");
    Serial.print(pin);
    Serial.print(" is ");
    Serial.println(val);
  }
}  // TB_ReadAndDisplayIfChangedDigital

float TB_ReadAnalogVoltage(int pin) {
  if (pin!=1) return -99.99;
  int sensorValue = analogRead(A1);
  // scale from 0..1023 digital to 0..5.0 float
  float voltage= sensorValue * (5.0 / 1023.0);
  
  // round to three points after comma
  int vround,round_factor_int;
  float round_factor_float;
  round_factor_int=10;
  round_factor_float=round_factor_int;
  vround=voltage * round_factor_int;         // 1.23456 --> 1234
  voltage=vround;                            //         --> 1234
  voltage=voltage / round_factor_float;      // 1234    --> 1.234
  
  //
  return voltage;
}

void TB_ReadAndDisplayIfChangedAnalog(int pin) {
  float val;

  val=TB_ReadAnalogVoltage(pin);
  
  if (val!=g_last_val_analog[pin]) 
  {
    g_last_val_analog[pin]=val;
    Serial.print("New analog value of A");
    Serial.print(pin);
    Serial.print(" is ");
    Serial.println(val);
  }
} // TB_ReadAndDisplayIfChangedAnalog



void setup()  
{  
  Serial.begin(9600); 
  Serial.println("TBs Test for reading Arduino vals"); 
  Serial.println(); 

  // we'll read digital 2,3,4 - set as input  
  TB_SetAsInput(1); 
  TB_SetAsInput(2);
  TB_SetAsInput(3);
  TB_SetAsInput(4);
} // setup  

void loop() { 
    TB_ReadAndDisplayIfChangedAnalog(1);
    TB_ReadAndDisplayIfChangedDigital(2);
    TB_ReadAndDisplayIfChangedDigital(3);
    TB_ReadAndDisplayIfChangedDigital(4);
} // loop



