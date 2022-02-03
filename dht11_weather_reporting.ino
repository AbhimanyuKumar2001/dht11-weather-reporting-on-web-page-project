#include<ESP8266WiFi.h>
#define ssid "OPPO_K1_Abhi"
#define password "12345678"
WiFiServer server(80);


#include "DHT.h"

#define DHTPIN D2     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,password);
 Serial.println("Connecting to Network......");
 while(WiFi.status()!=WL_CONNECTED){
    delay(400);
    Serial.print(".");
   }
   Serial.println("");
   Serial.println("Connected to Network");
   server.begin();
   Serial.println("Use this IP to Acess the page: ");
   Serial.print(WiFi.localIP());
   Serial.print("\n");
  
   Serial.println(F("DHT11 WEATHER REPORTING SYSTEM!\n"));
   dht.begin();
}

void loop() {
  // Waiting a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Checking if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Computing heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Computing heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);



  WiFiClient client=server.available();
    if(!client){
      return;
   }
   
  client.print("<!DOCTYPE html>\n");//HTML used for making WEB page
  client.print("<html>\n");
  client.print("<head>\n");
  client.print("\t<title>WEATHER MONITORING SYSTEM</title>\n");//Title
  client.print("</head>\n");
  client.print("<body><center>\n");
  client.print("\t<h3>WEATHER REPORT:\n</h3>\n");
  client.print("\t<div style=\"margin top: 50px;  margin-bottom:50px \"></div>\n");


  client.print(("Humidity: "));
  client.print(h);
  client.print("%\n");
  client.print("\n");
  client.print(("Temperature( in Celsius): "));
  client.print(t);
  client.print(("°C\n"));
  client.print("\n");
  client.print(("%  Temperature(in Faherenheit): "));
  client.print(f);
  client.print(("°F\n"));
  client.print("\n");
  client.print("HEAT INDEX: \n");
  client.print(hic);
  client.print(("°C ||"));
  client.print(hif);
  client.print(("°F\n"));


  client.print("</center>\n");
  client.print("\n");
  client.print("</body>\n");
  client.print("</html>");
}
