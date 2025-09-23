/*****************************************************************//**
 * @file   Funcoes.c
 * @brief  Ficheiro com as funcoes do Projeto de Avalia��o
 * 
 * @author David Carvalho (27973)
 * @date   March 2024
 *********************************************************************/

#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Header.h"

#pragma region Celulas
 /// <summary>
 /// Inicializa uma variavel do tipo matriz
 /// </summary>
 /// <returns>Retorna a matriz inicializada</returns>
Matriz* InicializarCelula() {
	Matriz* aux = (Matriz*)malloc(sizeof(Matriz));
	if (aux == NULL) return NULL;

	aux->num = NULL;
	aux->direita = NULL;
	aux->baixo = NULL;
	aux->escolhido = 0;
	aux->estaRiscado = false;
	aux->estaRiscado2Vezes = false;

	return aux;
}

 /// <summary>
 /// Cria uma variavel do tipo matriz
 /// </summary>
 /// <param name="num">Numero a ser adicionada na celula</param>
 /// <returns>Retorna a matriz com o numero adicionado</returns>
Matriz* CriarCelula(int num) {
	Matriz* aux = (Matriz*)malloc(sizeof(Matriz));
	if (aux == NULL) return NULL;

	aux->num = num;
	aux->direita = NULL;
	aux->baixo = NULL;
	aux->escolhido = 0;
	aux->estaRiscado = false;
	aux->estaRiscado2Vezes = false;

	return aux;
}

/// <summary>
/// Conta o numero de celulas que uma linha possui
/// </summary>
/// <param name="linha">Matriz Linha</param>
/// <returns>Retorna o numero de celulas que a linha possui</returns>
int ContarCelulasLinha(Matriz* linha) {
	if (linha == NULL) return NULL;
	Matriz* aux = linha;

	int celulas = 0;
	while (aux != NULL) {
		aux = aux->direita;
		celulas++;
	}

	return celulas;
}

/// <summary>
/// Conta o numero de celulas que uma coluna possui
/// </summary>
/// <param name="coluna">Matriz coluna</param>
/// <returns>Retorna o numero de celulas que a coluna possui</returns>
int ContarCelulasColuna(Matriz* coluna) {
	if (coluna == NULL) return NULL;
	Matriz* aux = coluna;

	int celulas = 0;
	while (aux != NULL) {
		aux = aux->baixo;
		celulas++;
	}

	return celulas;
}

#pragma endregion 

#pragma region Linhas
/// <summary>
/// Cria uma linha de variaveis do tipo matrizes a partir de um array de inteiros
/// </summary>
/// <param name="num">Array de numeros</param>
/// <param name="t">Quantidade de numeros existentes na array</param>
/// <returns>Retorna a linha de variaveis do tipo Matriz (lista)</returns>
Matriz* CriarLinhaMatriz(int num[], int t) {	
	Matriz* inicio = CriarCelula(num[0]);
	Matriz* aux = inicio;
	for (int i = 1; i < t; i++) {
		if (i == t) break;
		aux->direita = CriarCelula(num[i]);
		aux = aux->direita;
	}

	return inicio;
}

/// <summary>
/// Cria uma linha de variaveis do tipo matrizes apartir de um inteiro
/// </summary>
/// <param name="valor">Numero</param>
/// <param name="t">Numero de celulas na linha</param>
/// <returns>Retorna a linha de variaveis do tipo Matriz (lista)</returns>
Matriz* CriarLinhaMatriz2(int valor, int t) {
	Matriz* inicio = CriarCelula(valor);
	Matriz* aux = inicio;
	for (int i = 1; i < t; i++) {
		if (i == t) break;
		aux->direita = CriarCelula(valor);
		aux = aux->direita;
	}

	return inicio;
}

/// <summary>
/// 4) Adiciona uma linha a matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="linha">Linha a ser adicionada (lista de matrizes)</param>
 /// <returns>Retorna o inicio da matriz</returns>
Matriz* AdicionarLinhaMatriz(Matriz* inicio, Matriz* linha) {
	if (linha == NULL) return NULL;

	if (inicio == NULL) inicio = linha;
	else
	{
		//Se estiver a adicionar uma linha invalida nao adiciona
		if (ControlarLinhas(inicio) != ContarCelulasLinha(linha)) return inicio;

		Matriz* auxInicio = inicio;
		Matriz* aux = linha;
		Matriz* ligaVertical = auxInicio; //Ligado a matriz 

		while (auxInicio->baixo != NULL) {
			auxInicio = auxInicio->baixo;
		}
		auxInicio->baixo = aux; //Adiciona a primeira celula � nova linha
		auxInicio = auxInicio->baixo;

		while (1) {
			if (ligaVertical->baixo == aux) { //Quando chegar � penultima linha
				while (auxInicio->direita != NULL) {
					aux = aux->direita;
					auxInicio->direita = aux; //Ligo a celula da esquerda com a celula da direita

					//Ligo a celula da penultima linha com a ultima linha
					ligaVertical = ligaVertical->direita;
					ligaVertical->baixo = aux;

					auxInicio = auxInicio->direita;
				}
				break;
			}
			ligaVertical = ligaVertical->baixo; //Anda para baixo
		}

		return inicio;
	}
}

