//New file, everything fixed
#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"
#include <Arduino.h>
#include <Adafruit_GPS.h>
//asynchronous dht11 
#include "DHT_Async.h"
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define DHT_SENSOR_TYPE DHT_TYPE_11
static const int DHT_SENSOR_PIN = 4;
DHT_Async dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
//#define Warning_led 20
//#define Hazard_led 21
float temperature;
float humidity;

//heart rate sensor 
PulseOximeter pox;
float beat;
float spo2;


//gps files
#define GPSSerial Serial2
Adafruit_GPS GPS(&GPSSerial);
#define GPSECHO false


#define BAUDRATE 115200
#define REPORTING_PERIOD_MS 15000 //report to thingspeak every 20s
#define REPORTING_PERIOD_MS_THINGSPEAK 1000  // report to ThingSpeak every 20s

// Variables to store the duration and distance for ultrasonic sensors
long duration;
int distance; //for ultrasonic q

//variables to store dht11 readings
float temp;
float humi;

//variables for adding gps longitude and latitude to thingspeak
int lati;
int longi;

//for looping the main every 2 seconds
unsigned long previousMillis = 0; //execute the loop in void main only if the current time is - the last time readings were taken is greater than 2 seconds
const long interval = 1000; // Interval in milliseconds
uint32_t timer = millis();

//ssis and password for connecting esp32 to a network
const char* hs_ssid = "Seansiphone"; //hot spot phone name  
const char* hs_password = "gabtoocool"; //hot spot phone password
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
WebServer server(80);


//needed for thingspeak
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
uint32_t tsLastReport = 0; //4 byte unsigned int to time thingspeak 20s
uint32_t tsLastReportThingSpeak = 0;  //4 byte unsigned int to to time ThingSpeak 20s

// Define the pins for the ultrasonic sensor
const int trigPin = 5;
const int echoPin = 18; //for ultrasonic 1, labeled with blue on board


void handleRoot() {

  String message = homePagePart1 + temperature + homePagePart2 + humidity + homePagePart3 + beat + homePagePart4 + distance + homePagePart5 + spo2 + homePagePart6 + lati + homePagePart7 + longi + homePagePart8 + checkDistance() + homePagePart9 + checkTemperature() + homePagePart10 + checkBPM() + homePagePart11 + lati + homePagePart12 + longi + homePagePart13;


  server.send(200, "text/html", message);
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


void setup(void) {
  Serial.begin(115200);

  delay(1000);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  WiFi.begin(hs_ssid, hs_password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(hs_ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
 
  server.on("/", handleRoot);
  server.on("/inline", []() {
  server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
 
  server.begin();
  Serial.println("HTTP server started");

//configuring the different pins on the components as inputs or outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  // GPS
  Serial.println("Adafruit GPS library basic parsing test!");
  GPS.begin(9600);    
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GPSSerial.println(PMTK_Q_RELEASE);


  //heart rate sensor inititation
  // Register a callback for the beat detection
   Serial.print("Initializing pulse oximeter..");

  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;)
      ;
  } else {
    Serial.println("SUCCESS");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);

}
 
/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment(float* temperature, float* humidity) {
  static unsigned long measurement_timestamp = millis();

  /* Measure once every two seconds. */
  if (millis() - measurement_timestamp > 2000ul) {
    if (dht_sensor.measure(temperature, humidity)) {
      measurement_timestamp = millis();
      return (true);
    }
  }

  return (false);
}



void loop(void) {
  unsigned long currentMillis = millis();
  
  // Make sure to call update as fast as possible
  server.handleClient();
  pox.update();

  
if (millis() - tsLastReportThingSpeak > REPORTING_PERIOD_MS_THINGSPEAK ) {
  beat = pox.getHeartRate();
  spo2 = pox.getSpO2();


    tsLastReportThingSpeak = millis();  //update the time stamp
}

  if (currentMillis - previousMillis >= interval) {
    // Save the last time we read the sensors
    previousMillis = currentMillis;

    // Control buzzer and LED
  }


   // read data from the GPS in the 'main loop'
  char c = GPS.read();
  
  if (GPSECHO)
    if (c) Serial.print(c);
  if (GPS.newNMEAreceived()) {
   
    if (!GPS.parse(GPS.lastNMEA()))
      return; 
  }
  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
  
    // Measure distance for sensor 1
    ultraSonic(trigPin, echoPin, duration, distance);
    // Print the distance to the Serial Monitor
    Serial.print("\nDistance: ");
    Serial.print(distance);
    Serial.print(" cm  /  ");
    Serial.print("\nTemp:");
    Serial.print(temperature, 1);
    Serial.print("  Humi:");
    Serial.print(humidity, 1);
    Serial.println("%");
    checkDistance();
    checkTemperature();
    checkBPM();
  



    timer = millis(); // reset the timer
    Serial.print("\nTime: ");
    if (GPS.hour < 10) { Serial.print('0'); }
    Serial.print(GPS.hour, DEC); Serial.print(':');
    if (GPS.minute < 10) { Serial.print('0'); }
    Serial.print(GPS.minute, DEC); Serial.print(':');
    if (GPS.seconds < 10) { Serial.print('0'); }
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    if (GPS.milliseconds < 10) {
      Serial.print("00");
    } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
      Serial.print("0");
    }
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude/100, 2); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(-GPS.longitude/100, 2); Serial.println(GPS.lon);
      //Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      //Serial.print("Angle: "); Serial.println(GPS.angle);
     // Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);

      //thingspeak values for longitude and latitude
      lati = GPS.latitude/100;
      longi = -GPS.longitude/100;

    }
  }  


    if (measure_environment(&temperature, &humidity)) {
    Serial.print("\nTemp:");
    Serial.print(temperature, 1);
    Serial.print("  Humi:");
    Serial.print(humidity, 1);
    Serial.println("%");
  }

    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  ThingSpeak.setField(1,humidity);
  ThingSpeak.setField(2,temperature);
  ThingSpeak.setField(3,beat);
  ThingSpeak.setField(4,spo2);
  ThingSpeak.setField(5,distance);
  ThingSpeak.setField(6,longi);
  ThingSpeak.setField(7,lati);


