/***************************************************************************

  Designed specifically to work with the Adafruit HMC5883 Breakout
  http://www.adafruit.com/products/1746

  *** You will also need to install the Adafruit_Sensor library! ***

 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");

  /* Initialise the sensor */
  if (!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }

  /* Display some basic information on this sensor */
  displaySensorDetails();
}

void loop(void)
{
  /* Get a new sensor event */
  float xSpinRate [10], ySpinRate[10],zSpinRate[10];
  float xSpin, ySpin, zSpin,tempx, tempy, tempz;
  
  for(int i=0;i<10;i++){ 
  sensors_event_t event;
  mag.getEvent(&event);
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) 
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  "); Serial.println("uT");*/
  tempx = event.magnetic.x;
  xSpinRate[i] = tempx;

  tempy = event.magnetic.y;
  ySpinRate[i] = tempy;

  tempz = event.magnetic.z;
  zSpinRate[i] = tempz;
  delay(100);
  }
  
  /*This was a test to ensure array was filling correctly 
   * Serial.print("This is the array ");
  for(int j=0;j<10;j++){
  Serial.print(xSpinRate[j]); Serial.print(",");
  }
  Serial.print("\n");*/
  
  //Spin Rate Calculation

  xSpin = ((xSpinRate[9] - xSpinRate[0]) / 1);
  ySpin = ((ySpinRate[9] - ySpinRate[0]) / 1);
  zSpin = ((zSpinRate[9] - zSpinRate[0]) / 1);
  Serial.print("X_SpinRate: "); Serial.print(xSpin); Serial.print(" [degrees/sec]"); Serial.println(" ");
  Serial.print("Y_SpinRate: "); Serial.print(ySpin); Serial.print(" [degrees/sec]"); Serial.println(" ");
  Serial.print("Z_SpinRate: "); Serial.print(zSpin); Serial.print(" [degrees/sec]"); Serial.println(" ");
  delay(500);
}
