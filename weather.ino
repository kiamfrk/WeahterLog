/*
 * @ Realised by ING ANYAM 
 * @ Supervised by Dr NISSO Nicodem of ENSPM
 * @ NATIONAL ADBANCED SCHOOL OF ENGENEERING OF MAROUA (ENSPM)
 * @ 14 december 2021 
 */

#include <Bridge.h>
#include <Temboo.h>
#include <Process.h>
#include "DHT.h"
#include "Account.h" // contains Temboo account and googlespreadsheets information, as described below

#define DHTPIN 8 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

 
int light;
float hum;
float temp ;
unsigned long time;
Process date;

boolean debug_mode = false;

//we declare the fonction we are going to use
void appendVal (float, float, int );

void setup() {
  
    Serial.begin(115200);
    delay(4000);
    while(!Serial);
  
  //we start reading dht sensor data
  dht.begin();
  
  Bridge.begin();
  

  //start time and date
  if (!date.running())  {
  date.begin("date");
  date.addParameter("+%D-%T");
  date.run();
  }
}

void loop() {

  //we store the sensor's data
  
  hum  = dht.readHumidity();
  temp = dht.readTemperature();
  light= analogRead(A0);

  //we verify if we haven't reach the max choreo call wich is 10
  
  if (calls <= maxCalls) {

    //here we call our mean function with temperature, humidity and lightLevel to log it inside the spreadsheets
    runAppendVal(temp,hum,light);
  }
  //we wait 3 second
  delay(3000);
}


  void runAppendVal(float temp, float hum, int light){
      
    TembooChoreo AppendValuesChoreo;
    
    AppendValuesChoreo.begin();

    // Set Temboo account credentials
    AppendValuesChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendValuesChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendValuesChoreo.setAppKey(TEMBOO_APP_KEY);

    // Identify the Choreo to run
    AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");  

    // Set Choreo inputs
    AppendValuesChoreo.addInput("RefreshToken", GOOGLE_CLIENT_REFRESH_TOKEN);
    AppendValuesChoreo.addInput("ClientSecret", GOOGLE_CLIENT_SECRET);
    AppendValuesChoreo.addInput("ClientID", GOOGLE_CLIENT_ID);
    AppendValuesChoreo.addInput("SpreadsheetID", GOOGLE_SPREADSHEET_ID);

     //get time and date
    if (!date.running())  {
        date.begin("date");
        date.addParameter("+%D-%T");
        date.run();
     }
  
   
      String timeString = date.readString(); 
      
      //here we have to put time, temperature, humidity and lightLevel into JSON format
      String data = "[[\"" + timeString +"\", \""+String(temp) + "\", \"" + String(hum) + "\", \"" + String(light) + "\"]]";
      
    AppendValuesChoreo.addInput("Values",data);
  
    AppendValuesChoreo.run();

    while(AppendValuesChoreo.available()) {
      char c = AppendValuesChoreo.read();
      Serial.print(c); 
     }
    AppendValuesChoreo.close();
  }
