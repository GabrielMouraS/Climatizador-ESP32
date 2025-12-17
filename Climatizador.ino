#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const char* ssid = "Climatizador";
const char* password = "12345678";

const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

// Pinos dos relés 1,2,3,4,5,6
const int relePins[6] = {25, 26, 27, 32, 14, 33};

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body { font-family: sans-serif; text-align: center; margin-top: 40px; background: #f0f0f0; }
        h1 { color: #333; }
        .button {
          padding: 15px 30px;
          margin: 10px;
          font-size: 18px;
          border: none;
          border-radius: 5px;
          cursor: pointer;
        }
        .on { background-color: #4CAF50; color: white; }
        .off { background-color: #f44336; color: white; }
      </style>
    </head>
    <body>
      <h1>Controle de Relés</h1>
  )rawliteral";

  for (int i = 0; i < 6; i++) {
    html += "<p>Relé " + String(i + 1) + "</p>";
    html += "<a href=\"/on?r=" + String(i) + "\"><button class=\"button on\">Ligar</button></a>";
    html += "<a href=\"/off?r=" + String(i) + "\"><button class=\"button off\">Desligar</button></a><hr>";
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  int r = server.arg("r").toInt();
  if (r >= 0 && r < 6) {
    digitalWrite(relePins[r], LOW); // Ativa o relé
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  int r = server.arg("r").toInt();
  if (r >= 0 && r < 6) {
    digitalWrite(relePins[r], HIGH); // Desativa o relé
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  // Inicializa os pinos dos relés
  for (int i = 0; i < 6; i++) {
    pinMode(relePins[i], OUTPUT);
    digitalWrite(relePins[i], HIGH); // Relé desligado inicialmente
  }

  // Modo Access Point
  WiFi.softAP(ssid, password);
  delay(100);

  // Configura o portal cativo (DNS redirecionando tudo para o IP da ESP32)
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // Rotas
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.onNotFound(handleRoot); 

  server.begin();

  Serial.println("Acesse: http://" + WiFi.softAPIP().toString());
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
