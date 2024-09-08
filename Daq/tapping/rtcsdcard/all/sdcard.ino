
void sdCardCheck(){
  if (SD.begin())
  {
    Serial.println("SD card initialization successfull");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}


void logToSDCard(String realdate,String realtime,int temp){
  File dataFile = SD.open("Log.csv",FILE_WRITE);   
  if(dataFile){
  
    String mDate = realdate;
    String mTime = realtime;
    String mTemp = String(temp);
  
    dataFile.println(mDate+" "+mTime+","+mTemp);
    dataFile.close ();
  }
  else{
        Serial.println("Error Access");
    }
  }
