//RTC
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
RTC_DS1307 RTC;
#include <string.h>
#include <SPI.h>
#include <SD.h>
#define CS 4



char filename[] = "00000000.CSV";
File myFile;
String memorystatus="-";
String lastupdate="-";

//SDCARD

///////////////////////////////////
double dummy =0.00;

//inisialization format
char datee[10];
char timee[8];
double detik = 0;

//SENSOR
int a;
double sensor;
double cnv;
double degree;
//SENSOR

void setup() { 
 Serial.begin(9600);
 pinMode(CS,OUTPUT);
 Wire.begin();
 if(!SD.begin()){
  memorystatus="SD card error!";
  }
 //sdCardCheck();
 //SET RTC INISIALIZATION
 setUpRTC();
}


//delay system
#define INTERVAL_1 10
unsigned long time_1 = 0;
//delay systen


String dateTime,timeHours;
void loop() { 
  DateTime now = rtc.now();
  int rtc_second = now.second();   

  sprintf(datee,"%02d/%02d/%04d",now.day(),now.month(),now.year());
  dateTime = String(datee);
  sprintf(timee,"%02d:%02d:%02d",now.hour(),now.minute(),rtc_second);
  timeHours = String (timee);

  //SENSOR ACQUISITION///////////////////////////////////////////////////


  if(millis()>=time_1 + INTERVAL_1){
     a++;
     sensor+=analogRead(A0);
     if(a==100){
      sensor=sensor/a;
      sensor=sensor*100;
      sensor=map(sensor,0,100000,0,20000);
      dummy=sensor/100;

      getFileName();
      createFileName();

      if(memorystatus=="SD card OK!"){
        lastupdate = "Log: "+dateTime+" "+timeHours;
        }
            //sendToNextion(dateTime,timeHours,dummy,memorystatus,lastupdate,filename);
      a=0;
      sensor=0;
      }
    time_1+=INTERVAL_1;
    }
  
  
  //if(a==100){
     
      
      //sensor=(map(sensor,0,102400,400,2000));
      //cnv = sensor/100;  //dalam mA (4-20 mA);      
      
      
  //a=0;
  //sensor=0;
 // }
  
  //SESNOR ACQUISITION///////////////////////////////////////////////////

  if(rtc_second != detik){
    //degree=map(analogRead(A0),0,1000,0,2000);
    //dummy = degree/10;
    //sendToNextion(dateTime,timeHours,dummy);
   //dummy = random(0,150);
  /* Serial.print(dateTime);
   Serial.print(" ");
   Serial.print(timeHours);
   Serial.print(";");
   Serial.println(dummy);*/
 
   if (rtc_second % 10 == 0){
   //logToSDCard(dateTime, timeHours,dummy); 
   //Serial.println("Saved to Log");
    }
   //detik = rtc_second;
  }
  else{
    
    }
    

  
 
}
