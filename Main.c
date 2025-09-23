/*****************************************************************//**
 * \file   Main.c
 * \brief  Ficheiro Main do Projeto de Avaliação
 * 
 * \author David Carvalho (27973)
 * \date   March 2024
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {

	Matriz* inicio = NULL;

	Matriz* linha1 = NULL;
	Matriz* coluna1 = NULL;

	//Linhas
	int num1[4] = { 1 ,2 ,3 ,4};
	//Colunas
	int numC1[3] = { 10 ,11, 5};
	int numC2[3] = { 20, 69, 3};
	
	#pragma region CriarLinhasColunas
	//inicio = CriarLinhaMatriz(num1, 4); //Cria Linha

	//linha1 = CriarLinhaMatriz(num1, 4); //Cria Linha

	inicio = AdicionarLinhaMatriz(inicio, linha1); //Adiciona Linha
	//linha1 = CriarLinhaMatriz(num1, 4); //Volta a criar Linha
	//inicio = AdicionarLinhaMatriz(inicio, linha1); //Adiciona Linha

	//coluna1 = CriarColunaMatriz(numC2, 3); //Cria Coluna
	//inicio = AdicionarColunaMatriz(inicio, coluna1);
#pragma endregion

	#pragma region Remover
	//inicio = RemoverLinha(inicio, 2);
	//inicio = RemoverColuna(inicio, 5);
	#pragma endregion

	inicio = CarregarMatriz("Matriz.txt");

	//GuardaMatriz("Matriz.txt", inicio);

	MostrarMatrizTotal(inicio);

	printf("\nLinhas: %d\n", ContarLinhas(inicio));
	printf("Colunas: %d\n", ContarColunas(inicio));
	printf("Soma maxima total: %d\n", CalcularSomaMaxima(inicio));
}
