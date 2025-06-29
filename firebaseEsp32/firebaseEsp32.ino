#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "WiFi_Pritha-2.4G"
#define WIFI_PASSWORD "pritha@1234"

#define PWMChannel 0
const int freq = 5000;
const int resolution = 8;

#define API_KEY "yourFirebaseAPIKey" // Your Firebase project API key
#define DATABASE_URL "youtrFirebaseDatabaseURL" // Your Firebase Realtime Database URL

/* 4. Define the user Email and password that alreadey registerd or added in your project */
// #define USER_EMAIL "USER_EMAIL"
// #define USER_PASSWORD "USER_PASSWORD"

// Define Firebase Data object
FirebaseData fbdo,fbdo_s1,fbdo_s2;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOk = false;
float data1 = 0.0;
float data2 = 0.0;
int i=0;

int pwmValue =0;
bool ledStatus = false;
void setup()
{
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  ledcAttachChannel(10,freq,resolution,PWMChannel);
  // ledAttachPin(3,);
  analogReadResolution(12);
  
  Serial.begin(115200);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
    if (millis() - ms > 10000)
      break;
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  // auth.user.email = USER_EMAIL;
  // auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  if(Firebase.signUp(&config,&auth,"","")){
    Serial.println("Signup OK");
    signupOk=true;
  }
  else{
    Serial.println(config.signer.signupError.message.c_str());
  }
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectWiFi(true);
  
  //stream
  if(!Firebase.RTDB.beginStream(&fbdo_s1,"led/analog"))
    Serial.println("Stream 1 begin error, " + fbdo_s1.errorReason());
  if(!Firebase.RTDB.beginStream(&fbdo_s2,"led/digital"))
    Serial.println("Stream 2 begin error, " + fbdo_s2.errorReason());
}

void loop()
{

  // Firebase.ready() should be called repeatedly to handle authentication tasks.

  if (Firebase.ready() && signupOk && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    data1=data1+1;
    data2=data2+1;
    String arr[] = {"Hello","Hi","Bye","GoodBye"};
    i = (i+1)%4;
    if (Firebase.RTDB.setFloat(&fbdo, "Sensor/data1", data1)){
      Serial.print(data1);
      Serial.println(" successfully saved to:" +fbdo.dataPath()+" ("+fbdo.dataType() + ")");
    }
    else{
      Serial.println("FAILED:"+ fbdo.errorReason());
    }
    if (Firebase.RTDB.setFloat(&fbdo, "Sensor/data2", data2)){
      Serial.print(data2);
      Serial.println(" successfully saved to:" +fbdo.dataPath()+" ("+fbdo.dataType() + ")");

    }
    else{
      Serial.println("FAILED:"+ fbdo.errorReason());
    }
    if (Firebase.RTDB.setString(&fbdo, "Sensor/data3", arr[i])){
      Serial.print("Hello World");
      Serial.println(" successfully saved to:" +fbdo.dataPath()+" ("+fbdo.dataType() + ")");

    }
    else{
      Serial.println("FAILED:"+ fbdo.errorReason());
    }
  }
  if (Firebase.ready() && signupOk){ 
    if(!Firebase.RTDB.readStream(&fbdo_s1))
      Serial.println("stream 1 read error" + fbdo_s1.errorReason());
    if (fbdo_s1.streamAvailable()){
      if(fbdo_s1.dataType() == "int"){
        pwmValue = fbdo_s1.intData();
        Serial.println("successfully read from:" +fbdo_s1.dataPath() +": "+ pwmValue + " (" + fbdo_s1.dataType() + ")");
        ledcWriteChannel(PWMChannel,pwmValue);
      }
    }
   
    if(!Firebase.RTDB.readStream(&fbdo_s2))
      Serial.println("stream 1 read error" + fbdo_s2.errorReason());
    if (fbdo_s2.streamAvailable()){
      if(fbdo.dataType() == "int"){
        ledStatus = fbdo_s2.intData();
        Serial.println("successfully read from:" +fbdo_s2.dataPath() +": "+ ledStatus + " ("+fbdo_s2.dataType() + ")");
        digitalWrite(8,ledStatus);
      }
    }
    // Serial.println();
  }
}
