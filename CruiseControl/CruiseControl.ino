static bool cruiseFlag = false;
const int PWM_PIN = 3;
int pedalWriteValue_Locked;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(4, INPUT);
}

void loop() 
{
  //Low Pass  
  int lowPassRead = analogRead(A0);
  float lowPassWriteValue = lowPassRead * 0.249;
  float lowPassVoltage = lowPassRead * (5.0/1023.0);
  
  //Pedals
  int pedalReadValue = analogRead(A1);
  float pedalWriteValue = pedalReadValue * 0.249;
  float pedalVoltage = pedalReadValue * (5.0/1023.0);
  
  if(digitalRead(4) == HIGH)
  {
    Serial.println("Cruise Control Currently Active");
    if(cruiseFlag == false)
    {
      pedalWriteValue_Locked = pedalWriteValue;
      analogWrite(3, pedalWriteValue_Locked);
      cruiseFlag = true;
    }
    
    if(cruiseFlag == true && pedalWriteValue <= pedalWriteValue_Locked)
    {
      Serial.println("This is true!!!!!!!!!");
      pedalWriteValue = pedalWriteValue_Locked;
      analogWrite(3, pedalWriteValue);
    }
    
  }
  else
  {
    Serial.println("Cruise Control Off");
    analogWrite(3, pedalWriteValue);
    cruiseFlag = false;
  }
  lowPassVoltage = lowPassRead * (5.0/1023.0);
  Serial.println(lowPassVoltage);
  pedalVoltage = pedalReadValue * (5.0/1023.0);
  Serial.println(pedalVoltage);

}
