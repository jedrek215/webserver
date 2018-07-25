#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>

String page,decodedmsg,str;
int myVariable=0;
DNSServer dnsServer;
const byte DNS_PORT = 53;
IPAddress ip(192, 168, 1, 1); // where xx is the desired IP Address
//IPAddress gateway(1, 1, 1, 1); // set gateway to match your network
//IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your

ESP8266WebServer server(80); //Server on port 80

void buildWebsite(){
page ="<html> <title> SEND STRING</title> <head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <style> body {font-family: Calibri, Helvetica, sans-serif; color:white; background: #232428;} form {border: 3px solid white; margin:0px 400px; background-color: white; border-radius: 10px;} .messages {border: 15px solid white; margin:0px 385px; background-color: white; border-radius: 10px;} input[type=text]{ width: 100%; padding: 12px 20px; margin: 8px 0; display: inline-block; border: 1px solid #ccc; box-sizing: border-box; border-radius: 5px; } textarea { resize: none; width: 100%; height: 10%; border: 1px solid #ccc; border-radius: 10px; } .button{ background-color: #296ee5; color: white; padding: 14px 20px; margin: 8px 0; border: none; cursor: pointer; width: 100%; } .container { padding: 16px; } @media screen and (max-width: 640px) { form {border: 3px solid white; margin:0px 20px; background-color: white; border-radius: 10px;} } </style> </head> <body> <h1 align='center'>ESP 8266 Message</h1> <form action ='/'> <div class='container'> <label style='color:black; text-align:left;'><b>Send message</b></label><br> <input type='text' placeholder='Enter message' name ='mensahe' required> <br><br> <input type='submit' class='button' value='Send'> </div> </form> <br> <br> <div class = 'messages'> <div class='container'> <label style='color:black; text-align:left;'><b>Received messages</b></label><br> <textarea readonly>";
page+= myVariable;
page +="</textarea> <br><br> <input type='button' class = 'button' value='Reload' onclick=\"location.href='/';\" /></div> </div> </body> </html>";
}

/**
 * function to parse and fix string input 
 */
void handleString(){
  str = "";
  myVariable++;
buildWebsite();
server.send(200,"text/html", page);

   str = server.arg("mensahe");
  
  decodedmsg = str;
  decodedmsg.replace("+"," ");
  
  if(decodedmsg.length()>0)
  {
  Serial.print("Message:");
  Serial.println(decodedmsg);
  }
  
}

void setup() {
  delay(1000);
 Serial.begin(115200);
  dnsServer.start(DNS_PORT, "*", ip);
 //WiFi.softAPConfig(ip,gateway,subnet);
 WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0));
 WiFi.softAP("Emergency Network");
 
 
 Serial.println("HTTP server started");
  server.on("/", handleString);
  server.begin();

}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  

}