/// <summary>
/// Conta o numero de linhas de uma matriz
/// </summary>
/// <param name="matriz">Matriz</param>
/// <returns>Retorna o numero de linhas da matriz</returns>
int ContarLinhas(Matriz* matriz) {
	if (matriz == NULL) return NULL;
	Matriz* aux = matriz;
	int linhas = 1;
	while (aux->baixo != NULL) {
		aux = aux->baixo;
		linhas++;
	}

	return linhas;
}
#pragma endregion 

#pragma region Colunas
/// <summary>
/// Cria uma coluna de variaveis do tipo matrizes apartir de um array de inteiros
/// </summary>
/// <param name="num">Array de numeros</param>
/// <param name="t">Quantidade de numeros existentes na array</param>
/// <returns>Retorna a coluna de variaveis do tipo Matriz</returns>
Matriz* CriarColunaMatriz(int num[], int t) {
	Matriz* inicio = CriarCelula(num[0]);
	Matriz* aux = inicio;
	for (int i = 1; i < t; i++) {
		if (i == t) break;
		aux->baixo = CriarCelula(num[i]);
		aux = aux->baixo;
	}

	return inicio;
}

/// <summary>
/// Cria uma coluna de variaveis do tipo matrizes apartir de um inteiro
/// </summary>
/// <param name="valor">Numero</param>
/// <param name="t">Numero de celulas na coluna</param>
/// <returns>Retorna a coluna de variaveis do tipo Matriz</returns>
Matriz* CriarColunaMatriz2(int valor, int t) {
	Matriz* inicio = CriarCelula(valor);
	Matriz* aux = inicio;
	for (int i = 1; i < t; i++) {
		if (i == t) break;
		aux->baixo = CriarCelula(valor);
		aux = aux->baixo;
	}

	return inicio;
}

/// <summary>
/// 4) Adiciona uma coluna a matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="coluna">Coluna a ser adicionada</param>
 /// <returns>Retorna o inicio da matriz</returns>
Matriz* AdicionarColunaMatriz(Matriz* inicio, Matriz* coluna) {
	if (coluna == NULL) return NULL;

	if (inicio == NULL) inicio = coluna;
	else
	{
		//Se estiver a adicionar uma coluna invalida nao adiciona
		if (ControlarColunas(inicio) != ContarCelulasColuna(coluna)) return inicio;

		Matriz* auxInicio = inicio;
		Matriz* aux = coluna;
		Matriz* ligarHorizontal = auxInicio;

		while (auxInicio->direita != NULL) {
			auxInicio = auxInicio->direita;
		}
		auxInicio->direita = aux; //Adiciona a primeira celula da coluna 

		auxInicio = auxInicio->direita; //Colocado o auxinicio na ultima posicao da linha (na celula acabada de criar)

		while (1) {
			if (ligarHorizontal->direita == aux) { //At� chegar � penultima coluna
				while (auxInicio->baixo != NULL) {
					aux = aux->baixo;
					auxInicio->baixo = aux;

					//Ligo as celulas da penultima coluna com a ultima coluna
					ligarHorizontal = ligarHorizontal->baixo;
					ligarHorizontal->direita = aux;

					auxInicio = auxInicio->baixo;
				}
				break;
			}
			ligarHorizontal = ligarHorizontal->direita;
		}

		return inicio;
	}
}

/// <summary>
/// Conta o numero de colunas de uma matriz
/// </summary>
/// <param name="matriz">Matriz</param>
/// <returns>Retorna o numero de colunas da matriz</returns>
int ContarColunas(Matriz* matriz) {
	if (matriz == NULL) return NULL;
	Matriz* aux = matriz;
	int linhas = 1;
	while (aux->direita != NULL) {
		aux = aux->direita;
		linhas++;
	}

	return linhas;
}
#pragma endregion 

#pragma region Ficheiros
/// <summary>
/// 2) Carrega para o programa a matriz dentro de um ficheiro de texto
/// </summary>
/// <param name="fileName">Nome do ficheiro</param>
/// <returns>Retorna o inicio da matriz que foi carregada</returns>
Matriz* CarregarMatriz(char fileName[]) {
	if (strlen(fileName) == 0) return NULL;
	FILE* fp = fopen(fileName, "r");
	char line[256];

	Matriz* inicio = InicializarCelula();
	Matriz* auxInicio = inicio;
	Matriz* aux = auxInicio;
	Matriz* auxLimpar = aux;

	while (fgets(line, 256, fp) != NULL) {
		char* token = strtok(line, ";");
		while (token != NULL) {
			int a = atoi(token);
			if (a == 0) break;
			aux->num = a;
			aux->direita = InicializarCelula();
			token = strtok(NULL, ";");
			aux = aux->direita;
		}
		auxInicio->baixo = InicializarCelula();
		aux = auxInicio->baixo;
		auxLimpar = auxInicio;
		auxInicio = auxInicio->baixo;
	}
	free(aux);
	auxLimpar->baixo = NULL;

	LigarMatriz(inicio);
	RemoverColuna(inicio, ContarColunas(inicio));

	return inicio;
}

