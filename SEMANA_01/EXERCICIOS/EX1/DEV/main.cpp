#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>

using namespace std;

// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente 
// entre dois valores mínimo e máximo e retorna esse valor
float converteSensor(int medida, int valorminimo, int valormaximo){

	float resposta;
	medida = medida - valorminimo;
	valormaximo = valormaximo - valorminimo;
	resposta = (medida * 100)/valormaximo;
	return resposta;
}
// 2 - Faça uma função que simule a leitura de um sensor lendo o 
// valor do teclado ao final a função retorna este valor
int tecla() {
	int retorno;
	printf("Digite a distancia para ser retornada...\n");
	cin >> retorno;
    return retorno;
}
// 3 - Faça uma função que armazena uma medida inteira qualquer 
// em um vetor fornecido. Note que como C não possui vetores 
// nativos da linguagem, lembre-se que você precisa passar o 
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em 
// uma área de memória fora do vetor

int vetorArmazenado(int medida, int *vetorMov, int maxVetor, int posAtualVetor) {
	if (posAtualVetor < maxVetor) {
	    vetorMov[posAtualVetor] = medida;
	    return posAtualVetor + 1;
	}
	return posAtualVetor;
}


// 4 - Faça uma função que recebe um vetor com 4 posições que contém 
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção 
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a 
// segunda é esta maior distância.

char* direcaoMaiorCaminho(int *vetor, int *distancia) {
 
    int maior_v = vetor[0];
    int maior_i = 0;
    for(int i = 1; i < 4; i++) {
        if (maior_v < vetor[i]) {
            maior_v = vetor[i];
            maior_i = i;
        }
    }
    *distancia = maior_v;
    
    switch (maior_i) {
     case 0:
        return (char*)"Direita";
     case 1:
        return (char*)"Esquerda";
     case 2:
        return (char*)"Frente";
     case 3:
        return (char*)"Tras";
    }
}


// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e 
// retorna verdadeiro ou falso

int leComando() {
    string resposta;
    printf("Voce deseja continuar o mapeamento? s/n: ");
    cin >> resposta;
    if (resposta == "s") {
        return 1;
    }
    else {
        return 0;
    }
    
}

// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô 
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", 
// "Frente", "Tras"). 
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno 
// para uma movimentação futura. 
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro 
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado 
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas 
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja 
// enviado pelo usuário. 
//
//      Complete a função com a chamada das funções já criadas
 int dirige(int *v,int maxv){
 	int maxVetor = maxv;
 	int *vetorMov = v;
 	int posAtualVetor = 0;
 	int dirigindo = 1;		
 	while(dirigindo){		
 		int medidaDireita = tecla(); /// .. Chame a função de de leitura da medida para a "Direita"
 		medidaDireita = converteSensor(medidaDireita,0,830);
 		posAtualVetor = vetorArmazenado(medidaDireita, vetorMov, maxVetor, posAtualVetor);
 		
 		int medidaEsquerda = tecla(); /// .. Chame a função de de leitura da medida para a "Esquerda"
 		medidaEsquerda = converteSensor(medidaEsquerda,0,830);
 		posAtualVetor = vetorArmazenado(medidaEsquerda, vetorMov, maxVetor, posAtualVetor);// Chame a função para armazenar a medida no vetor
 		
 		int medidaFrente = tecla(); /// .. Chame a função de de leitura da medida para a "Frente"
 		medidaFrente = converteSensor(medidaFrente,0,830);
 		posAtualVetor = vetorArmazenado(medidaFrente, vetorMov, maxVetor, posAtualVetor);// Chame a função para armazenar a medida no vetor
 		
 		int medidaTras = tecla(); /// .. Chame a função de de leitura da medida para a "Tras"
 		medidaTras = converteSensor(medidaTras,0,830);
 		posAtualVetor = vetorArmazenado(medidaTras, vetorMov, maxVetor, posAtualVetor);// Chame a função para armazenar a medida no vetor
 		
 		dirigindo = leComando();		
 	}
 	return posAtualVetor;
 }


// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado 
// na maior distância a cada movimento
void percorre(int *v,int tamPercorrido){		
  int *vetorMov = v;
 	int maiorDir = 0;
	
 	for(int i = 0; i< tamPercorrido; i+=4){
 		char *direcao = direcaoMaiorCaminho(&(vetorMov[i]),&maiorDir);
 		printf("Movimentando para %s com distancia de  %i.\n",direcao,maiorDir);
 	}
 }

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;

	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}