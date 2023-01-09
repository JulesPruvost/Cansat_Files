/*
    The name is Cansat Aether Files and it makes our cansat have a connection between us on the ground and the cansat that will be going in the air. 
    Copyright (C) 2023  Jules Pruvost

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Wire.h>
#include <Adafruit_LIS3MDL.h> // 0x1C
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM6DSOX.h>

/*
#define kw 19  //SCL
#define LIS3MDL_MISO 12
#define LIS3MDL_MOSI 18  //SDA
#define LIS3MDL_INT 37
#define MAGNEETPIN 33
*/

// BMP388
//SCK -> SCL pin for I2C
//SDI -> SDA pin for I2C

// LSM6DSOX + LIS3MDL
// A4 => SDA  
// A5 => SCL 
#define SDA_PIN A4
#define SCL_PIN A5

Adafruit_LIS3MDL lis3mdl;
Adafruit_LSM6DSOX lsm6dsox;

void setup(void) {
  Serial.begin(9600);

  while (!Serial) delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  // LSM6DSOX + LIS3MDL
  Wire.setSCL(A4);
  Wire.setSDA(A5);
 
  //
  // LSM6DSOX SETUP
  //
  if(!lsm6dsox.begin_I2C()) {
    Serial.println("Failed to find LSM6DSOX chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("LSM6DSOX Found!");

    // sox.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );
  Serial.print("Gyro range set to: ");
  switch (lsm6dsox.getGyroRange()) {
  case LSM6DS_GYRO_RANGE_125_DPS:
    Serial.println("125 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_250_DPS:
    Serial.println("250 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_500_DPS:
    Serial.println("500 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_1000_DPS:
    Serial.println("1000 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_2000_DPS:
    Serial.println("2000 degrees/s");
    break;
  case ISM330DHCX_GYRO_RANGE_4000_DPS:
    break; // unsupported range for the DSOX
  }

  // sox.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Gyro data rate set to: ");
  switch (lsm6dsox.getGyroDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }

  /*if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }*/
  // Try to initialize!
¨
  //
  // lis3mdl SETUP
  //
  if (!lis3mdl.begin_I2C()) {  // hardware I2C mode, can pass in address & alt Wire
                               //if (! lis3mdl.begin_SPI(LIS3MDL_CS)) {  // hardware SPI mode
                               //if (! lis3mdl.begin_SPI(LIS3MDL_CS, LIS3MDL_CLK, LIS3MDL_MISO, LIS3MDL_MOSI)) { // soft SPI
    Serial.println("Failed to find LIS3MDL chip");
    while (1) { delay(10); }
  }

  Serial.println("LIS3MDL Found!");

  //MAGNEET
  lis3mdl.setPerformanceMode(LIS3MDL_ULTRAHIGHMODE);
  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
  lis3mdl.setDataRate(LIS3MDL_DATARATE_1000_HZ);
  lis3mdl.setRange(LIS3MDL_RANGE_16_GAUSS);

  lis3mdl.setIntThreshold(500);
  lis3mdl.configInterrupt(false, false, true,  // enable z axis
                          true,                // polarity
                          false,               // don't latch
                          true);               // enabled!c

  // 
  // bmp280 SETUP
  // 

}  //end setup

void loop() {

}
