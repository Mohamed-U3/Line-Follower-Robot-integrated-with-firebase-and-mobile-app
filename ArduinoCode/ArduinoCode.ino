#include <SoftwareSerial.h>

SoftwareSerial STM(13, 15,false); //Define hardware connections SoftwareSerial(rxPin, txPin, inverse_logic, buffer size);

String FirebaseVariable = "Two";
String storedData = "";
float duration = 2.05;
String Timer = "2.05";//String(duration);

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  STM.begin(9600);
  Serial.println("\nSoftware serial test started");
}

void loop()
{
  if (Serial.available() > 0)
  {
    storedData = "";
    while (Serial.available() > 0)
    {
      char inChar = Serial.read();
      storedData += inChar;
    }
  }
  while (STM.available() > 0)
  { //wait for data at software serial
    Serial.write(STM.read()); //Send data recived from software serial to hardware serial
    delay(10);
  }
  delay(100);
  if (storedData == "T")
  {
    STM.write("2");
    STM.write("- Duration: ");
    STM.print(Timer);
  }
  else if (storedData == "F")
  {
    STM.write("4");
    STM.write("- Duration: ");
    STM.print(Timer);
  }
  else
  storedData = "";
//    STM.write("E");
}
