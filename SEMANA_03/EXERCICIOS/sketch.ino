#include <stdio.h>

int ArrayBotaoSalvar[1];
int binaryArray[4];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(14, INPUT);
  pinMode(27, OUTPUT);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  ArrayBotaoSalvar[0] = 0;
}

void numerobinario(int n) {

  // counter for binary array
  int i = 0;
  while (i < 4) {
      // storing remainder in binary array
      if (n > 0) {
      binaryArray[i] = n % 2;
      n = n / 2;
      }
      else {
        binaryArray[i] = 0;
      }
      i++;
  }

  Serial.print("Array binario: ");
  for (int j = i - 1; j >= 0; j--){
      Serial.print(binaryArray[j]);
  }
  Serial.println(" ");
  Serial.println("===========");
}

void acenderLed() {
  if (binaryArray[3] == 1) {
    digitalWrite(2, HIGH);
  }
  else {
    digitalWrite(2, LOW);
  }

  if (binaryArray[2] == 1) {
    digitalWrite(15, HIGH);
  }
  else {
    digitalWrite(15, LOW);
  }

  if (binaryArray[1] == 1) {
    digitalWrite(5, HIGH);
  }
  else {
    digitalWrite(5, LOW);
  }

  if (binaryArray[0] == 1) {
    digitalWrite(4, HIGH);
  }
  else {
    digitalWrite(4, LOW);
  }
}

void buzina(int n) {
  int i = 1;
  while (i < n) {
    tone(27, (100*n), 200);
    n = n - i;
  }
}

void loop() {

  Serial.print("Analog Read: ");
  Serial.println(analogRead(14));
  int number = analogRead(14);
  int numberDecimal = (number / 273);
  Serial.print("Number Decimal: ");
  Serial.println(numberDecimal);
  numerobinario(numberDecimal);
  acenderLed();
  buzina(numberDecimal);

  if (digitalRead(22) == LOW) {
    Serial.println("Salvando no array... ");
    ArrayBotaoSalvar[0] = numberDecimal;
    delay(250);
    Serial.print("Número: ");
    Serial.println(ArrayBotaoSalvar[0]);
  }
  else {
    Serial.println("Botao nao apertado.");
  }

  if (digitalRead(23) == LOW) {
    if (ArrayBotaoSalvar[0] != 0) {
    Serial.print("Tocando os sons do numero ");
    Serial.println(ArrayBotaoSalvar[0]);
    numerobinario(ArrayBotaoSalvar[0]);
    acenderLed();
    buzina(ArrayBotaoSalvar[0]);
    }
    else {
      Serial.println("Nao ha nenhum numero armazenado no vetor.");
    }
    delay(2500);
  }
  // put your main code here, to run repeatedly:
  delay(3000); // this speeds up the simulation
}
