#include <iostream>
#include <fstream> 
using namespace std;


int tamanhoMatriz(char *arquivo)
{
	int n;
	ifstream file(arquivo);
	file >> n;
	return n;
}

int popularMatriz( char *arquivo, int n, void *x)
{
	// conversão para matriz de inteiros 
	int (*matriz)[n] = static_cast<int (*)[n]>(x);

	int l;
	ifstream file(arquivo);
	file >> l;

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int valor;

			file >> valor;
				matriz[i][j] = valor;
				matriz[j][i] = valor;

			
		}
	}
}
