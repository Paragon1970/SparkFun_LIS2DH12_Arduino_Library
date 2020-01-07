/* 
  Reading and controlling the very low power LIS2DH12
  Author: Nathan Seidle
  Created: Septempter 18th, 2019
  License: This code is Lemonadeware; do whatever you want with this code.
  If you see me (or any other SparkFun employee) at the
  local, and you've found our code helpful, please buy us a round!
  
  This example demonstrates how to read XYZ from the LIS2DH12.

  Feel like supporting open source hardware?
  Buy a board from SparkFun!
  Edge: https://www.sparkfun.com/products/15170
  Edge 2: https://www.sparkfun.com/products/15420
  Qwiic LIS2DH12 Breakout: https://www.sparkfun.com/products/15760

  Hardware Connections:
  Plug a Qwiic cable into the Qwiic Accelerometer RedBoard Qwiic or BlackBoard
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic Breadboard Jumper (https://www.sparkfun.com/products/14425)
  Open the serial monitor at 115200 baud to see the output
*/

#include <Wire.h>

#include "SparkFun_LIS2DH12.h" //Click here to get the library: http://librarymanager/All#SparkFun_LIS2DH12

SPARKFUN_LIS2DH12 accel; //Create instance

#define ACCEL_ADDRESS 0x19 //Default address on the LIS2DH12 breakout board, Edge, and Edge2
//#define ACCEL_ADDRESS 0x18 //Address if the address jumper is closed on the breakout board

void setup()
{
  Serial.begin(115200);
  Serial.println("SparkFun Accel Example");

  Wire.begin(); //Accel is on IOM3 and defined in the variant file as Wire1.

  //By default the SparkFun library uses Wire. We need to begin
  //with Wire1 on the Edge/Edge2.
  if (accel.begin(ACCEL_ADDRESS, Wire) == false)
  {
    Serial.println("Accelerometer not detected. Are you sure you did a Wire1.begin()? Freezing...");
    while (1);
  }

  accel.setDataRate(LIS2DH12_ODR_100Hz); //1 to 5.376kHz
  int currentRate = accel.getDataRate();
  Serial.print("Current rate (0 to 9): ");
  Serial.println(currentRate);

  accel.setScale(LIS2DH12_2g);
  //accel.setScale(LIS2DH12_16g);
  int currentScale = accel.getScale();
  Serial.print("Current scale (0 to 3): ");
  Serial.println(currentScale);

  accel.setMode(LIS2DH12_LP_8bit);
  //accel.setMode(LIS2DH12_NM_10bit);
  //accel.setMode(LIS2DH12_HR_12bit);
  int currentMode = accel.getMode();
  Serial.print("Current mode (0 to 2): ");
  Serial.println(currentMode);

  accel.enableTemperature();
  //accel.disableTemperature();

  accel.enableTapDetection();
  accel.setTapThreshold(40); //7-bit value. 4 is a little low. 7 is ok. 10 is a bit hard.

  while (accel.isTapped() == true) delay(10); //Clear any initial event that may be in the buffer
}

int tapCounter = 0;

void loop()
{
  if (accel.isTapped())
  {
    Serial.print("Tap: ");
    Serial.println(tapCounter++);

    while (accel.isTapped() == true) delay(10); //Clear any initial event that may be in the buffer
  }
  //Print accel values only if new data is available
  if (accel.available())
  {
    //      float accelX = accel.getX();
    //      float accelY = accel.getY();
    //      float accelZ = accel.getZ();
    //      float tempC = accel.getTemperature();
    //
    //      Serial.print("Acc [mg]: ");
    //      Serial.print(accelX, 1);
    //      Serial.print(" x, ");
    //      Serial.print(accelY, 1);
    //      Serial.print(" y, ");
    //      Serial.print(accelZ, 1);
    //      Serial.print(" z, ");
    //      Serial.print(tempC, 1);
    //      Serial.print("C");
    //      Serial.println();

    int rawX = accel.getRawX();
    int rawY = accel.getRawY();
    int rawZ = accel.getRawZ();

    Serial.print("Acc raw: ");
    Serial.print(rawX);
    Serial.print(" x, ");
    Serial.print(rawY);
    Serial.print(" y, ");
    Serial.print(rawZ);
    Serial.print(" z");
    Serial.println();
  }

}
