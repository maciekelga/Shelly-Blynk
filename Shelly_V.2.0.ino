#include <PushButton.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define input_switch_1 13 //Switch 1
#define relay_1 4 //Relay 1

PushButton switch_1(input_switch_1); //Assign switch 1

//Others
unsigned long time_after_start; //Variable for assign time from millis
BlynkTimer timer; // Define timer

//Blynk settings - token, wifi ssid and pass
char host[] = "write Your host name";
char auth[] = "write Your auth token";
char ssid[] = "write Your SSID";
char pass[] = "write Your password";

void setup() {
  pinMode(relay_1, OUTPUT); //Define pinMode
  pinMode(input_switch_1, INPUT); //Define pinMode
  switch_1.setDebounceTime(5); //Set debounce time for 5ms - You can adjust it
  switch_1.disableDoubleClick(); //Disable double click option
  Blynk.config(auth); //Blynk auth token
  WiFi.hostname(host); //Host name
  WiFi.begin(ssid, pass); //Begin wifi session
  timer.setInterval(60000L, CheckConnection); // Interrupt which check if still connected every 30 seconds 
  timer.setInterval(25, CheckInputs); // Interrupt which check if still connected every 8 miliseconds
  time_after_start = millis(); // Get value from millis 
  
  //Loop which check for 10s if Blynk is connected
  while((millis() - time_after_start) <10000) // Execute for 10 seconds or if Blynk is connected
   {
     Blynk.connect(); //Connect to Blynk server
     Blynk.run(); //Blynk run
     if(Blynk.connected()){ //Break loop when is connected
        break;  
     }
   }

}

//Loop which is call every 60s for checking connection
  void CheckConnection(){    
  if(!Blynk.connected()){ //If Blynk not connected
    
    if (WiFi.status() == WL_CONNECTED) //If Wifi is connected than try to connect to server
  { 
    Blynk.connect(5000);  // Try to connect to server
  }
         
  }
}

void CheckInputs(){  // Check every 25ms state of inputs
  switch_1.update(); //Update button state 

  // Check for a specific button event, eg. isClicked()
  if (switch_1.isClicked())
  {
    set_relay_1_output(); 
  }
}


BLYNK_WRITE(V10) //Virtual pin assigned to first switch input
{
  int relay_status = param.asInt(); //Get value of widget 
  digitalWrite(relay_1, relay_status); // Assign value from widget to relay output
  if(relay_status != digitalRead(relay_1)) //If value is different than output synchronize to widget
  { 
  Blynk.virtualWrite(V10, digitalRead(relay_1));
  }
}


void loop() {
   if(Blynk.connected()){ 
    Blynk.run();
  }
     timer.run();
}

void set_relay_1_output()
{
  digitalWrite(relay_1, !digitalRead(relay_1)); // Toggle the relay everytime the button is clicked 
  Blynk.virtualWrite(V10, digitalRead(relay_1)); //Assign state of relay for Blynk widget
   

}
