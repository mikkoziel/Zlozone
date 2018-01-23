#include <dht1.h>
#include <SPI.h>
#include <SD.h>

File myFile;
dht1 DHT;
#define MOISTURE_PIN A2 
#define DHT11_PIN 9   
#define MOTOR_PIN 5 

int airHumidity;   
int airTemperature;  
int soilHumidity;   
int check=0;
int count=269;

void setup() {
   Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  cardInit();
}

void loop() {
 sensorRead();
 if(check==0){ 
  saveToFile();
  readFromFile();
 }

 if(check==0){
  pump();
  count++;
  delay(600000);
 }
 else if(check==1){
  delay(1000);
  digitalWrite(MOTOR_PIN, LOW);
  check=2;
  }
 else if(check==2){
  pump();
  delay(1000);
 }
}

void cardInit(){
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void sensorRead(){
  int chk;
  chk = DHT.read(DHT11_PIN);   
  switch (chk){
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }
  airHumidity=DHT.humidity;
  airTemperature=DHT.temperature;
  soilHumidity=(700-analogRead(MOISTURE_PIN))/6;
  
  Serial.print("\tairHumidity:");
  Serial.print(airHumidity);
  Serial.print("\tairTemperature:");
  Serial.print(airTemperature);
  Serial.print("\tsoilHumidity:");
  Serial.println(soilHumidity);
}

void saveToFile(){
    myFile = SD.open("text1.txt", FILE_WRITE);
    if (myFile) {
      Serial.print("Writing to test.txt...");
      myFile.print(airHumidity);
      myFile.print(",");
      myFile.print(airTemperature);
      myFile.print(",");
      myFile.print(soilHumidity);
      myFile.print(",");
      myFile.println(count);
      myFile.close();
      Serial.println("done.");
     } else {
    // if the file didn't open, print an error:
       Serial.println("error opening test.txt");
    }
}

void readFromFile(){
   myFile = SD.open("text1.txt");
  if (myFile) {
    Serial.println("text1.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }  
}

void pump(){
  if(airHumidity<=50){
    if(airTemperature<=30){
       if(soilHumidity<=70){
        digitalWrite(MOTOR_PIN, HIGH);   
        check=1;
       }                     
       else if(soilHumidity>=64){
        digitalWrite(MOTOR_PIN, LOW);
        check=0;
       }
    }
    else{
      if(soilHumidity<=75){
        digitalWrite(MOTOR_PIN, HIGH);   
        check=1;   
       }                     
       else if(soilHumidity>=80){
        digitalWrite(MOTOR_PIN, LOW);
        check=0;
       }
    }
  }
  else if(airHumidity<=100){
    if(airTemperature<=30){
       if(soilHumidity<=60){
        digitalWrite(MOTOR_PIN, HIGH);      
        check=1;
       }                     
       else if(soilHumidity>=75){
        digitalWrite(MOTOR_PIN, LOW);
        check=0;
       }
    }
    else{
      if(soilHumidity<=60){
        digitalWrite(MOTOR_PIN, HIGH);      
        check=1;
       }                     
       else if(soilHumidity<=70){
        digitalWrite(MOTOR_PIN, LOW);
        check=0;
       }
    }
  }   

}