/// <summary>
/// Guarda a matriz para um ficheiro de texto
/// </summary>
/// <param name="fileName">Nome do ficheiro de texto</param>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna 1 se o ficheiro for guardado e retorna 0 se nao for guardado</returns>
int GuardaMatriz(char fileName[], Matriz* inicio) {
	if (strlen(fileName) == 0) return 0;
	if (inicio == NULL) return 0;
	FILE* fp = fopen(fileName, "w");
	int a;
	Matriz* aux = inicio;
	Matriz* aux2 = inicio;
	while (aux2 !=NULL)
	{
		while (aux != NULL)
		{
			a = aux->num;
			fprintf(fp, "%d", a);
			aux = aux->direita;
			if(aux != NULL)
				fprintf(fp, ";");
		}
		fprintf(fp, "\n");
		aux2 = aux2->baixo;
		aux = aux2;
	}
	return 1;
}
#pragma endregion 

#pragma region Remover
/// <summary>
/// 5) Remove uma linha de uma matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="l">Linha a ser removida</param>
/// <returns>Retorna o inicio</returns>
Matriz* RemoverLinha(Matriz* inicio, int l) {
	if (inicio == NULL) return NULL;
	if (l == 0) return inicio;

	Matriz* auxInicio = inicio;
	Matriz* aux = auxInicio;
	Matriz* ant = aux;

	//Remove a primeira linha
	if (l == 1) {
		auxInicio = auxInicio->baixo;
		inicio = auxInicio;
		while (aux != NULL) {
			aux = aux->direita;
			free(ant);
			ant = aux;
		}
	}
	else if (l == ContarLinhas(inicio)) { //Se for a ultima linha
		for (int i = 1; i < l - 1; i++) {
			auxInicio = auxInicio->baixo;
		}
		while (auxInicio != NULL) {
			free(auxInicio->baixo);
			auxInicio->baixo = NULL;
			auxInicio = auxInicio->direita;
		}
	}
	else {
		for(int i=1; i<l-1; i++){
			auxInicio = auxInicio->baixo;
			aux = aux->baixo;
		}		
		aux = aux->baixo;

		while (auxInicio != NULL) {
			auxInicio->baixo = aux->baixo;
			free(aux);
			if (auxInicio->direita == NULL) break;
			auxInicio = auxInicio->direita;
			aux = auxInicio->baixo;
		}
	}

	return inicio;
}

/// <summary>
/// 5) Remove uma coluna de uma matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="c">Coluna a ser removida</param>
/// <returns>Retorna o inicio</returns>
Matriz* RemoverColuna(Matriz* inicio, int c) {
	if (inicio == NULL) return NULL;
	if (c == 0) return inicio;

	Matriz* auxInicio = inicio;
	Matriz* aux = auxInicio;
	Matriz* ant = aux;

	//Remove a primeira coluna
	if (c == 1) {
		auxInicio = auxInicio->direita;
		inicio = auxInicio;
		while (aux != NULL) {
			aux = aux->baixo;
			free(ant);
			ant = aux;
		}
	}
	else if (c == ContarColunas(inicio)) { //Se for a ultima linha coluna
		for (int i = 1; i < c - 1; i++) {
			auxInicio = auxInicio->direita;
			aux = aux->direita;
		}
		while (auxInicio != NULL) {
			free(auxInicio->direita);	
			auxInicio->direita = NULL;
			auxInicio = auxInicio->baixo;
		}
	}
	else {
		for (int i = 1; i < c - 1; i++) {
			auxInicio = auxInicio->direita;
			aux = aux->direita;
		}
		aux = aux->direita;
		while (aux != NULL) {
			auxInicio->direita = aux->direita;
			free(aux);
			if (auxInicio->baixo == NULL) break;
			auxInicio = auxInicio->baixo;
			aux = auxInicio->direita;
		}
	}

	return inicio;
}
#pragma endregion

#pragma region Outro
/// <summary>
/// 3) Altera��o dos inteiros constantes na matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="l">Linha da posicao</param>
/// <param name="c">Coluna da posicao</param>
/// <param name="valor">Valor que vai adicionado a posicao</param>
/// <returns>Retorna o inicio</returns>
Matriz* AlterarValorMatriz(Matriz* inicio, int l, int c, int valor){
	if (inicio == NULL) return NULL;
	if (l <= 0 || c <= 0) return inicio;

	Matriz* aux = MudarPosicaoMatriz(inicio, l, c);
	aux->num = valor;

	return inicio;
}

/// <summary>
/// Vai para uma posicao da matriz 
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="l">Linha da posicao</param>
/// <param name="c">Coluna da posicao</param>
/// <returns>Retorna a celula da matriz que esta na posicao escolhida</returns>
Matriz* MudarPosicaoMatriz(Matriz* inicio, int l, int c) {
	if (inicio == NULL) return NULL;
	if (l <= 0 || c <= 0) return inicio;

	Matriz* aux = inicio;

	for (int i = 1; i < c; i++) {
		aux = aux->direita;
	}
	for (int j = 1; j < l; j++) {
		aux = aux->baixo;
	}

	return aux;
}

/// <summary>
/// Faz a liga��o entre todas as celulas da matriz 
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o inicio</returns>
Matriz* LigarMatriz(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;
	Matriz* aux3 = aux2;

	aux2 = aux2->baixo;
	aux3 = aux3->baixo;
	while (aux3 != NULL) {
		while (aux->direita != NULL) {
			aux = aux->direita;
			aux2 = aux2->direita;
			aux->baixo = aux2;
		}
		aux = aux3;
		aux2 = aux3->baixo;
		aux3 = aux3->baixo;
	}

	return inicio;
}