//calling funcion to update thingspeak every 20 seconds
  updateTS();

}


//Functions 

//function to update thingspeak
void updateTS(){
     if (millis () - tsLastReport > REPORTING_PERIOD_MS)
 {
  if (humidity>=75){
    Serial.println("\nRoads may be slippery!!\n Proceed with caution.");
  }
  // pieces of information in a channel.  Here, we write to field all the fields.
 int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);//this ,ine is the problem with max30100
       if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;)
      ;
  } else {
    Serial.println("SUCCESS");
  }
 pox.setOnBeatDetectedCallback(onBeatDetected);
pox.update();
  tsLastReport = millis();
  }
}

// Callback (registered below) fired when a pulse is detected
void onBeatDetected() {
  Serial.println("\nBeat!");
    Serial.print(beat);
  Serial.print("bpm / SpO2:");
  Serial.print(pox.getSpO2());
  Serial.println("%");
}



void ultraSonic(int trig, int echo, long &duration, int &distance) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.0343 / 2;
}

String checkDistance(){
  if (distance < 10 && distance > 15){
    //digitalWrite(Warning_led,HIGH);
    return String("Please allow distance from obstacle infront of you");
  }
  else if (distance<10){
    //digitalWrite(Warning_led,HIGH);
    //digitalWrite(Hazard_led,HIGH);
    return String("Activating hazard lights, Engaging Breaks");
  }
  else{
    //digitalWrite(Warning_led,LOW);
    return String("Distance Normal");
  }
}

String checkTemperature(){
  if (temperature>=24){
    //digitalWrite(Warning_led,HIGH);
    return String("Turning on A/C, you could become sleepy");
  }
  else if (temperature<=10){
    return String("You're too cold, turning up heat");
  }
  else{
    //digitalWrite(Warning_led,LOW);
    return String("Temperature normal");
  }
}

String checkBPM(){
  if (beat>=140){
    //digitalWrite(Warning_led,HIGH);
    //digitalWrite(Hazard_led,HIGH);
    return String("Detecting Heart problems, activating hazards, engaging break gently, contacting emegency services and contacts");
  }
  else if (beat<=55 && beat>=45){
    return String("You're getting sleepy, engaging A/C, continuing to monitor");
  }
  else if (beat<45){
    //digitalWrite(Warning_led,HIGH);
    //digitalWrite(Hazard_led,HIGH);
    return String("You've fallen asleep, Car has been stopped safely and Emeergency services and contacts have been informed");
  }
  else{
    return String("Heart rate normal");
  }
}



