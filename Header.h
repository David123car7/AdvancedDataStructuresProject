/*****************************************************************//**
 * \file   Header.h
 * \brief  Ficheiro cabeçalho do Projeto de Avaliação
 * 
 * \author David Carvalho (27973)
 * \date   March 2024
 *********************************************************************/

#pragma once

#include <stdbool.h>

/// <summary>
/// int num: Numero inteiro da matriz
///  Matriz* direita: Apontador do tipo matriz que serve para apontar a direita
///  Matriz* baixo: Apontador do tipo matriz que serve para apontar baixo
///  int escolhido: Se for 1 é o numero escolhido para a soma, se for 0 é porque ainda nao se sabe se pode ser escolhido e se for -1 nao pode ser escolhido
///	 bool estaRiscado: Variavel booleana que determina se a celula da matriz esta riscada ou nao
///  bool estaRiscado2Vezes: Variavel booleana que determina se a celula da matriz esta riscada duasvezes ou nao
/// </summary>
typedef struct Matriz{
	int num; 
	struct Matriz* direita;
	struct Matriz* baixo;
	int escolhido; 
	bool estaRiscado;
	bool estaRiscado2Vezes;
}Matriz;

#pragma region Celulas
Matriz* CriarCelula(int num);
Matriz* AdicionarCelulaInicio(Matriz* inicio, Matriz* matriz);
Matriz* AdicionarCelulaFim(Matriz* inicio, Matriz* matriz);
int ContarCelulasLinha(Matriz* linha);
int ContarCelulasColuna(Matriz* coluna);
#pragma endregion

#pragma region Linhas
Matriz* CriarLinhaMatriz(int num[], int t);
Matriz* CriarLinhaMatriz2(int valor, int t);
Matriz* AdicionarLinhaMatriz(Matriz* inicio, Matriz* linha);
int ContarLinhas(Matriz* matriz);
#pragma endregion

#pragma region Colunas
Matriz* CriarColunaMatriz(int num[], int t);
Matriz* CriarColunaMatriz2(int valor, int t);
Matriz* AdicionarColunaMatriz(Matriz* inicio, Matriz* coluna);
int ContarColunas(Matriz* matriz);
#pragma endregion

#pragma region Mostrar
int MostrarMatrizTotal(Matriz* inicio);
#pragma endregion

#pragma region Ficheiros
Matriz* CarregarMatriz(char fileName[]);
int GuardaMatriz(char fileName[], Matriz* inicio);
#pragma endregion

#pragma region Remover
Matriz* RemoverLinha(Matriz* inicio, int l);
Matriz* RemoverColuna(Matriz* inicio, int c);
#pragma endregion

#pragma region CalcularSomaMaxima
int CalcularSomaMaxima(Matriz* inicio);
Matriz* NegarNumerosMatriz(Matriz* inicio);
Matriz* SomarValoresMatriz(Matriz* inicio, int valor);
Matriz* SomarValoresMatrizRiscadoDuasVezes(Matriz* inicio, int valor);
Matriz* FazerMatrizQuadarada(Matriz* inicio);
#pragma endregion

#pragma region Verificacoes
Matriz* AplicarAtribuicaoIdeal(Matriz* inicio);
int VerificarAtribuicao(Matriz* inicio);
#pragma endregion

#pragma region EncontrarMenorValor
int EncontrarMenorValorMatriz(Matriz* inicio);
int EncontrarMenorValorMatrizNaoRiscado(Matriz* inicio);
int EncontrarMenorValorLinha(Matriz* inicio, int l);
int EncontrarMenorValorColuna(Matriz* inicio, int c);
int EncontrarPrimeiroValorMatrizNaoRiscado(Matriz* inicio);
#pragma endregion

#pragma region SubtrairValores
Matriz* SubtrairValorLinha(Matriz* inicio, int valor, int l);
Matriz* SubtrairValorColuna(Matriz* inicio, int valor, int c);
Matriz* SubtrairValoresMatrizNaoRiscado(Matriz* inicio, int valor);
#pragma endregion

#pragma region ContarNumeros
int ContarNumeroLinha(Matriz* inicio, int num, int linha);
int ContarNumeroLinha2(Matriz* inicio, int num);
int ContarNumeroColuna(Matriz* inicio, int num, int coluna);    
int ContarNumeroColuna2(Matriz* inicio, int num);
int ContarZerosEscolhidosLinha(Matriz* inicio, int linha);
int ContarZerosEscolhidosColuna(Matriz* inicio, int coluna);
int ContarZerosEscolhidosColuna2(Matriz* inicio);
#pragma endregion

#pragma region RiscarMatriz
Matriz* RiscarMatriz(Matriz* inicio);
Matriz* RiscarLinha(Matriz* inicio, int linha);
Matriz* RiscarLinha2(Matriz* inicio);
Matriz* RiscarColuna(Matriz* inicio, int coluna);
Matriz* RiscarColuna2(Matriz* inicio);
Matriz* ResetarRiscos(Matriz* inicio);
#pragma endregion

#pragma region Controlo
int ControlarLinhas(Matriz* inicio);
#pragma endregion

#pragma region Outro
Matriz* AlterarValorMatriz(Matriz* inicio, int l, int c, int valor);
Matriz* LigarMatriz(Matriz* inicio);
Matriz* MudarPosicaoMatriz(Matriz* inicio, int l, int c);
int PosicaoNumero(Matriz* inicioColuna, Matriz* posicaoColuna, int num);
#pragma endregion
