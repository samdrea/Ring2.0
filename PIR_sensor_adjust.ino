
/*
 * For calibrating the HC-SR501 PIR sensor using an Arduino Uno Rev3 and LED
 */
 

int PIR_pin = 2;
int LED_pin = 13;
int PIR_state = 0;
unsigned long timer_start;

void setup()
{
  Serial.begin(9600);
  pinMode(PIR_pin, INPUT);
  pinMode(LED_pin, OUTPUT);
}


void loop()
{
  
  // print out the state of the button:
  PIR_state = digitalRead(PIR_pin);
  Serial.println("PIR_state: " + PIR_state);

   
  if (PIR_state == 1) {
    digitalWrite(LED_pin, HIGH);
  } else {
    digitalWrite(LED_pin, LOW);
  }

  
  delay(1000);
}
