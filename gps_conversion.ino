////////////////////////////// gps acquisition and conversion////////////////////////
////////////////////////////////////////////////////////////////////////////////////
#include<SoftwareSerial.h>
SoftwareSerial GPSModule(10,11); //  RX,TX
////////////////////////////////////////////////////////////////////////////////////
uint8_t lat_degree;
int lat_minute;
int lat_sec;

uint8_t long_degree;
int long_minute;
int long_sec;

bool north_pole = false;
bool east_pole = false;

int index_nmea;
int stringStart = 0;
String nmea[15];
////////////////////////////////////////////////  void setup
void setup(){
  Serial.begin(9600);
  GPSModule.begin(9600); 
}
////////////////////////////////////////////////  void loop
void loop(){
  Serial.flush();
  GPSModule.flush();
  while (GPSModule.available() > 0)
  {
    GPSModule.read();

  } 
  
    if (GPSModule.find("$GPRMC,"))
  {
      String tempMsg = GPSModule.readStringUntil('\n');
      for (int i = 0; i < tempMsg.length(); i++)
      {
        if (tempMsg.substring(i, i + 1) == ",")
        {
          nmea[index_nmea] = tempMsg.substring(stringStart, i);
          stringStart = i + 1;
          index_nmea++;
        }
        if (i == tempMsg.length() - 1)
        {
          nmea[index_nmea] = tempMsg.substring(stringStart, i);
        }
       }
   }
   else
    {
      Serial.println("Update Failed");
    }

    converttoLat();
    converttoLon();

    Serial.print("long_degree"); 
    Serial.print(long_degree);
    Serial.println("");
    
    Serial.print("pole-1");
    Serial.print(nmea[5]);           
    Serial.println("");
    
    Serial.print("lat_degree"); 
    Serial.print(lat_degree);
    Serial.println("");

    Serial.print("pole-2");
    Serial.print(nmea[3]);          
    Serial.println("");
    stringStart = 0;
    index_nmea = 0;
    delay(10);
}
//////////////////////////////////////////////// fuction definitions
void converttoLat(){
  
  if (nmea[3] == "N"){
     north_pole = false;
  }
  else{
     north_pole = true;
  }
    
  for (int i = 0; i < nmea[2].length(); i++)
  {
    if (nmea[2].substring(i, i + 1) == ".")
    {
      lat_degree = nmea[2].substring(0, i - 2).toInt();
      lat_minute = nmea[2].substring(i - 2,i - 1).toInt();
      lat_sec =nmea[2].substring(i+1).toInt();
    }
  }
  
}
////////////////////////////////////
void converttoLon(){

  if (nmea[5] == "E"){
     east_pole = false;
  }
  else{
     east_pole = true;
  }
    
  for (int i = 0; i < nmea[4].length(); i++)
  {
    if (nmea[2].substring(i, i + 1) == ".")
    {
      long_degree = nmea[4].substring(0, i - 2).toInt();
      long_minute = nmea[4].substring(i - 2,i - 1).toInt();
      long_sec =nmea[4].substring(i+1).toInt(); 
    }
  }
}
///////////////////////////////////////