int PosicaoNumero(Matriz* inicioColuna, Matriz* posicaoColuna,int num) {
	if (inicioColuna == NULL || posicaoColuna == NULL) return NULL;
	Matriz* auxInicio = inicioColuna;
	Matriz* auxPosColuna = posicaoColuna;

	int pos = 1;
	while (auxInicio != auxPosColuna) {
		auxInicio = auxInicio->baixo;
		pos++;
	}

	while (auxInicio != NULL) {
		if (auxInicio->num == 0)
			return pos;
		auxInicio = auxInicio->baixo;
		pos++;
	}

	return pos;
}
#pragma endregion

#pragma region CalcularSomaMaxima
/// <summary>
/// 7) Calcula a soma maxima possivel dos numeros presentes numa matriz.
/// Obs: Utilizado o algoritmo hungaro (https://www.hungarianalgorithm.com/index.php)
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns></returns>
int CalcularSomaMaxima(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;
	Matriz* matrizOriginal = CarregarMatriz("Matriz.txt");
	Matriz* matrizOriginal2 = matrizOriginal;

	//1�Passo: Negar todos os numeros
	NegarNumerosMatriz(aux);

	//2�Passo: Encontrar o menor valor da matriz e transformando-o em positivo
	int a = -(EncontrarMenorValorMatriz(aux));

	//3�Passo: Colocar a matriz positiva sumando a todas as celulas o valor encontrado no passo anterior
	SomarValoresMatriz(aux, a);

	//4�Passo: Fazer a matriz quadrada 
	FazerMatrizQuadarada(aux);

	//5�Passo: Subtrair a todas as linhas o numero menor dessas mesmas linhas
	int menorLinha = 0;
	int numLinhas = ContarLinhas(aux);
	for (int i = 1; i <= numLinhas; i++) {
		menorLinha = EncontrarMenorValorLinha(aux, i);
		SubtrairValorLinha(aux, menorLinha, i);
	}

	//6�Passo: Subtrair a todas as linhas o numero menor dessas mesmas linhas
	int menorColuna = 0;
	int numColunas = ContarColunas(aux);
	for (int j = 1; j <= numColunas; j++) {
		menorColuna = EncontrarMenorValorColuna(aux, j);
		SubtrairValorColuna(aux, menorColuna, j);
	}

	//7� Cobrir todos os zeros com um numero minimo de linhas
	RiscarMatriz(aux);

	//�8 Passo somar os numeros escolhidos
	int soma = 0;
	while (aux2 != NULL) {
		while (aux != NULL) {
			if (aux->escolhido == 1) {
				soma += matrizOriginal->num;
			}
			aux = aux->direita;
			matrizOriginal = matrizOriginal->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;

		matrizOriginal = matrizOriginal2->baixo;
		matrizOriginal2 = matrizOriginal2->baixo;
	}

	return soma;
}

/// <summary>
/// Nega todos os numeros dentro de uma matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o inicio com os numeros todos negados</returns>
Matriz* NegarNumerosMatriz(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;

	while (aux2 != NULL) {
		while (aux != NULL) {
			aux->num = -aux->num;
			aux = aux->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	return inicio;
}

/// <summary>
/// Soma a todas as celulas da matriz um valor 
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="valor">Valor a somar as celulas</param>
/// <returns>Retorna o inicio</returns>
Matriz* SomarValoresMatriz(Matriz* inicio, int valor) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;

	while (aux2 != NULL) {
		while (aux != NULL) {
			aux->num = aux->num + valor;
			aux = aux->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	return inicio;
}

/// <summary>
/// Soma um determinado valor as celulas da matriz que estao riscadas duas vezes
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="valor">Valor a ser somado</param>
/// <returns>Retorna o inicio da matriz</returns>
Matriz* SomarValoresMatrizRiscadoDuasVezes(Matriz* inicio, int valor) {
	if(inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;

	while (aux2 != NULL) {
		while (aux != NULL) {
			if (aux->estaRiscado2Vezes == true) {
				aux->num += valor;
			}
			aux = aux->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	return inicio;
}

/// <summary>
/// Torna a matriz quadrada adicionando 0 nas posicoes necessarias
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o inicio</returns>
Matriz* FazerMatrizQuadarada(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;

	int valor = 0;
	int linhas = ContarLinhas(aux);
	int colunas = ContarColunas(aux);
	if (colunas == linhas)
		return inicio;

	if (linhas > colunas) {
		valor = linhas - colunas; //Numero de colunas a adicionar
		for (int i = 0; i < valor; i++) {
			AdicionarColunaMatriz(aux, CriarColunaMatriz2(0, linhas));
		}
	}
	if (colunas > linhas) {
		valor = colunas - linhas; //Numero de linhas a adicionar
		for (int i = 0; i < valor; i++) {
			AdicionarLinhaMatriz(aux, CriarLinhaMatriz2(0, colunas));
		}
	}

	return inicio;
}
#pragma endregion //Conjunto de funcoes criadas para a alinea 7 (Incompleto)

#pragma region EncontrarValores
/// <summary>
/// Encontra o menor valor presente numa matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o menor valor da matriz</returns>
int EncontrarMenorValorMatriz(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;
	int menor = aux->num;

	while (aux2 != NULL) {
		while (aux != NULL) {
			if (aux->num < menor) {
				menor = aux->num;
			}
			aux = aux->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	return menor;
}

// <summary>
/// Encontra o menor valor presente numa matriz que nao esteja riscado
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o menor valor da matriz</returns>
int EncontrarMenorValorMatrizNaoRiscado(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;
	int menor = EncontrarPrimeiroValorMatrizNaoRiscado(inicio);

	while (aux2 != NULL) {
		while (aux != NULL) {
			if (aux->estaRiscado == true) {
				aux = aux->direita;
				continue;
			}
			if (aux->num < menor) {
				menor = aux->num;
			}
			aux = aux->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	return menor;
}

/// <summary>
/// Encontra o menor valor de uma linha
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="l">Linha</param>
/// <returns>Retorna o menor valor da linha</returns>
int EncontrarMenorValorLinha(Matriz* inicio, int l) {
	if (inicio == NULL) return NULL;
	if (l <= 0) return inicio;

	Matriz* aux = inicio;
	aux = MudarPosicaoMatriz(aux, l, 1); 
	
	int menor = aux->num;
	while (aux != NULL) {
		if (aux->num < menor)
			menor = aux->num;
		aux = aux->direita;
	}
	
	return menor;
}

/// <summary>
/// Encontra o menor valor de uma coluna
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="l">Coluna</param>
/// <returns>Retorna o menor valor da coluna</returns>
int EncontrarMenorValorColuna(Matriz* inicio, int c) {
	if (inicio == NULL) return NULL;
	if (c <= 0) return inicio;

	Matriz* aux = inicio;
	aux = MudarPosicaoMatriz(aux, 1, c);

	int menor = aux->num;
	while (aux != NULL) {
		if (aux->num < menor)
			menor = aux->num;
		aux = aux->baixo;
	}

	return menor;
}

/// <summary>
/// Encontra o primeiro valor da matriz que nao esta riscado
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o menor valor da matriz que nao esta riscado e retorna -1 se nao haver nenhum valor na matriz que nao esteja riscado</returns>
int EncontrarPrimeiroValorMatrizNaoRiscado(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;

	while (aux2 != NULL) {
		while (aux != NULL) {
			if (aux->estaRiscado == false)
				return aux->num;
			else
				aux = aux->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	return -1;
}


#pragma endregion

#pragma region SubtrairValores
/// <summary>
/// Subtrai um valor a todas as celulas de uma linha
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="valor">Valor para subtrair</param>
/// <param name="l">Linha</param>
/// <returns>Retorna o inicio da linha</returns>
Matriz* SubtrairValorLinha(Matriz* inicio, int valor, int l) {
	if (inicio == NULL) return NULL;
	if (l <= 0) return inicio;

	Matriz* aux = inicio;
	Matriz* aux2 = NULL;

	aux = MudarPosicaoMatriz(aux, l, 1);
	aux2 = aux;
	while (aux != NULL) {
		aux->num = aux->num - valor;
		aux = aux->direita;
	}

	return aux2;
}

/// <summary>
/// Subtrai um valor a todas as celulas de uma coluna
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="valor">Valor para subtrair</param>
/// <param name="c">Coluna</param>
/// <returns>Retorna o inicio da coluna</returns>
Matriz* SubtrairValorColuna(Matriz* inicio, int valor, int c) {
	if (inicio == NULL) return NULL;
	if (c <= 0) return inicio;

	Matriz* aux = inicio;
	Matriz* aux2 = NULL;

	aux = MudarPosicaoMatriz(aux, 1, c);
	aux2 = aux;
	while (aux != NULL) {
		aux->num = aux->num - valor;
		aux = aux->baixo;
	}

	return aux2;
}

/// <summary>
/// Subtrai um determinado valor a todas as celulas da matriz que nao estejam riscadas
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="valor">Valor a ser subtraido</param>
/// <returns>Retorna o incio da matriz</returns>
Matriz* SubtrairValoresMatrizNaoRiscado(Matriz* inicio, int valor) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;

	while (aux2 != NULL) {
		while (aux != NULL) {
			if (aux->estaRiscado == false) {
				aux->num -= valor;
			}
			aux = aux->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	return inicio;
}

#pragma endregion

#pragma region ContarNumeros
/// <summary>
/// Conta o numero de vezes que um determinado numero � encontrado numa determinada linha 
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="num">Numero a ser contado</param>
/// <param name="coluna">Linha a ser procurada o numero</param>
/// <returns>Retorna -1 se nao for possivel fazer a conta, e retorna o numero de vezes que foi encontrado o numero</returns>
int ContarNumeroLinha(Matriz* inicio, int num, int linha) {
	if (inicio == NULL) return -1;
	if (linha > ContarLinhas(inicio)) return -1;
	Matriz* aux = inicio;

	aux = MudarPosicaoMatriz(aux, linha, 1);

	int contar = 0;
	while (aux != NULL) {
		if (aux->num == num)
			contar++;	
		aux = aux->direita;
	}

	return contar;
}

/// <summary>
/// Conta o numero de vezes que um determinado numero � encontrado numa determinada coluna 
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="num">Numero a ser contado</param>
/// <param name="coluna">Coluna a ser procurada o numero</param>
/// <returns>Retorna -1 se nao for possivel fazer a conta, e retorna o numero de vezes que foi encontrado o numero</returns>
int ContarNumeroColuna(Matriz* inicio, int num, int coluna) {
	if (inicio == NULL) return -1;
	if (coluna > ContarColunas(inicio)) return -1;
	Matriz* aux = inicio;

	aux = MudarPosicaoMatriz(aux, 1, coluna);

	int contar = 0;
	while (aux != NULL) {
		if (aux->num == num)
			contar++;
		aux = aux->baixo;
	}

	return contar;
}

/// <summary>
/// Conta o numero de vezes que um determinado numero � encontrado numa determinada linha (conta apartir da posicao em que esta logo se estiver na segunda 
/// linha contara apartir da segunda linha) 
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="num">Numero a ser contado</param>
/// <returns>Retorna -1 se nao for possivel fazer a conta, e retorna o numero de vezes que foi encontrado o numero</returns>
int ContarNumeroLinha2(Matriz* inicio, int num) {
	if (inicio == NULL) return -1;
	Matriz* aux = inicio;

	int contar = 0;
	while (aux != NULL) {
		if (aux->num == num)
			contar++;
		aux = aux->direita;
	}

	return contar;
}

/// <summary>
/// Conta o numero de vezes que um determinado numero � encontrado numa determinada coluna (conta apartir da posicao em que esta logo se estiver na segunda 
/// coluna contara apartir da segunda coluna)  
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="num">Numero a ser contado</param>
/// <returns>Retorna -1 se nao for possivel fazer a conta, e retorna o numero de vezes que foi encontrado o numero</returns>
int ContarNumeroColuna2(Matriz* inicio, int num) {
	if (inicio == NULL) return -1;
	Matriz* aux = inicio;

	int contar = 0;
	while (aux != NULL) {
		if (aux->num == num)
			contar++;
		aux = aux->baixo;
	}

	return contar;
}

/// <summary>
/// Conta a quantidade de zeros escolhidos para a soma numa linha
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="linha">Linha a ser contado os zeros</param>
/// <returns>Retorna o numero de zeros encontrados</returns>
int ContarZerosEscolhidosLinha(Matriz* inicio, int linha) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;

	aux = MudarPosicaoMatriz(aux, linha, 1);

	int zeros = 0;
	while (aux != NULL) {
		if(aux->num == 0)
			if (aux->escolhido == 1)
				zeros++;

		aux = aux->direita;
	}

	return zeros;
}

/// <summary>
/// Conta a quantidade de zeros escolhidos para a soma numa coluna
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="coluna">Coluna a ser contado os zeros</param>
/// <returns>Retorna o numero de zeros encontrados</returns>
int ContarZerosEscolhidosColuna(Matriz* inicio, int coluna) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;

	aux = MudarPosicaoMatriz(aux, 1, coluna);

	int zeros = 0;
	while (aux != NULL) {
		if (aux->num == 0)
			if (aux->escolhido == 1)
				zeros++;

		aux = aux->baixo;
	}

	return zeros;
}

/// <summary>
/// Conta a quantidade de zeros escolhidos para a soma apartir de uma coluna 
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="coluna">Coluna a ser contado os zeros</param>
/// <returns>Retorna o numero de zeros encontrados</returns>
int ContarZerosEscolhidosColuna2(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;

	int zeros = 0;
	while (aux != NULL) {
		if (aux->num == 0)
			if (aux->escolhido == 1)
				zeros++;

		aux = aux->baixo;
	}

	return zeros;
}
#pragma endregion 

#pragma region RiscarMatriz
Matriz* RiscarMatriz(Matriz* inicio) { //Fazer funcao que verifique quando � para paragar e nao contar as linhas como esta
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;
	Matriz* aux3 = aux2; //Para acompanhar a posicao da coluna em cima de todo

	int linhas = ContarLinhas(aux);
	int linhasRiscadas = 0;
	while (1) {
		if (VerificarAtribuicao(aux) == 0) {
			int pos = 1;
			inicio = ResetarRiscos(inicio);
			while (aux->baixo != NULL) {
				int numLinhas = ContarNumeroLinha2(aux, 0);
				int numColunas = ContarNumeroColuna2(aux, 0);

				if (numLinhas > numColunas) {
					RiscarLinha(aux2, pos);
					linhasRiscadas++;
				}
				if (numLinhas < numColunas) {
					if (numColunas == 1) {
						int pos2 = PosicaoNumero(aux3, aux, 0);
						RiscarLinha(aux2, pos2);
						linhasRiscadas++;
					}
					else
						RiscarColuna(aux2, pos);
				}

				if(numLinhas == numColunas)
					 RiscarLinha(aux2, pos);

				pos++;
				aux = aux->baixo; //Mudar de linha
				aux = aux->direita;
				aux3 = aux3->direita;
			}
			aux = inicio;
			aux2 = aux;
			aux3 = aux2;
			int valorAux = EncontrarMenorValorMatrizNaoRiscado(aux3);
			aux3 = SubtrairValoresMatrizNaoRiscado(aux3, valorAux);
			aux3 = SomarValoresMatrizRiscadoDuasVezes(aux3, valorAux);
		}
		else {
			aux = AplicarAtribuicaoIdeal(aux);
			break;
		}
	}

	return inicio;
}

Matriz* AplicarAtribuicaoIdeal(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;
	Matriz* aux3 = aux2;

	//Verificar Linhas
	int numerosEscolhidos = 0;
	int linhas = ContarLinhas(aux);
	for (int i = 1; i <= linhas; i++) {
		if (ContarNumeroLinha(inicio, 0, i) == 0) {
			return NULL; //Tem que ter  pelo menos um 0
		}
		if (ContarNumeroLinha(inicio, 0, i) == 1) {
			while (aux != NULL) {
				if (aux->num == 0) {
					aux->escolhido = 1;
					numerosEscolhidos++;
				}
				aux = aux->direita;
				if (aux->direita == NULL) {
					aux = aux2->baixo;
					aux2 = aux2->baixo;
					break;
				}
			}
		}
		else {
			aux = aux2->baixo;
			aux2 = aux2->baixo;
			continue;
		}
	}

	aux = inicio;
	aux2 = aux;

	//VerificarColunas
	int colunas = ContarColunas(aux);
	for (int c = 1; c <= colunas; c++) {
		if (ContarNumeroColuna(inicio, 0, c) == 0) {
			return NULL;
		}

		if (ContarNumeroColuna(inicio, 0, c) == 1) {
			while (aux != NULL) {
				if (aux->num == 0) {
					aux->escolhido = 1;
					numerosEscolhidos++;
				}
				aux = aux->baixo;
				if (aux->baixo == NULL) {
					aux = aux2->direita;
					aux2 = aux2->direita;
					break;
				}
			}
		}
		else {
			aux = aux2->direita;
			aux2 = aux2->direita;
			continue;
		}
	}

	aux = inicio;
	aux2 = aux;

	//Ultima Fase
	for (int l = 1; l <= linhas; l++) {
		if (ContarZerosEscolhidosLinha(inicio, l) == 0) {
			while (aux != NULL) {
				if (ContarZerosEscolhidosColuna2(aux3) == 0) {
					aux->escolhido = true;
					numerosEscolhidos++;
				}
				else {
					aux = aux->direita;
					aux3 = aux3->direita;
				}
					
			}
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	if (numerosEscolhidos == linhas)
		return inicio;
	else
		return NULL;
}

/// <summary>
/// Verifica se ainda � preciso riscar a matriz para encontrar os valores para a soma maxima
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna 0 se ainda � preciso riscar a matriz e retorna 1 se ja nao � preciso riscar a matriz</returns>
int VerificarAtribuicao(Matriz* inicio) {
	if (inicio == NULL) return 0;
	Matriz* aux = inicio;

	int auxPos = 1;
	int qntZeros = 0;
	int linhas = ContarLinhas(inicio);
	int colunas = ContarColunas(inicio);

	//Verifica Linhas
	for (int c = 1; c <= colunas; c++) {
		aux = MudarPosicaoMatriz(aux, 1, c);
		qntZeros = 0;
		if (ContarNumeroColuna(inicio, 0, c) > 1) {
			while (aux != NULL) {
				if (aux->num == 0) {
					if(ContarNumeroLinha(inicio, 0, auxPos) == 1)
						qntZeros++;

					if (qntZeros > 1)
						return 0;
				}
				aux = aux->baixo;
				auxPos++;
			}
		}
	}

	aux = inicio;
	auxPos = 1;
	qntZeros = 0;

	//Verifica Colunas 
	for (int l = 1; l <= colunas; l++) {
		aux = MudarPosicaoMatriz(aux, l, 1);
		qntZeros = 0;
		if (ContarNumeroLinha(inicio, 0, l) > 1) {
			while (aux != NULL) {
				if (aux->num == 0) {
					if (ContarNumeroColuna(inicio, 0, auxPos) == 1)
						qntZeros++;

					if (qntZeros > 1)
						return 0;
				}
				aux = aux->direita;
				auxPos++;
			}
		}
	}

	return 1;
}


/// <summary>
/// Riscar uma linha de uma matriz (mudando o valor da variavel estaRiscado para verdadeiro em todas as celulas da linha)
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="linha">Linha a ser riscada</param>
/// <returns>Retorna null se nao for possivel riscar a linha e retorna o incicio da matriz se a linha foi riscada</returns>
Matriz* RiscarLinha(Matriz* inicio, int linha) {
	if (inicio == NULL) return NULL;
	if (linha > ContarLinhas(inicio)) return NULL;
	Matriz* aux = inicio;

	aux = MudarPosicaoMatriz(aux, linha, 1);

	while (aux != NULL) {
		if (aux->estaRiscado == true) {
			aux->estaRiscado2Vezes = true;
		}
		else
			aux->estaRiscado = true;

		aux = aux->direita;
	}

	return inicio;
}

/// <summary>
/// Riscar uma coluna de uma matriz (mudando o valor da variavel estaRiscado para verdadeiro em todas as celulas da coluna)
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="coluna">Coluna a ser riscada</param>
/// <returns>Retorna null se nao for possivel riscar a coluna e retorna o incicio da matriz se a coluna foi riscada</returns>
Matriz* RiscarColuna(Matriz* inicio, int coluna) {
	if (inicio == NULL) return NULL;
	if (coluna > ContarColunas(inicio)) return NULL;
	Matriz* aux = inicio;

	aux = MudarPosicaoMatriz(aux, 1, coluna);

	while (aux != NULL) {
		if (aux->estaRiscado == true) {
			aux->estaRiscado2Vezes = true;
		}
		else
			aux->estaRiscado = true;

		aux = aux->baixo;
	}

	return inicio;
}

/// <summary>
/// Riscar uma linha de uma matriz (mudando o valor da variavel estaRiscado para verdadeiro em todas as celulas da linha)
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="linha">Linha a ser riscada</param>
/// <returns>Retorna null se nao for possivel riscar a linha e retorna o incicio da matriz se a linha foi riscada</returns>
Matriz* RiscarLinha2(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;

	while (aux != NULL) {
		aux->estaRiscado = true;
		aux = aux->direita;
	}

	return inicio;
}


/// <summary>
/// Riscar uma coluna de uma matriz (mudando o valor da variavel estaRiscado para verdadeiro em todas as celulas da coluna)
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="coluna">Coluna a ser riscada</param>
/// <returns>Retorna null se nao for possivel riscar a coluna e retorna o incicio da matriz se a coluna foi riscada</returns>
Matriz* RiscarColuna2(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;

	while (aux != NULL) {
		aux->estaRiscado = true;
		aux = aux->baixo;
	}

	return inicio;
}

/// <summary>
/// Retira todos os riscos da matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o inicio da matriz</returns>
Matriz* ResetarRiscos(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;
	Matriz* aux2 = aux;

	while (aux2 != NULL) {
		while(aux != NULL){
			aux->estaRiscado = false;
			aux->estaRiscado2Vezes = false;
			aux = aux->direita;
		}
		aux = aux2->baixo;
		aux2 = aux2->baixo;
	}

	return inicio;
}
#pragma endregion

#pragma region Controlo
/// <summary>
/// Controla o tamanho que uma linha pode ter para ser adicionada a uma matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o numero de celulas que a linha tem que ter</returns>
int ControlarLinhas(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;

	int colunas = ContarColunas(aux);

	return colunas;
}

/// <summary>
/// Controla o tamanho que uma coluna pode ter para ser adicionada a uma matriz
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna o numero de celulas que a coluna tem que ter</returns>
int ControlarColunas(Matriz* inicio) {
	if (inicio == NULL) return NULL;
	Matriz* aux = inicio;

	int linhas = ContarLinhas(aux);

	return linhas;
}
#pragma endregion

#pragma region Mostrar
/// <summary>
/// Funcao que mostra uma celula da matriz
/// </summary>
/// <param name="matriz">Matriz</param>
/// <returns>Retorna 1 se for mostrada e retorna 0 se a matriz for nula</returns>
int MostrarMatriz(Matriz* matriz) {
	if (matriz == NULL) return 0;

	printf("%d\t", matriz->num);

	return 1;
}

/// <summary>
/// 6) Funcao que mostra uma matriz completa (linhas e colunas)
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <returns>Retorna 1 se for mostrada e retorna 0 se a matriz for nula</returns>
int MostrarMatrizTotal(Matriz* inicio) {
	if (inicio == NULL) return 0;

	Matriz* auxDireita = inicio;
	Matriz* auxBaixo = auxDireita;

	while (auxBaixo != NULL) {
		while (auxDireita != NULL) {
			MostrarMatriz(auxDireita);
			auxDireita = auxDireita->direita;
		}
		printf("\n");
		auxBaixo = auxBaixo->baixo;
		auxDireita = auxBaixo;
	}

	return 1;
}
#pragma endregion 

#pragma region NaoUtilizadoPeloTrabalho
/// <summary>
/// Adiciona uma variavel do tipo matriz no inicio da lista de matrizes
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="matriz">Matriz a ser adicionada</param>
/// <returns>Retorna o inicio da matriz</returns>
Matriz* AdicionarCelulaInicio(Matriz* inicio, Matriz* matriz) {
	if (matriz == NULL) return inicio;

	if (inicio == NULL)
		inicio = matriz;
	else {
		matriz->direita = inicio;
		inicio = matriz;
	}

	return inicio;
}

/// <summary>
/// Adiciona uma variavel do tipo matriz na posicao final da lista de matrizes
/// </summary>
/// <param name="inicio">Inicio da matriz</param>
/// <param name="matriz">Matriz a ser adicionada</param>
/// <returns>Retorna o inicio da matriz</returns>
Matriz* AdicionarCelulaFim(Matriz* inicio, Matriz* matriz) {
	if (matriz == NULL) return NULL;

	if (inicio == NULL)
		inicio = matriz;
	else {
		Matriz* aux = inicio;

		while (aux != NULL) {
			if (aux->direita == NULL) {
				aux->direita = matriz;
				break;
			}
			aux = aux->direita;
		}
	}

	return inicio;
}
#pragma endregion //Funcoes que foram feitas mas nao t�m nenhum peso no trabalho 



