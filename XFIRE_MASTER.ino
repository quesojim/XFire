#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//Define custom character set

  byte copyrightChar[8] = {
  B01110,
  B10101,
  B11011,
  B11001,
  B11011,
  B10101,
  B01110,
  B00000
};

byte arrowChar[8] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
  B00000
};

byte signalChar[8] = {
  B11111,
  B10101,
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte fullSignalChar1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00101,
  B10101,
  B10101
};

byte fullSignalChar2[8] = {
  B00001,
  B00001,
  B00101,
  B10101,
  B10101,
  B10101,
  B10101,
  B10101
};

//Defining network variables
const char* ssid     = "Pyro NO_ACCESS";
const char* password = "colby460359";

//Other Variables
bool armed_status = false;
int moduleNumber = 1;
int outputPins[] = {14, 32, 33, 25, 26, 27, 15, 13, 12, 4, 0, 2, 5, 18, 19, 3, 1, 23};
bool testStates[18];
int testPin = 34;       
int continuityState = 0;
static unsigned long lastTime = 0;
const int Analog_channel_pin= 36;
int ADC_VALUE = 0;
double voltage_value = 0;
int batteryPercentage = 0;
int lowestPercentage = 100;

// Set web server port number to 80
WiFiServer server(80);

void setup() {
  
  //Setup input pin
  pinMode(34, INPUT);
  //Set all outputs to low
  for (int i = 0; i < 18; i++){
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
    
  }
  //Initialize Serial Communication
  //Serial.begin(115200); //Serial output pulls pins 1 and 3 high, causing output problems.
  //Initialize LCD Screen
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.begin();
  //Create Chars for custom characters
  lcd.createChar(0, copyrightChar);
  lcd.createChar(1, arrowChar);
  lcd.createChar(2, signalChar);
  lcd.createChar(3, fullSignalChar1);
  lcd.createChar(4, fullSignalChar2);
  //Print startup information to screen
  lcd.setCursor(0,0); 
  lcd.print(" X-FIRE "); 
  lcd.write(0);
  lcd.print(" 2019");
  lcd.setCursor(0,1); 
  lcd.print(" Firmware v1.0 ");
  delay(2500);
  lcd.clear();
  lastTime = millis() + 1000;
  

  // Initialize the output variables as outputs
  bool IsArmed;
  IsArmed = false;
  
  //Start WiFi network
  //Serial.print("Setting AP (Access Point)...");

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  //Serial.print("AP IP address: ");
  //Serial.println(IP);
  server.begin();
}

