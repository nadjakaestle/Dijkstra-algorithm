#include <iostream>
#include <fstream>
using namespace std;

typedef struct vertice
{
	int *A;
} Vertice;

int tamanhoMatriz(char *arquivo)
{
	int n;
	ifstream file(arquivo);
	file >> n;
	return n;
}

int popularMatriz(char *arquivo, int n, void *x)
{
	// conversão para matriz de inteiros
	int(*matriz)[n] = static_cast<int(*)[n]>(x);

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

int filhoEsquerda(int i)
{
	return 2 * i + 1;
}

int filhoDireita(int i)
{
	return 2 * i + 2;
};

void minHeapify(Vertice *arr, int i, int tamanho_heap)
{
	int esquerda = filhoEsquerda(i);
	int direita = filhoDireita(i);
	int menor;
	int trocar;

	if ((esquerda <= tamanho_heap) && (arr->A[esquerda] < arr->A[i]))
	{
		menor = esquerda;
	}
	else
		menor = i;

	if ((direita <= tamanho_heap) && (arr->A[direita] < arr->A[menor]))
	{
		menor = direita;
	}
	if (menor != i)
	{
		trocar = arr->A[i];
		arr->A[i] = arr->A[menor];
		arr->A[menor] = trocar;

		minHeapify(arr, menor, tamanho_heap);
	}
}
void build_min_Heap(Vertice arr[], int tamanho_heap)
{
	for (int i = (tamanho_heap-1) / 2; i >= 0; i--)
		minHeapify(arr, i, tamanho_heap-1);
}
