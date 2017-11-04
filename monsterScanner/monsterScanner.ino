
// Pin 13 has an LED connected on most Arduino boards:
// use this pin to give device status
// BEGIN STATUS LIGHT GLOBAL VARS...
int STATUSLIGHT = 13;
int STATBRIGHTNESS = 25;
int MAXBRIGHTNESS = 250;
int MINBRIGHTNESS = 25;
int STATDIRECTION = 1; // 1 is up, 0 is down
// END STATUS LIGHT GLOBAL VARS...


void setup()
{  // initialize the digital pin as an output.
  pinMode(STATUSLIGHT, OUTPUT);
}

void loop()
{
  pulseStatus();
  
  delay(20);
}

void pulseStatus()
{
  if (STATBRIGHTNESS < MINBRIGHTNESS)
  {
    STATDIRECTION = 1;
  }
  else if (STATBRIGHTNESS > MAXBRIGHTNESS)
  {
    STATDIRECTION = 0;
  }

  if (STATDIRECTION > 0)
  {
    STATBRIGHTNESS += 5;
  }
  else
  {
    STATBRIGHTNESS -= 5;
  }
  analogWrite(STATUSLIGHT, STATBRIGHTNESS);
}

