#include <ESP8266WiFi.h>
#include "FS.h"
#include "Updater.h"
#include <ESP8266HTTPClient.h>

HTTPClient http;
int counter=0;

String fileName;

String url = "http://18.218.214.164:8080/s3/download?filename=copass_program1_1.ino.nodemcu.bin";
void setup() {
  
   Serial.begin(115200);   

   WiFiConnect();
    //file_name = test2.htm
    Serial.println(url);
    if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
   }
   size_t size;
   Serial.println(SPIFFS.format()?"formated":"error while formating");
    File f = SPIFFS.open("/otaFile.bin", "w");
    if (f) {
      http.begin(url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          size = http.writeToStream(&f);
          fileName = f.name();
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
    
      f.close();
    }
    http.end();
     Serial.println(size);
      Serial.println(fileName);
 
   //https://agnext-jasmine.s3.us-east-2.amazonaws.com/iot/copass_program1_1.ino.nodemcu.bin
  
    File file = SPIFFS.open("/otaFile.bin","r");
  
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }   
    Serial.println("Starting update..");
    size_t fileSize = file.size();
    if(!Update.begin(fileSize)){
       
       Serial.println("Cannot do the update");
       return;
    };
 
    Update.writeStream(file);
 
    if(Update.end()){
       
      Serial.println("Successful update");  
    }else {
       
      Serial.println("Error Occurred: " + String(Update.getError()));
      return;
    }
     
    file.close();
 
    Serial.println("Reset in 4 seconds...");
    delay(4000);
 
    ESP.restart();
}
  
void loop() {}

void WiFiConnect(){
       WiFi.begin("Sahil Vabhiav", "24041990");//Testing office
  while(WiFi.status()!=WL_CONNECTED){
      Serial.print(".");
      counter++;
      delay(500);
      if(counter>=20){ 
        ESP.restart();
    }
  }
  Serial.println(WiFi.localIP());
}
