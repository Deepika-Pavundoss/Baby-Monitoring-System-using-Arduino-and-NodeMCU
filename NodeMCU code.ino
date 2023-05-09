#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <string.h>
#include <stdlib.h>



ESP8266WebServer server(80);

char str[100];
String str1="";
int t=0;
char ch='0';
int i = 0;
int l1 = 4;
int l2 = 14;
char status[15]="--------------";
char temp[5] = "----";


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("connected");
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  WiFi.disconnect();
  Serial.println("Starting..."); 
  WiFi.begin("deepika","hello123");
  Serial.print("Connecting");
  while(!(WiFi.status() == WL_CONNECTED)){
    delay(500);
    Serial.print("...");
  }
  Serial.println("");
  Serial.println("Connected Successfully!");

  // IP of Local Network
  Serial.println("Local IP:");
  Serial.println(WiFi.localIP()); 

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started..."); 

}

void handle_OnConnect(){
  //strncpy(str1,str,2);
  //t = atoi(str1);
  server.send(200, "text/html", SendHTML());
}

void loop() { // run over and over
  if (Serial.available()) {
    ch= Serial.read();
    strncat(str, &ch, 1);
//    if(ch=='B'){
//      strcpy(status,"--------------");
//      strcpy(temp,"----");
//      i = 0;
//    }
//    if(i<14){
//      status[i] = ch;
//      i++;
//    }
//    else if(i>13 && i<18){
//      temp[i-14] = ch;
//      i++;
//    }    
//    if(i==18){
//      i = 0;
//    }
    
  }
  server.handleClient();
}

void handle_NotFound(){
  server.send(404, "text/plain", "Some Server issues, please try again later!");  
}

String SendHTML(){
  
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<meta http-equiv='refresh' content='2'/>";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Child Monitoring</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Child Monitoring System</h1>\n";
  ptr+="<p>";
  ptr +=str;
//  ptr +="<p>Temperature in Baby's Room: ";
//  ptr += temp;
//  ptr +=" degree celsius<br>";
//  ptr +="<br>\n";
//  ptr +="Updates: ";
//  ptr += status;
  ptr +="<br></p>\n";
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
  
}
