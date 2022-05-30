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
      analogWrite(PWM_PIN, pedalWriteValue_Locked);
      cruiseFlag = true;
    }
    else
    {
      analogWrite(PWM_PIN, pedalWriteValue_Locked);
      Serial.println(pedalWriteValue_Locked);
      //delay(500);
      //analogWrite(PWM_PIN, 0);
    }
  }
  else
  {
    Serial.println("Cruise Control Off");
    analogWrite(PWM_PIN, pedalWriteValue);
    cruiseFlag = false;
  }
}
