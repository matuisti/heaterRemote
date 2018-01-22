
#include <SoftwareSerial.h>
SoftwareSerial SIM800(2, 3);
char inchar = 0;
int onPin = 8;

void setup()
{
  pinMode(onPin, OUTPUT);
  Serial.begin(9600);
  SIM800.begin(9600);
  delay(20000);
  SIM800.print("AT+CMGF=1\r");
  delay(1000);
  SIM800.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  Serial.println("Valmis!");
}

void reset()
{
  delay(100);
  SIM800.println("AT+CMGD=1,4\r");
  delay(1000);
  SIM800.print("AT+CNMI=2,2,0,0,0\r");
  delay(1000);
  Serial.println("reset");
}

void loop() {
  if (SIM800.available() >0) {
    inchar = SIM800.read();
    Serial.print(inchar);

    if (inchar == 'o')
    {
      delay(10);

      inchar = SIM800.read();
      if (inchar == 'n')
      {
        delay(1000);
        SIM800.println("AT+CMGS=\"+358409629998\"\r");
        delay(1000);
        SIM800.print("Rellun lammitys paalla!");
        delay(100);
        SIM800.print((char)26);
        delay(1000);
        On();
        reset();

      }

    }

  } 

}

void On()
{
  Serial.println("ON");
  digitalWrite(onPin, HIGH);
  delay(500);
  digitalWrite(onPin, LOW);
}



