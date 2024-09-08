#include <SD.h>
#include "RTClib.h"
#include <Wire.h>
#include <string.h>

RTC_DS3231 rtc;

char filename[] = "00000000.CSV";
File myFile;
String memorystatus="-";
String lastupdate="-";
String uptime;
double dd,hh,mm,ss;
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

#define INTERVAL_1 10
#define INTERVAL_2 300000 //10 menitan 600000
unsigned long time_1 = 0;
unsigned long time_2 = 0;
//delay systen


String dateTime,timeHours;

void setup()
{
Serial.begin(9600);
//Wire.begin(); //Important for RTClib.h
rtc.begin();

pinMode(4,OUTPUT);
digitalWrite(4,HIGH);

//Serial.println("RTC is NOT running!");
//// following line sets the RTC to the date & time this sketch was compiled
//rtc.adjust(DateTime(__DATE__, __TIME__));
//return;



 if(!SD.begin()){
      memorystatus="SD card error";
    }
    else{
      memorystatus="SD card OK";
      }


//Serial.print("Initializing SD card...");
//if (!SD.begin()) {
//Serial.println("initialization failed!");
//return;
//}
//Serial.println("initialization done.");
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0



int b=0;
bool capt=true;
int capt_second;
unsigned long n;
void loop()
{
 DateTime now = rtc.now();
  int rtc_second = now.second();   

  if(capt==true){
    capt_second=rtc_second;
    capt=false;
    }
  
  sprintf(datee,"%02d/%02d/%04d",now.day(),now.month(),now.year());
  dateTime = String(datee);
  sprintf(timee,"%02d:%02d:%02d",now.hour(),now.minute(),rtc_second);
  timeHours = String(timee);


  if(rtc_second != detik){    
  n++;

int days = n / 60 / 60 / 24;
int hours = (n / 60 / 60) % 24;
int minutes = (n / 60) % 60;
int seconds = n % 60;

if(minutes == 31){
  resetFunc();  //call reset
  }

String sss="0";
String mmm="0";
String hhh="0";
String ddd="0";
if(seconds<10){
  sss="0";
  }
  else{
    sss="";
    }

if(minutes<10){
  mmm="0";
  }
  else{
    mmm="";
    }
    
if(hours<10){
  hhh="0";
  }
  else{
    hhh="";
    }

if(days<10){
  ddd="0";
  }
  else{
    ddd="";
    }



  uptime = ddd+String(days)+":"+hhh+String(hours)+":"+mmm+String(minutes)+":"+sss+String(seconds);  

  detik= rtc_second;
    }

  //SENSOR ACQUISITION///////////////////////////////////////////////////


  if(millis()>=time_1 + INTERVAL_1){
     a++;
     sensor+=analogRead(A0);
     
     if(a==100){
      sensor=sensor/a;
      
      //sensor=map(sensor,0,102400,0,20000);
      //sensor=map(sensor,20500,102400,0,20000);
      //dummy=(sensor/100)+10-54;
      
      dummy = (sensor-205.00)*(200.00/818.00);

      if(dummy>=200){
        dummy=200;
        }

      if(dummy>=0 && dummy <=130){
        digitalWrite(4,HIGH);
        }

      else{
        digitalWrite(4,LOW);
        }


            sendToNextion(dateTime,timeHours,dummy,memorystatus,lastupdate,filename,uptime);
            Serial.flush();
      a=0;
      sensor=0;
      }
    time_1+=INTERVAL_1;
    }

  if(millis()>=time_2+INTERVAL_2){
 
//if(memorystatus=="SD card error"){
//        //memorystatus="SD card error!";
//        }
//        else{
      
      getFileName();
      createFileName();
      
          //}
    
    time_2+=INTERVAL_2;
    }



}

void getFileName(){
DateTime now = rtc.now();
filename[0] = (now.year()/1000)%10 + '0'; //To get 1st digit from year()
filename[1] = (now.year()/100)%10 + '0'; //To get 2nd digit from year()
filename[2] = (now.year()/10)%10 + '0'; //To get 3rd digit from year()
filename[3] = now.year()%10 + '0'; //To get 4th digit from year()
filename[4] = now.month()/10 + '0'; //To get 1st digit from month()
filename[5] = now.month()%10 + '0'; //To get 2nd digit from month()
filename[6] = now.day()/10 + '0'; //To get 1st digit from day()
filename[7] = now.day()%10 + '0'; //To get 2nd digit from day()
//Serial.println(filename);
}

void createFileName(){
  //memorystatus="SD card error!";
//Check file name exist?
if (SD.exists(filename)) {
myFile = SD.open(filename, FILE_WRITE);
if(myFile){
myFile.print(dateTime);
myFile.print(" ");
myFile.print(timeHours);
myFile.print(";");
myFile.print(dummy);
myFile.println();
myFile.close();
//Serial.println("exists.");
lastupdate = "Log: "+dateTime+" "+timeHours;
memorystatus = "SD card OK";
  }
  else{
    memorystatus = "SD error 12";
    }

}

else {
//Serial.println("doesn't exist.");
//Serial.println("Creating new file");
//Serial.println(filename);
myFile = SD.open(filename, FILE_WRITE);
if(myFile){
myFile.println("Datetime;Temperature(deg)");
myFile.print(dateTime);
myFile.print(" ");
myFile.print(timeHours);
myFile.print(";");
myFile.print(dummy);
myFile.println();
myFile.close();
lastupdate = "Log: "+dateTime+" "+timeHours;
memorystatus = "new file OK";
  }
  else{
    memorystatus = "SD error 13";
    }

}
}







#define MAX_TEMP 200
#define MIN_TEMP 0
#define MAX_WAVE_NEXTION 255
#define MIN_WAVE_NEXTION 0



void sendToNextion(String dateTime, String timeHours, double temp,String memory, String lastupdate, String filenamed,String uptime){
  sendTime(dateTime);
  sendDate(timeHours);
  sendTemp(temp);  
  sendWaveform(temp);
  sendMemory(memory);
  sendLastupdate(lastupdate);
  sendFilename(filenamed);
  sendUptime(uptime);
}



void sendUptime(String dataIn){
  String sendIt = "t11.txt=\""+String(dataIn)+"\"";
  Serial.print(sendIt);
  endNextion();
}

void sendFilename(String dataIn){
  String sendIt = "t8.txt=\""+String(dataIn)+"\"";
  Serial.print(sendIt);
  endNextion();
}

void sendLastupdate(String dataIn){
  String sendIt = "t7.txt=\""+String(dataIn)+"\"";
  Serial.print(sendIt);
  endNextion();
}

void sendMemory(String dataIn){
  String sendIt = "t6.txt=\""+String(dataIn)+"\"";
  Serial.print(sendIt);
  endNextion();
}

void sendTime(String dataIn){
  String sendIt = "time.txt=\""+String(dataIn)+"\"";
  Serial.print(sendIt);
  endNextion();
}
void sendDate(String dataIn){
  String sendIt = "date.txt=\""+String(dataIn)+"\"";
  Serial.print(sendIt);
  endNextion();
}
void sendTemp(double dataIn){
  String sendIt = "temp.txt=\""+String(dataIn)+"\"";
  Serial.print(sendIt);
  endNextion();
}
void sendWaveform(double dataIn){   
 
  int decimalMap = (((dataIn - MIN_TEMP)/(MAX_TEMP - MIN_TEMP))*( MAX_WAVE_NEXTION - MIN_WAVE_NEXTION))*0.9843137255;
  String sendIt = "add 3,0,"+String(decimalMap);
  Serial.print(sendIt);
  endNextion();

}
void endNextion() {
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}
