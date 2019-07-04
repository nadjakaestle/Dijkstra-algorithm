#include <iostream>
#include <fstream>
#include "dijasktra.hpp"

#define ENTRADA "dij10.txt"

int main()
{
	int n = tamanhoMatriz(ENTRADA);

	int matriz[n][n] = {{0}};

	printf("Tamanho da matriz: %d\n", n);

	popularMatriz(ENTRADA, n, matriz);	
	 
	dijkstra(matriz, n, 0);
	
	return 0;
}