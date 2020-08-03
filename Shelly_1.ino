
#include <PushButton.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define input_switch_1 5 //Switch 1

#define relay_1 4 //Relay 1


PushButton switch_1(input_switch_1); //Assign pin 5 to switch function

BlynkTimer timer; // Define timer


char host[] = "host";
char auth[] = "token";
char ssid[] = "ssid";
char pass[] = "password";

void setup() {
  pinMode(relay_1, OUTPUT);

  pinMode(input_switch_1, INPUT);

  switch_1.setDebounceTime(4); //Set debounce time for 5ms - You can adjust it
  switch_1.disableDoubleClick(); //Disable double click option


  Blynk.config(auth); //Blynk auth token
  WiFi.hostname(host); //Host name
  WiFi.begin(ssid, pass); //Begin wifi session

  timer.setInterval(120000L, CheckConnection); // Every 120s call CheckConnection
  timer.setInterval(25, CheckInputs); // Every 25ms call CheckInputs

}

void loop() {
   if(Blynk.connected()){ 
    Blynk.run();
   }
     timer.run();
}

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

  if (switch_1.isClicked()) //Check if switch 1 is clicked
  {
    set_relay_1_output(); 
  }
}



void set_relay_1_output()
{
  digitalWrite(relay_1, !digitalRead(relay_1)); // Toggle the relay everytime the button is clicked 
  Blynk.virtualWrite(V1, digitalRead(relay_1)); //Assign state of relay for Blynk widget 

}


BLYNK_WRITE(V1) //Virtual pin assigned to first switch input
{
  int relay_1_status = param.asInt(); //Get value of widget 
  digitalWrite(relay_1, relay_1_status); // Assign value from widget to relay output
  delay(20);
  if(relay_1_status != digitalRead(relay_1)) //If value is different than output synchronize to widget
  { 
  Blynk.virtualWrite(V1, digitalRead(relay_1));
  }
  
}
