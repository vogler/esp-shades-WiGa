// https://github.com/diyhue/Lights/blob/master/Arduino/Generic_ON_OFF_device/Generic_ON_OFF_device.ino

#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup_WebServer() {
  server.onNotFound(handleNotFound);

  server.on("/set", []() {
    server.send(200, "text/plain", "OK");
  });
  
  server.on("/", []() {
//    if (server.hasArg("reset")) {
//      reset(m1);
//      reset(m2);
//      reset(m3);
//    }
    if (server.hasArg("m1")) {
      if (server.arg("m1") == "down")
        move(m1, DOWN);
      else if (server.arg("m1") == "up")
        move(m1, UP);
      else if (server.arg("m1") == "stop")
        reset(m1);
    }
    if (server.hasArg("m2")) {
      if (server.arg("m2") == "down")
        move(m2, DOWN);
      else if (server.arg("m2") == "up")
        move(m2, UP);
      else if (server.arg("m2") == "stop")
        reset(m2);
    }
    if (server.hasArg("m3")) {
      if (server.arg("m3") == "down")
        move(m3, DOWN);
      else if (server.arg("m3") == "up")
        move(m3, UP);
      else if (server.arg("m3") == "stop")
        reset(m3);
    }
  
    String http_content = "<!doctype html>";
    http_content += "<html>";
    http_content += "<head>";
    http_content += "<meta charset=\"utf-8\">";
    http_content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    http_content += "<title>Wintergarten-Rollos</title>";
    http_content += "<link rel=\"stylesheet\" href=\"https://unpkg.com/purecss@0.6.2/build/pure-min.css\">";
    http_content += "</head>";
    http_content += "<body>";
    http_content += "<fieldset>";
    http_content += "<h3>Wintergarten-Rollos</h3>";
    http_content += "<form class=\"pure-form pure-form-aligned\" action=\"/\" method=\"post\">";
    
    http_content += "<div class=\"pure-control-group\">";
    http_content += "<label for=\"power\"><strong>Links</strong></label>";
    http_content += "<a class=\"pure-button";
    if (m1.state == MUP)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m1=up\">Hoch</a>";
    http_content += "<a class=\"pure-button";
    if (m1.state == STOP)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m1=stop\">Stop</a>";
    http_content += "<a class=\"pure-button";
    if (m1.state == MDOWN)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m1=down\">Runter</a>";
    http_content += "</div>";
    
    http_content += "<div class=\"pure-control-group\">";
    http_content += "<label for=\"power\"><strong>Mitte</strong></label>";
    http_content += "<a class=\"pure-button";
    if (m2.state == MUP)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m2=up\">Hoch</a>";
    http_content += "<a class=\"pure-button";
    if (m2.state == STOP)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m2=stop\">Stop</a>";
    http_content += "<a class=\"pure-button";
    if (m2.state == MDOWN)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m2=down\">Runter</a>";
    http_content += "</div>";

    http_content += "<div class=\"pure-control-group\">";
    http_content += "<label for=\"power\"><strong>Rechts</strong></label>";
    http_content += "<a class=\"pure-button";
    if (m3.state == MUP)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m3=up\">Hoch</a>";
    http_content += "<a class=\"pure-button";
    if (m3.state == STOP)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m3=stop\">Stop</a>";
    http_content += "<a class=\"pure-button";
    if (m3.state == MDOWN)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m3=down\">Runter</a>";
    http_content += "</div>";

    http_content += "<hr/>";

    http_content += "<div class=\"pure-control-group\">";
    http_content += "<label for=\"power\"><strong>Alle</strong></label>";
    http_content += "<a class=\"pure-button";
    if (m3.state == MUP)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m1=up&m2=up&m3=up\">Hoch</a>";
    http_content += "<a class=\"pure-button";
    if (m3.state == STOP)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m1=stop&m2=stop&m3=stop\">Stop</a>";
    http_content += "<a class=\"pure-button";
    if (m3.state == MDOWN)
      http_content += " pure-button-primary";
    http_content += "\" href=\"/?m1=down&m2=down&m3=down\">Runter</a>";
    http_content += "</div>";

    http_content += "</fieldset>";
    http_content += "</form>";
    http_content += "</body>";
    http_content += "</html>";
  
    server.send(200, "text/html", http_content);
  });

  server.begin();
}
