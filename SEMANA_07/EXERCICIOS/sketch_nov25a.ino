#include <WiFi.h>

#define LED 35
#define LED1 36
#define LED2 13
#define LED3 12

const char *ssid = "rede";
const char *password = "senha";

int posicao = 3;

WiFiServer server(80);

void led_wifi();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  delay(4000);
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Nao Conectado.");
  }

  Serial.println("");
  Serial.println("Conectado ao WiFi!");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  while(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.print(".");

    delay(500);
  }

  led_wifi();

  switch(posicao) {
    case 1:
    digitalWrite(LED, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(300);
    digitalWrite(LED, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    ESP.restart();
    break;

    case 2:
    digitalWrite(LED, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    break;

    case 3:
    digitalWrite(LED, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    break;

    case 4:
    digitalWrite(LED, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    break;

    case 5:
    digitalWrite(LED, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    delay(300);
    digitalWrite(LED, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    ESP.restart();
    break;
  }
}

void led_wifi() {
  WiFiClient client = server.available();

  if(client) {
    Serial.println("Cliente Detectado!");
    String currentLine = "";
    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        Serial.write(c);
        if(c=='\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Clique <a href=\"/H1\">AQUI</a> Jogador 1</h2><br>");
            client.print("<h2>Clique <a href =\"/L1\"> AQUI</a> Jogador 2</h2></br>");
            client.println();
          break;
          }
          else currentLine="";
        }

        else if(c != '\r') currentLine += c;

        if(currentLine.endsWith("GET /H1")) posicao = posicao - 1;
        if(currentLine.endsWith("GET /L1")) posicao = posicao + 1;
      }
    }
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}