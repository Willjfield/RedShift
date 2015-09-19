/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

 This example code is in the public domain.
 */
int sensorValue1, sensorValue2;
int diff, oldDiff;
float zShift;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  sensorValue1 = 0;
  sensorValue2 = 0;
  diff = 0;
  oldDiff = 0;
  zShift=0;
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);
  diff = sensorValue1-sensorValue2;
  zShift = (zShift+diff-oldDiff)/2;
  // print out the value you read:
  Serial.println(zShift);
  oldDiff = diff;
  delay(1);        // delay in between reads for stability
}
