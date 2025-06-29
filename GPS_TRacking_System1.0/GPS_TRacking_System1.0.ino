// #include <SoftwareSerial.h>
#include <TinyGPS++.h>

String Latitude="0.0";
String Longitude="0.0";

TinyGPSPlus gps;

// SoftwareSerial gpsSerial(3,2); // RXpin, TXpin(for GPS module)
// SoftwareSerial gsmSerial(5,4); // RXpin, TXpin(for GPS module)
HardwareSerial GSM(1); // RXpin, TXpin(for GSM module)
HardwareSerial gpsSerial(2); // RXpin, TXpin(for GPS module)

void setup() {
  Serial.begin(9600);
  // gpsSerial.begin(9600);
  // gsmSerial.begin(9600);
  GSM.begin(9600, SERIAL_8N1, 26, 25); // Serial1 on pins 16 and 17
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);   // Serial2 on pins 4 and 5
  // Initialize GSM module
  sendCommand("AT");
  delay(300);                // Check if module is responding
  sendCommand("AT+CMGF=1");         // Set SMS mode to Text
  delay(300);                // Check if module is responding
  sendCommand("AT+CSCS=\"GSM\"");
  delay(300);                // Check if module is responding
}

void loop() {
  // Latitude="0.0";
  // Longitude="0.0";
  // Read GPS data
 while (gpsSerial.available() > 0){
    gps.encode(gpsSerial.read());
    if (gps.location.isUpdated()){
      Latitude=gps.location.lat();
      Longitude=gps.location.lng();
      Serial.println(Latitude +","+ Longitude);
      String smsMessage = "Live Location: https://maps.google.com/maps?q="+Latitude+","+Longitude +"";
      SOS("+917439928541", smsMessage); // Change to your number

      delay(60000); // Send every 1 minute
      break;
    }
  }
    // Formulate SMS message

    // Send SMS through GSM module
}
void SOS(String number, String message){
  sendCommand("AT"); 
  delay(300);               // Check if module is responding
  sendCommand("AT+CMGF=1");         // Set SMS mode to Text
  delay(300);               // Check if module is responding
  sendCommand("AT+CSCS=\"GSM\"");   // Set character set to GSM
  delay(300);               // Check if module is responding
  sendSMS(number.c_str(),message.c_str());
}
void sendCommand(const String& cmd) {
  GSM.println(cmd);
  delay(500);

  while (GSM.available()) {
    Serial.write(GSM.read());
  }
}
void sendSMS(const char* number, const char *message) {
  GSM.print("AT+CMGS=\"");
  GSM.print(number);
  GSM.println("\"");
  delay(1000);
  GSM.print(message);
  GSM.write(26); // Ctrl+Z to send SMS
  delay(1000);      // Wait for SMS to be sent

  Serial.println("SMS Sent!");
}