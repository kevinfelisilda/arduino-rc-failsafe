int sIn = 10;
int sOut = 9;
unsigned long dur;
unsigned long failsafeVal = 1900;
int mapped;

//amount of time to regain rc signal from the time its lost
int debounce = 3; //seconds

unsigned long lastDisconnection = 0;

unsigned long previousMillis = 0;
unsigned long ledBlinkInterval = 100;

int ledIndicator = 13;
int ledIndState = LOW;
int RCstatus = 0;
int prevStatus = 0;
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
  unsigned long currentMillis = millis();
  
  dur = pulseIn(sIn, HIGH, 20000);
  
  //falls to acceptable range
  if (dur >= 1000 && dur <= 2000)
  {
    //check if it regains signal
    if (prevStatus == 2 && (currentMillis - lastDisconnection) < (debounce * 1000))
    {
      dur = failsafeVal;
      RCstatus = 2;
    }
    else
    {
      RCstatus = 1;
    }
  }
  else
  {
    RCstatus = 2;
    //dur = 1000;
    dur = failsafeVal;
    lastDisconnection = currentMillis;
  }
  
  prevStatus = RCstatus;
  
  mapped = map(dur, 1000,2000,125,254);
  
  analogWrite(sOut, mapped);
  
  
  
  //update LED Status
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
