#include <SoftwareSerial.h>
#include <TinyGPS.h>
 
long lat,lon;// create variable for latitude and longitude object
double latitude,longitude;
int result = 0;

SoftwareSerial gpsSerial(2, 3); // create gps sensor connection
TinyGPS gps; // create gps object
 
void setup(){
  Serial.begin(9600); // connect serial
  gpsSerial.begin(9600); // connect gps sensor
  mySerial.begin(115200);   // Setting the baud rate of GSM Module 
  pinMode(13,INPUT);
}
 
void loop(){
  while(gpsSerial.available()){ // check for gps data
    result = digitalRead(13);
   if(gps.encode(gpsSerial.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    // display position
    latitude = double(lat);
    latitude = latitude / 1000000;
    longitude = double(lon);
    longitude = longitude / 1000000;
    Serial.print("Position: ");
    Serial.print("lat: ");Serial.print(latitude);Serial.print(" ");// print latitude
    Serial.print("lon: ");Serial.println(longitude); // print longitude
    
    
   }
   if(result==0 ) {
    SendMessage();
    delay(100);
    }
  }

 
}

  void SendMessage()
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+91xxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.print("Emergency at location : ");
  delay(100);
  Serial.println("https://maps.google.com/?t=k&q=");// The SMS text you want to send
  delay(100);
  Serial.print(latitude);
  Serial.print(",");
  Serial.println(longitude);
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
