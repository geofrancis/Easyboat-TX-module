#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h> 

//---------------------------------------------------------------------------
#include "SBUS.h"
SBUS x8r(Serial1);
// channel, fail safe, and lost frames data
uint16_t channels[16];
bool failSafe;
bool lostFrame;
//----------------------------------------------------------------------------


#include "FrSkySportSensor.h"
#include "FrSkySportSensorAss.h"
#include "FrSkySportSensorEsc.h"
#include "FrSkySportSensorFcs.h"
#include "FrSkySportSensorFlvss.h"
#include "FrSkySportSensorGps.h"
#include "FrSkySportSensorRpm.h"
#include "FrSkySportSensorSp2uart.h"
#include "FrSkySportSensorVario.h"
#include "FrSkySportSingleWireSerial.h"
#include "FrSkySportTelemetry.h"
#include "SoftwareSerial.h"


FrSkySportSensorAss ass;                               // Create ASS sensor with default ID
FrSkySportSensorEsc esc;                               // Create ESC sensor with default ID
FrSkySportSensorFcs fcs;                               // Create FCS-40A sensor with default ID (use ID8 for FCS-150A)
FrSkySportSensorFlvss flvss1;                          // Create FLVSS sensor with default ID
FrSkySportSensorFlvss flvss2(FrSkySportSensor::ID15);  // Create FLVSS sensor with given ID
FrSkySportSensorGps gps;                               // Create GPS sensor with default ID
FrSkySportSensorRpm rpm;                               // Create RPM sensor with default ID
FrSkySportSensorSp2uart sp2uart;                       // Create SP2UART Type B sensor with default ID
FrSkySportSensorVario vario;                           // Create Variometer sensor with default ID
#include "FrSkySportPollingDynamic.h"
FrSkySportTelemetry telemetry(new FrSkySportPollingDynamic()); // Create telemetry object with dynamic (FrSky-like) polling




const int ledPin =  LED_BUILTIN;
int ledState = LOW;   
unsigned long previousMillis = 0; 
const long interval = 1000;   



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


//RC inputs   

int ch1 = 1500;  //throttle
int ch2 = 1500;  //rudder
int ch3 = 1500;  //camera yaw
int ch4 = 1500;  //lights
int ch5 = 1500;  //anchor winch
int ch6 = 1500;  //tow winch
int ch7 = 1500;  //bilge pump / fire monitor
int ch8 = 1500;  //flight mode
int ch9 = 1500;  //avoid gain
int ch10 = 1350; //avoid mode
int ch11 = 1350; //avoid mode
int ch12 = 1350; //avoid mode
int ch13 = 1350; //avoid mode
int ch14 = 1350; //avoid mode
int ch15 = 1350; //avoid mode
int ch16 = 1350; //avoid mode

// Define variables to store  Telemetry
 float tel1;
 float tel2;
 float tel3;
 float tel4;
 float tel5;
 float tel6;
 float tel7;   
 float tel8;
 float tel9;
 float tel10;
 float tel11;
 float tel12;
 float tel13;
 float tel14;

// Variable to store if sending data was successful
String success;
//-------------------------------------------------------------------------------
//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    float eh1;
    float eh2;
    float eh3;
    float eh4;
    float eh5;
    float eh6;
    float eh7;   
    float eh8;
    float eh9;
    float eh10;
    float eh11;
    float eh12;
    float eh13;
    float eh14;
    } 
struct_message;

// Create a struct_message called RC_CHANNELS to hold sensor readings
struct_message RC_CHANNELS;

// Create a struct_message to hold incoming sensor readings
struct_message INCOMING_TELEMETRY;

esp_now_peer_info_t peerInfo;
//--------------------------------------------------------------------------------------
// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}
//-----------------------------------------------------------------------------------
// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&INCOMING_TELEMETRY, incomingData, sizeof(INCOMING_TELEMETRY));
  Serial.print("Bytes received: ");
  Serial.println(len);
  tel1 = INCOMING_TELEMETRY.eh1;
  tel2 = INCOMING_TELEMETRY.eh2;
  tel3 = INCOMING_TELEMETRY.eh3;
  tel4 = INCOMING_TELEMETRY.eh4;
  tel5 = INCOMING_TELEMETRY.eh5;
  tel6 = INCOMING_TELEMETRY.eh6;
  tel7 = INCOMING_TELEMETRY.eh7;
  tel8 = INCOMING_TELEMETRY.eh8;
  tel9 = INCOMING_TELEMETRY.eh9;
  tel10 = INCOMING_TELEMETRY.eh10;
  tel11 = INCOMING_TELEMETRY.eh11;
  tel12 = INCOMING_TELEMETRY.eh12;
  tel13 = INCOMING_TELEMETRY.eh13;
  tel14 = INCOMING_TELEMETRY.eh14;
}
//--------------------------------------------------------------------------------------
 


int val;
int angle;
int avoidmode;



//=======================================================================

void setup() {

Serial.begin(115200);
  x8r.begin();
   telemetry.begin(FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_12, &ass, &esc, &fcs, &flvss1, &flvss2, &gps, &rpm, &sp2uart, &vario);
  
pinMode(LED_BUILTIN, OUTPUT);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
                                              

}


void loop() { 

SBUSin();
ESPNOW();
Telemetry();
serialprint();

}