void checkBattery(){
  
  const long interval = 60000;
  static bool state = 0;
  unsigned long now = millis();
  
  //On Loop
  if ( now - lastTime > interval && state == 0) {
    state = 1;

    ADC_VALUE = analogRead(Analog_channel_pin);
    voltage_value = ((double)(ADC_VALUE) / 370);
    batteryPercentage = (((voltage_value - 6.0) / 2.4) * 100);
    if (batteryPercentage < lowestPercentage){
      lowestPercentage = batteryPercentage; 
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Channel: 001 ");
    lcd.setCursor(0,1);
    lcd.print("Battery: ");
    lcd.print(lowestPercentage);
    lcd.print("%");

  }
  //Off Loop
  if ( now - lastTime > interval && state == 1) {
    state = 0;
    lastTime = now;
    
  }
}

void testCues(){
  
  for (int i = 0; i < 18; i++){
    digitalWrite(outputPins[i], HIGH);
    delay(10);
    continuityState = digitalRead(34);
    delay(10);
    digitalWrite(outputPins[i], LOW);
    if (continuityState == 0){
      testStates[i] = true;
    }
    else{
      testStates[i] = false;
    }
    
  }
  
}

void loop(){
checkBattery();
//Open TCP connection for communication
WiFiClient client = server.available();
if (client){
  while (client.connected()){
    while (client.available() > 0){
        //Read Current Message into String
        String message = client.readStringUntil('\r');
        //Serial.println(message);

        if(message == "fire cue 1"){
          client.println("Firing Cue 1...");
          digitalWrite(outputPins[0], HIGH);
          delay(500);
          digitalWrite(outputPins[0], LOW);
          client.println("Fired Cue 1."); 
        }
        if(message == "fire cue 2"){
          client.println("Firing Cue 2...");
          digitalWrite(outputPins[1], HIGH);
          delay(500);
          digitalWrite(outputPins[1], LOW);
          client.println("Fired Cue 2."); 
        }
        if(message == "fire cue 3"){
          client.println("Firing Cue 3...");
          digitalWrite(outputPins[2], HIGH);
          delay(500);
          digitalWrite(outputPins[2], LOW);
          client.println("Fired Cue 3."); 
        }
        if(message == "fire cue 4"){
          client.println("Firing Cue 4...");
          digitalWrite(outputPins[3], HIGH);
          delay(500);
          digitalWrite(outputPins[3], LOW);
          client.println("Fired Cue 4."); 
        }
        if(message == "fire cue 5"){
          client.println("Firing Cue 5...");
          digitalWrite(outputPins[4], HIGH);
          delay(500);
          digitalWrite(outputPins[4], LOW);
          client.println("Fired Cue 5."); 
        }
        if(message == "fire cue 6"){
          client.println("Firing Cue 6...");
          digitalWrite(outputPins[5], HIGH);
          delay(500);
          digitalWrite(outputPins[5], LOW);
          client.println("Fired Cue 6."); 
        }
        if(message == "fire cue 7"){
          client.println("Firing Cue 7...");
          digitalWrite(outputPins[6], HIGH);
          delay(500);
          digitalWrite(outputPins[6], LOW);
          client.println("Fired Cue 7."); 
        }
        if(message == "fire cue 8"){
          client.println("Firing Cue 8...");
          digitalWrite(outputPins[7], HIGH);
          delay(500);
          digitalWrite(outputPins[7], LOW);
          client.println("Fired Cue 8."); 
        }
        if(message == "fire cue 9"){
          client.println("Firing Cue 9...");
          digitalWrite(outputPins[8], HIGH);
          delay(500);
          digitalWrite(outputPins[8], LOW);
          client.println("Fired Cue 9."); 
        }
        if(message == "fire cue 10"){
          client.println("Firing Cue 10...");
          digitalWrite(outputPins[9], HIGH);
          delay(500);
          digitalWrite(outputPins[9], LOW);
          client.println("Fired Cue 10."); 
        }
        if(message == "fire cue 11"){
          client.println("Firing Cue 11...");
          digitalWrite(outputPins[10], HIGH);
          delay(500);
          digitalWrite(outputPins[10], LOW);
          client.println("Fired Cue 11."); 
        }
        if(message == "fire cue 12"){
          client.println("Firing Cue 12...");
          digitalWrite(outputPins[11], HIGH);
          delay(500);
          digitalWrite(outputPins[11], LOW);
          client.println("Fired Cue 12."); 
        }
        if(message == "fire cue 13"){
          client.println("Firing Cue 13...");
          digitalWrite(outputPins[12], HIGH);
          delay(500);
          digitalWrite(outputPins[12], LOW);
          client.println("Fired Cue 13."); 
        }
        if(message == "fire cue 14"){
          client.println("Firing Cue 14...");
          digitalWrite(outputPins[13], HIGH);
          delay(500);
          digitalWrite(outputPins[13], LOW);
          client.println("Fired Cue 14."); 
        }
        if(message == "fire cue 15"){
          client.println("Firing Cue 15...");
          digitalWrite(outputPins[14], HIGH);
          delay(500);
          digitalWrite(outputPins[14], LOW);
          client.println("Fired Cue 15."); 
        }
        if(message == "fire cue 16"){
          client.println("Firing Cue 16...");
          digitalWrite(outputPins[15], HIGH);
          delay(500);
          digitalWrite(outputPins[15], LOW);
          client.println("Fired Cue 16."); 
        }
        if(message == "fire cue 17"){
          client.println("Firing Cue 17...");
          digitalWrite(outputPins[16], HIGH);
          delay(500);
          digitalWrite(outputPins[16], LOW);
          client.println("Fired Cue 17."); 
        }
        if(message == "fire cue 18"){
          client.println("Firing Cue 18...");
          digitalWrite(outputPins[17], HIGH);
          delay(500);
          digitalWrite(outputPins[17], LOW);
          client.println("Fired Cue 18."); 
        }
                          
        if(message == "test"){
          testCues();
          int cueNumber = 0;
          String resultMessage = "NULL";
          for (int i = 0; i < 18; i++){
            cueNumber++;
            if(testStates[i] == true){
              resultMessage = "Cue " + String(cueNumber) + ": GOOD";
            }
            else{
              resultMessage = "Cue " + String(cueNumber) + ": BAD";
            }
            client.println(resultMessage);
          }
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("1-9    ");
            lcd.setCursor(0,1);
            lcd.print("10-18  ");
            
            for (int i = 0; i < 9; i++){
            lcd.setCursor((i+6),0);
            if(testStates[i] == true){
              lcd.print("G");
              
            }
            else{
              lcd.print("X");
            }
            
          }
            for (int i = 9; i < 18; i++){
            lcd.setCursor((i-3),1);
            if(testStates[i] == true){
              lcd.print("G");
              
            }
            else{
              lcd.print("X");
            }
            
          }
                   
      }
      
      delay(80);
      
    }
  }
    client.stop();
    //Serial.println("Client disconnected.");
    //Serial.println("");
    }
    
}
