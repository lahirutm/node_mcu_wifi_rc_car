#define IN_1  12          // MX1508 in1 FW/BW motors (+)           GPIO15(D8)
#define IN_2  14          // MX1508 in2 FW/BW motors (-)           GPIO13(D7)
#define IN_3  2           // MX1508 in3 L/R motors (+)             GPIO2(D4)
#define IN_4  0           // MX1508 in4 L/R motors (-)             GPIO0(D3)
// Later you can change the (+/-) above settings according to the correct direction of the motor's rotating direction.
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String to store app command state.

const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup() { 
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 

 digitalWrite(IN_1, LOW);
 digitalWrite(IN_2, LOW);

 digitalWrite(IN_3, LOW);
 digitalWrite(IN_4, LOW);
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
  }

void goRight(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
  }

void goAheadRight(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
  }

void goBackRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}






