#include <ESP8266WiFi.h>        //Use ESP8266 functions  
#include <WiFiClientSecure.h>                                            
#include <ESP8266HTTPClient.h>
#include <GxEPD.h>

#include <GxGDEW027C44/GxGDEW027C44.h>    // 2.7" b/w/r

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#if defined(ESP8266)

// generic/common.h
//static const uint8_t SS    = 15;
//static const uint8_t MOSI  = 13;
//static const uint8_t MISO  = 12;
//static const uint8_t SCK   = 14;
// pins_arduino.h
//static const uint8_t D8   = 15;
//static const uint8_t D7   = 13;
//static const uint8_t D6   = 12;
//static const uint8_t D5   = 14;

// GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
GxIO_Class io(SPI, SS, 0, 2); // arbitrary selection of D3(=0), D4(=2), selected for default of GxEPD_Class
// GxGDEP015OC1(GxIO& io, uint8_t rst = 2, uint8_t busy = 4);
GxEPD_Class display(io); // default selection of D4(=2), D2(=4)
#endif

 // const char* ssid = "PandoraBox-2.4G-551F22";
 const char* ssid = "123";                          
  const char* password = "123";        //WIFI Password
  const char* host = "api.thingspeak.com";  //We read the data from this host                                   
  const int httpPortRead = 80;                                           
                                                  
  const char* url1 = "/apps/thinghttp/send_request?api_key=4QE1GP0WFZMJGKYB";     //Change this URL Cases
  const char* url2 = "/apps/thinghttp/send_request?api_key=3240Z9CZCAI2AQXI";   //Deaths
  const char* url3 = "/apps/thinghttp/send_request?api_key=XBSVQKPNK95K9E1T";   //Recovered
  int To_remove;      //There are some irrelevant data on the string and here's how I keep the index
                      //of those characters 
  String Cases,Deaths,Recovered,Data_Raw,Data_Raw_1,Data_Raw_2,Data_Raw_3;  //Here I keep the numbers that I got

  WiFiClient client;      //Create a WiFi client and http client                                                     
  HTTPClient http; 

  
 void setup() {
  // put your setup code here, to run once:
   display.init();
   display.setRotation(3);

    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();             //Disconnect and reconnect to the Wifi you set                                                 
    delay(1000);                                                                  
    WiFi.begin(ssid, password);                                                   
    Serial.println("Connected to the WiFi network");   //Display feedback on the serial monitor                                        
    Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:

     if( http.begin(host,httpPortRead,url1))        //Connect to the host and the url                                      
      {
        int httpCode = http.GET();                //Check feedback if there's a response                                                  
        if (httpCode > 0)                                                              
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {                
              
              Data_Raw = http.getString();   //Here we store the raw data string
            
              
              Data_Raw_1 = Data_Raw;                                    
              To_remove = Data_Raw_1.indexOf(">");                      //I look for the position of this symbol ">"                                 
              Data_Raw_1.remove(0,To_remove+1);                        //I remove it and everything that's before
              
              To_remove = Data_Raw_1.indexOf("<");                     //I look for the position of this symbol ">"                                
              Data_Raw_1.remove(To_remove,Data_Raw_1.length());          //I remove it and everything that's after
                                                                     //Example: This is the raw data received <td style="font-weight: bold; text-align:right">63,927</td>
                                                                     //First we look for ">" and we remove everything before it including it
                                                                     //We stay with this 63,927</td>
                                                                     //We look for "<" symbol and we remove it + everything after
                                                                     //We keep only this 63,927 as string
              Cases=Data_Raw_1;
              Serial.print("C: ");  //I choosed to display it on the serial monitor to help you debug
              Serial.println(Cases); 
              
              ///////////////
              
              Data_Raw_2=Data_Raw;
              To_remove = Data_Raw_2.indexOf("<span>");
              Data_Raw_2.remove(0,To_remove+6);
              
              Data_Raw_3=Data_Raw_2;
              To_remove = Data_Raw_2.indexOf("</span>");
              Data_Raw_2.remove(To_remove,Data_Raw_2.length());

              Deaths=Data_Raw_2;
              Serial.print("D: ");
              Serial.println(Deaths);
            
              To_remove = Data_Raw_3.indexOf("<span>");
              Data_Raw_3.remove(0,To_remove+6);

              To_remove = Data_Raw_3.indexOf("<");
              Data_Raw_3.remove(To_remove,Data_Raw_3.length());

              Recovered=Data_Raw_3;
              
              Serial.print("R: ");
              Serial.println(Recovered);    
                                                                                       
            }
        }
        else //If we can't get data
        {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        
        http.end();   
                                                                    
      }
      
    else //If we can't connect to the HTTP
      {
        Serial.printf("[HTTP} Unable to connect\n");
      }
      

    while (WiFi.status() != WL_CONNECTED)     //In case the Wifi connexion is lost                                    
      { 
        
        WiFi.disconnect();                                                        
        delay(1000);                                                             
        
        WiFi.begin(ssid, password);                                              
        Serial.println("Reconnecting to WiFi..");       
        delay(10000);                                                             
      }
    showFontCallback();

    
}

void showFontCallback(){
  
  const char* name = "FreeSansBold24pt7b";
  const GFXfont* f = &FreeSansBold24pt7b;
  
  const char* name9 = "FreeSans9pt7b";
  const GFXfont* f9pt = &FreeSans9pt7b;
  

  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_RED);
  display.setFont(f);
  display.setCursor(20, 40);
  display.println("COVID-19");
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f9pt);
  display.setCursor(35, 65);
  display.println("Country :");
  display.setTextColor(GxEPD_RED);
  display.setCursor(115, 65);
  display.println("United States");
  display.drawLine(0,85,264,85,GxEPD_BLACK);
  display.drawLine(95,85,95,176,GxEPD_BLACK);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f9pt);
  display.setCursor(0, 105);
  display.println("Cases");
  display.setTextColor(GxEPD_RED);
  display.setCursor(105, 105);
  display.println(Cases);
  display.drawLine(0,115,264,115,GxEPD_BLACK);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0, 135);
  display.println("Deaths");
  display.setTextColor(GxEPD_RED);
  display.setCursor(105, 135);
  display.println(Deaths);
  display.drawLine(0,145,264,145,GxEPD_BLACK);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0, 165);
  display.println("Recovered");
  display.setTextColor(GxEPD_RED);
  display.setCursor(105, 165);
  display.println(Recovered);
  delay(60000);  
  display.update();
 
  
   
}
