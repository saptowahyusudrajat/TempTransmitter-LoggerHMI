void setUpRTC(){
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2021, 6, 7, 19, 12, 10));
  
  }
    
}


void getFileName(){
DateTime now = RTC.now();
filename[0] = (now.year()/1000)%10 + '0'; //To get 1st digit from year()
filename[1] = (now.year()/100)%10 + '0'; //To get 2nd digit from year()
filename[2] = (now.year()/10)%10 + '0'; //To get 3rd digit from year()
filename[3] = now.year()%10 + '0'; //To get 4th digit from year()
filename[4] = now.month()/10 + '0'; //To get 1st digit from month()
filename[5] = now.month()%10 + '0'; //To get 2nd digit from month()
filename[6] = now.day()/10 + '0'; //To get 1st digit from day()
filename[7] = now.day()%10 + '0'; //To get 2nd digit from day()
Serial.println(filename);
}

void createFileName(){
//Check file name exist?
if (SD.exists(filename)) {
myFile = SD.open(filename, FILE_WRITE);
myFile.print(dateTime);
myFile.print(" ");
myFile.print(timeHours);
myFile.print(";");
myFile.print(dummy);
myFile.println();
myFile.close();
Serial.println("exists.");
//memorystatus = "SD card OK!";
}

else {
Serial.println("doesn't exist.");
Serial.println("Creating new file");
Serial.println(filename);
myFile = SD.open(filename, FILE_WRITE);
myFile.println("Datetime;Temperature(deg)");
myFile.close();
//memorystatus = "SD card error!";
}
}
