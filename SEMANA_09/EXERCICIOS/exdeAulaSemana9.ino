#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <iostream>

using namespace std;

#define SEVIDOR_ENVIO "https://ur524n-3000.preview.csb.app/teobaldo"

//Vetores com nomes de rede e senhas dos Access Points
const char* SSIDS[4]={"nome"};
const char* PWD[4]={"senha"};

void postDataToServer() {
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("https://ur524n-3000.preview.csb.app/teobaldo");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;
    // Add values in the document
    //
    String frase = "teste";
    
    String fraseCripto = frase;
    for(int i = 0; (i < frase.length()); i++) {
            frase[i] = frase[i] + 2;
            cout << "frase: ";
            cout << frase[i] << endl;
    }
    doc["nomeAluno"] = "Joao Carazzato";
    string nomeAluno = "Joao Carazzato";
    doc["turma"] = "Turma 1";
    string turma = "Turma 1";
    doc["grupo"] = "Grupo 4";
    string grupo = "Grupo 4";
    doc["mensagemEmTexto"] = fraseCripto;
    String mensagemEmTexto = fraseCripto;
    doc["mensagemCripto"] = frase;
    String mensagemCripto = frase;

    Serial.println(F("\nDados enviados:"));
    cout << nomeAluno << endl;
    cout << turma << endl;
    cout << grupo << endl;
    cout << mensagemEmTexto << endl;
    cout << mensagemCripto << endl;
     // Add an array.
    //
    JsonArray data = doc.createNestedArray("data");
     
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
     
}
void getDataFromServer() {
 
  Serial.println("Pegando dados do Servidor...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("https://ur524n-3000.preview.csb.app/teobaldo");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;
     
    int httpResponseCode = http.GET();
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
      deserializeJson(doc, response);
      int action = doc["action"];
      String sensor = doc["sensor"];
      String status1 = doc["status"];
      //Exemplo no caso de vetores/arrays no JSON
      //double latitude = doc["data"][0];
      //double longitude = doc["data"][1];
      Serial.println(action);
      Serial.println(sensor);
      Serial.println(status1);
    }
     
}
//Uma função para ler todos os dados da conexão WiFi
void DadosConexao(){
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.println("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("DNS IP: ");
  Serial.println(WiFi.dnsIP());
  Serial.println("BroadCast: ");
  Serial.println(WiFi.broadcastIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("Network ID: ");
  Serial.println(WiFi.networkID());
  Serial.println("PSK: ");
  Serial.println(WiFi.psk());
  Serial.println("BSSID: ");
  Serial.println(WiFi.BSSIDstr());
  Serial.println("RSSI: ");
  Serial.println(WiFi.RSSI());
}

//Função para um Menu de escolha cujo intuito é mostrar todas as possibilidades do Wifi.
//Conectar separadamente nos APs e depois fazer a triangulação
int menu()
{
  Serial.println(F("\nEscolha uma opção:"));
  Serial.println(F("5 - Conectar no WIFI e enviar dados para o servidor.  \n"));
  Serial.println(F("6 - Conectar no WIFI e receber dados para o servidor.  \n"));
  //fica aguardando enquanto o usuário nao enviar algum dado
  while(!Serial.available()){};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}
//Utilizado na função CONECTAR, para continuar mostrando os dados da conexão enquanto permanecer
//conectado. 
//Função para conectar em APs sem medição FTM
void EnviarDados(int rede)
{
  Serial.println("Conectando na rede: ");
  Serial.println(rede);
  WiFi.begin(SSIDS[rede],PWD[rede]);
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Tentando novamente!");
        delay(500);
      }
        Serial.println("WiFi connected");
        //DadosConexao();
        postDataToServer();      
}
void ReceberDados(int rede)
{
  Serial.println("Conectando na rede: ");
  Serial.println(rede);
  WiFi.begin(SSIDS[rede],PWD[rede]);
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Tentando novamente!");
        delay(500);
      }
        Serial.println("WiFi connected");
        //DadosConexao();
        getDataFromServer();      
}
//Função para conectar num AP sem medição FTM. Futuramente para conectar na internet e enviar 
//os dados dos sensores


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 
}

void loop() {
  int opcao = menu();
  switch(opcao)
  {
    case 5:
      opcao = 0;      
      Serial.println("Conectar na internet e enviar dados para o servidor!");
      ReceberDados(0);
      EnviarDados(0);
      Serial.println("Dados enviados!");
      break;
    case 6:
      opcao = 0;
      Serial.println("Conectar na internet e receber dados para o servidor!");
      ReceberDados(0);
      break;
    default:
      Serial.println("Opção fora do padrão!");
      break;
  }
   

}
