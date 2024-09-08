#define MAX_TEMP 200
#define MIN_TEMP 0
#define MAX_WAVE_NEXTION 255
#define MIN_WAVE_NEXTION 0



void sendToNextion(String dateTime, String timeHours, double temp,String memory, String lastupdate, String filenamed){
  sendTime(dateTime);
  sendDate(timeHours);
  sendTemp(temp);  
  sendWaveform(temp);
  sendMemory(memory);
  sendLastupdate(lastupdate);
  sendFilename(filenamed);
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
