
// Pin 13 has an LED connected on most Arduino boards:
int STATUSLIGHT = 13;

int counter = 25;

int MAXBRIGHTNESS = 250;
int MINBRIGHTNESS = 25;
int DIRECTION = 1; // 1 is up, 0 is down

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
  if (counter < MINBRIGHTNESS)
  {
    DIRECTION = 1;
  }
  else if (counter > MAXBRIGHTNESS)
  {
    DIRECTION = 0;
  }

  if (DIRECTION > 0)
  {
    counter += 5;
  }
  else
  {
    counter -= 5;
  }
  
  analogWrite(STATUSLIGHT, counter);
}

