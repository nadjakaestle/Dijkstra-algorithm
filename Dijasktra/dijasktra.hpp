#include <iostream>
#include <fstream>
using namespace std;

#define INFINITO 214748364;

typedef struct vertice
{
	int A;
	int id;
	int proximoID;
	bool included;
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
	Vertice trocar;

	if ((esquerda <= tamanho_heap) && (arr[esquerda].A < arr[i].A))
	{
		menor = esquerda;
	}
	else
		menor = i;

	if ((direita <= tamanho_heap) && (arr[direita].A < arr[menor].A))
	{
		menor = direita;
	}
	if (menor != i)
	{
		trocar = arr[i];
		arr[i] = arr[menor];
		arr[menor] = trocar;

		minHeapify(arr, menor, tamanho_heap);
	}
}
void build_min_Heap(Vertice arr[], int tamanho_heap)
{
	for (int i = (tamanho_heap - 1) / 2; i >= 0; i--)
		minHeapify(arr, i, tamanho_heap - 1);
}

void dijkstra(void *x, int n, int inicio)
{
	// conversão para matriz de inteiros
	int(*matriz)[n] = static_cast<int(*)[n]>(x);

	Vertice V[n];

	//seta distancias para infinito
	for (int i = 0; i < n; i++)
	{
		V[i].A = INFINITO;
		V[i].id = i;
		V[i].proximoID = -1;
	}
	V[inicio].A = 0;
	V[inicio].included = true;
	//inicia nó na fila de prioridade
	Vertice Q[n];
	
	for (int i = 0; i < n; i++)
	{
		Q[i] = V[i];
		
	}

	build_min_Heap(Q, n);

	/* for (int i = 0; i < n; i++)
	{
		printf("ordenação v %d , chave: %d\n", Q[i].id,Q[i].A);
	}*/
}
