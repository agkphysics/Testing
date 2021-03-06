#include <Compass.h>
#include <Wire.h>
#include <MotorDriver.h>

Compass compass;
MotorDriver motors(0x20);

int _initialHeading;
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  delay(1000);
  _initialHeading = (int)(compass.correctedHeading());
  Serial.print("Initial Heading: ");
  Serial.println(_initialHeading);
}

void loop()
{
  delay(100);
  
  //*
  float rawHeading = compass.heading();
  Serial.print("rawHeading: ");
  Serial.println(rawHeading);
  
  float currentHeading = compass.correctedHeading();
  Serial.print("currentHeading: ");
  Serial.println(currentHeading);
  float degreesToRotate = degreesToNearest90();
  Serial.print("degreesToRotate: ");
  Serial.println(degreesToRotate);
  motors.rotate(degreesToRotate);
  motors.wait();
  delay(1000);
  Serial.print("Heading: ");
  Serial.println(currentHeading);
  Serial.println();
  //*/
}
	 
float degreesToNearest90()
{
    int currentHeading = (int)(compass.correctedHeading());
    
    int currentRelativeHeading = currentHeading - _initialHeading;
    if (currentRelativeHeading < 0) {
      currentRelativeHeading = currentRelativeHeading + 360;
    }
    Serial.print("CurrentRelativeHeading: ");
    Serial.println(currentRelativeHeading);
    int closest90 = ((currentRelativeHeading + 45)/90)*90;
    Serial.print("closest90: ");
    Serial.println(closest90);
    return (float)(closest90 - currentRelativeHeading);
}
