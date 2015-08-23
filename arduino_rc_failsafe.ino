int sIn = 10;
int sOut = 9;
unsigned long dur;
int mapped;

unsigned long previousMillis = 0;
unsigned long ledBlinkInterval = 100;

int ledIndicator = 13;
int ledIndState = LOW;
int RCstatus = 0;
/*
0 default
1 ok
2 out or range signal
*/


void setup()
{
  pinMode(sIn, INPUT);
  pinMode(sOut, OUTPUT);
  pinMode(ledIndicator, OUTPUT);
  //Serial.begin(115200);
}

void loop()
{
  dur = pulseIn(sIn, HIGH, 20000);
  
  if (dur > 2000)
  {
    RCstatus = 2;
    dur = 2000;
  }
  else if(dur < 1000)
  {
    RCstatus = 2;
    dur = 1000;
  }
  else
  {
    RCstatus = 1;
  }
  
  mapped = map(dur, 1000,2000,1,255);
  
  analogWrite(sOut, mapped);
  
  
  
  //update LED Status
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis > ledBlinkInterval)
  {
      previousMillis = currentMillis;
      
      //check status
      switch (RCstatus)
      {
        //ok
        case 1:
          digitalWrite(ledIndicator, HIGH);
          break;
        //out of range signal
        case 2:
          //blink the LED
          digitalWrite(ledIndicator, ledIndState);
          if (ledIndState == LOW)
          {
            ledIndState = HIGH;
          }
          else
          {
            ledIndState = LOW;
          }
          break;
        case 0:
        default:
          digitalWrite(ledIndState, LOW);
      }
  }
  
  
  
  delay(1);
}
