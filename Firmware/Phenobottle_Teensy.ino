/* <Phenobottle Teensy Script. Controls "The Phenobottles" sensors>
     Copyright (C) <2020>  <Harvey Bates>

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.
     
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
     
     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <https://www.gnu.org/licenses/>
     
     For more information contact: harvey.bates@student.uts.edu.au or see
     https://github.com/HarveyBates/Open-JIP 
*/ 

// Analog Pins


//#define temperatureReadPin 33

// Optical density
#define odEmitPin   23
#define odDetectPin 22
#define odReadPin   20

// Fluorescence
#define fluorescenceReadPin A14
#define actinicPin 35
#define actinicPower 255

//RGB Control 
#define redPin 38
#define greenPin 37
#define bluePin 36

//Other
#define temperaturePower 20

// Fluorescence measuring settings


#define MICRO_READS 10000  // samples

#define MILI_DELAY  100    // us
#define MILI_LENGTH 1000   // ms
#define MILI_READS  MILI_LENGTH*1000/MILI_DELAY

// Setup arrays that hold fluorescence data
int microRead [MICRO_READS];
int milliRead [MILI_READS];

// Setup arrays that hold timestamps that correspond to fluorescence values
float microTime [MICRO_READS]; 
float milliTime [MILI_READS];
String command;

int microLength = MICRO_READS, milliLength = MILI_READS; // Change these to match the size of the above arrays

float refVoltage = 3.3; // Set the reference voltage (only applicable with Teensy 3.6)

void setup() {
  Serial.begin(500000); // Initalise serial communications at specific baud rate
  analogReadResolution(12); // Set the resolution of the microcontroller in bits
  set_reference_voltage(refVoltage); // Only applicable with a Teensy 3.6 (disable if using other microcontroller)
  
  pinMode(temperaturePower, OUTPUT);
  pinMode(odEmitPin, OUTPUT);
  pinMode(odDetectPin, OUTPUT);
  pinMode(actinicPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(odReadPin, INPUT);
  //pinMode(odReadPin, INPUT_PULLUP);
 
  digitalWrite(actinicPin, LOW);
  analogWriteFrequency(actinicPin, 20000);
  
  digitalWrite(odEmitPin, LOW);
  digitalWrite(odDetectPin, HIGH);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  // Testing
  RGB_light_ON(0,0,0);
  analogWrite(actinicPin, 0);
  
}

void RGB_light_ON(int red_intensity,int green_intensity, int blue_intensity){
  analogWrite(redPin, red_intensity);
  analogWrite(greenPin, green_intensity);
  analogWrite(bluePin, blue_intensity);
}

String getValue(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void measure_optical_density(){
  set_reference_voltage(refVoltage);
  digitalWrite(odEmitPin, HIGH); // Turn on emitting LED
  delay(500); // Slight delay to ensure emitting LED is stable
  int odMeasure = analogRead(odReadPin); // Read optical density
  Serial.println(odMeasure);
  digitalWrite(odEmitPin, LOW); // Turn off emitting LED
}

void set_reference_voltage(float voltage){
  // Sets and initalises the required reference voltage for measurments
  if(voltage == 3.3){
    analogReference(DEFAULT); // Set to 3.3 V
  }
  else if(voltage == 1.1){
    analogReference(DEFAULT); // Set to 1.1 V
  }
  else{
    analogReference(DEFAULT); // Set to default (3.3 V) if unknown value is found
  }
  analogRead(fluorescenceReadPin); // Initalise reference voltage
}

void measure_fluorescence() {
  set_reference_voltage(refVoltage); 
  
  analogWrite(actinicPin, actinicPower); // Turn on actinic LED

  long timer = micros(); // Start timer 

  // Read microsecond fluorescence values and corresponding timestamps
  for (unsigned int i = 0; i < MICRO_READS; i++) 
  {
    microRead[i] = analogRead(fluorescenceReadPin);
    microTime[i] = micros() - timer;
  }

  // Read millisecond fluorescence values and corresponding timestamps
  for (unsigned int i = 0; i < MILI_READS ; i++) 
  {
    milliRead[i] = analogRead(fluorescenceReadPin);
    milliTime[i] = micros() - timer;
    delayMicroseconds(MILI_DELAY);
  }

  analogWrite(actinicPin, 0);
  //digitalWrite(actinicPin, LOW); // Turn off actinic LED
  delay(1);

  // Convert micros() to milliseconds (ms) for microsecond values and convert bits to voltage
  for (unsigned int i = 0; i < sizeof(microRead) / sizeof(int); i++)
  {
   float milliReal = microTime[i]/1000; // Convert micros() to ms
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println(microRead[i]);
   delay(1);
  }

  // Convert micros() to milliseconds for millsecond values and convert bits to voltage
  for (unsigned int i = 0; i < sizeof(milliRead) / sizeof(int); i++) 
  {
   float milliReal = milliTime[i]/1000; // Convert micros() to ms
   
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println(milliRead[i]);
   delay(1);
  }
}

void measure_light(){
  analogWrite(actinicPin, actinicPower);
  delay(3000);
  digitalWrite(actinicPin, LOW);
  delay(20);
}

void loop(){
  if(Serial.available()){   
    command = Serial.readStringUntil('\n');
    if(command.equals("MeasureOpticalDensity") || command.equals("MOD")){
      measure_optical_density();
    }
    else if(command.equals("MeasureFluorescence") || command.equals("MF")){
      measure_fluorescence();
    }
    else if(command.equals("MeasureLight") || command.equals("ML")){
      measure_light();
    }
    else if(command.startsWith("RGB_light_ON")){
      String red_col = getValue(command, ';', 1);
      String red_freq = getValue(command, ';', 2); 
      String green_col = getValue(command, ';', 3);
      String green_freq = getValue(command, ';', 4); 
      String blue_col = getValue(command, ';', 5);
      String blue_freq = getValue(command, ';', 6);      
      RGB_light_ON(red_freq.toInt(), green_freq.toInt(), blue_freq.toInt());
    }
    else if(command.startsWith("RGB_light_OFF")){
      RGB_light_ON(0,0,0);
    }
    else{
      delay(100);
    }
  }
}
