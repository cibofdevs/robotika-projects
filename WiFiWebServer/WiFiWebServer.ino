#include <ESP8266WiFi.h>

#define ON HIGH
#define OFF LOW
#define LED D1

const char* ssid = "SSID"; //Your SSID
const char* password = "PASSWORD"; //Your Password
 
int value = OFF;

WiFiServer server(80);
 
void setup() {
  Serial.begin(9600); //Default 115200
  delay(10);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, OFF);
 
   // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if(request.indexOf("/led=ON") != -1 ){
    digitalWrite(LED, ON);   
    value = ON;
  }
  if(request.indexOf("/led=OFF") != -1 ){
    digitalWrite(LED, OFF);
    value = OFF;   
  }
  
// Set relay according to the request
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset='utf-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<meta http-equiv='x-ua-compatible' content='ie=edge'>");
  client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css' integrity='sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ' crossorigin='anonymous'>");  
  client.println("</head>");
  client.println("<body>"); 
  client.println("<br><br>");
  client.println("<div class='col-md-6'>");
  client.println("<div class = 'container-fluid'>");
  client.println("<div class ='row'>"); 
  client.println("<div class ='col-md-6'>");
  
  client.println("<div class='card mb-3'>");
  client.println("<div class = 'card-header'>");
  client.println("<p>NodeMCU LED Control <p>");
  client.println("</div>");
  client.println("<div class = 'card-body'>");
  client.println("<p> Turn On and Turn Off LED <p>");
  client.println("<a href=\"/led=ON\"\" type = 'button' class='btn btn-danger btn-block'>ON</a>");
  client.println("<a href=\"/led=OFF\"\" type = 'button' class='btn btn-primary btn-block'>OFF</a>");
  client.println("</div>");
  client.println("</div>");
  
  client.println("</div>");
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
