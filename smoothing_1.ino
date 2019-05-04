const int numReadings = 50;
const int ledPin = 13;
const int sensorPin = 0;
const int numDelay = 25;

float readings[numReadings];      // the readings from the analog input
int index = 0;                    // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the rounded average
float average_accurate = 0;       // the average

float accuracy = 4.0;             // rounding the average: more accuracy = more precision

float diff = 0;                   // temporary variable

int x = 0;
int row = 0;


int inputPin = A0;

void setup(){
  
  int x = 0;
int row = 0;
  
  // initialize serial communication with computer:
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,x");
  
  // initialize all the readings to 0: 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;          
}

void loop() {
  // subtract the last reading:
  total= total - readings[index];         
  // read from the sensor:  
  readings[index] = analogRead(inputPin); 
  // add the reading to the total:
  total= total + readings[index];  
  
  int index_temp = index+1;
  if(index_temp == numReadings) {
    index_temp = 0;
  }
  
  diff = readings[index] - readings[index_temp];
  average_accurate = average_accurate + diff/numReadings;  
  average = int(accuracy*average_accurate)/accuracy;
  index = index + 1;

  // advance to the next position in the array:  
  // index = index + 1;                    

  // if we're at the end of the array...
  if (index >= numReadings)              
    // ...wrap around to the beginning: 
    index = 0;                           

  // calculate the average:
  // average = total / numReadings;
  
  if (average < 0)
    average = average * (-1);

digitalWrite(11, HIGH);

  int rate = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH);
  delay(numDelay);
  digitalWrite(ledPin, LOW);
  delay(numDelay);

  Serial.print("DATA,TIME,"); 
  Serial.println (average);
  
  row++;
  x++;
          
}

