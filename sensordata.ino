#include <ArduinoJson.h>

#include <SoftwareSerial.h>
SoftwareSerial s(5,6);



const int FLEX_PIN = A0; // Pin connected to voltage divider output

// Measure the voltage at 5V and the actual resistance of your
// 10k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 13000.0; // Measured resistance of 10k resistor

// Upload the code, then try to adjust these values to more accurately calculate bend degree.

const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

//int xaxis;
//int yaxis;
//int zaxis;


void setup() 
{
  
  Serial.begin(9600);
  s.begin(9600);

  pinMode(FLEX_PIN, INPUT);
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  int angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
  Serial.println("Bend: " + String(angle) + " degrees");
 // Serial.println();

    // print the accelerometer sensor values:
  Serial.println("X-axis\tY-axis\tZ-axis");
  int xaxis=analogRead(xpin);
  Serial.print(xaxis);
  // print a tab between values:
  Serial.print("\t");
  int yaxis=analogRead(ypin);
  Serial.print(yaxis);
  // print a tab between values:
  Serial.print("\t");
  int zaxis=analogRead(zpin);
  Serial.print(zaxis);
  Serial.println();

  if(Serial.read()=='j');
  {
    DynamicJsonBuffer jBuffer;
    JsonObject& root = jBuffer.createObject();
    root["Angle"] = angle;
    root["Xaxis"] = xaxis;
    root["Yaxis"] = yaxis;
    root["Zaxis"] = zaxis;

    root.printTo(s);
  }
    
  delay(2000);
}
