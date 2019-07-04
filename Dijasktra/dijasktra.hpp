#include <iostream>
#include <fstream>
using namespace std;

#define INFINITO 2147483647; //valor maximo para uma variavel do tipo int

typedef struct vertice
{
	int A;
	int id;
	int paiID;
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

Vertice extrairMin(Vertice arr[], int *tamanho_heap)
{
	vertice minimo = arr[0];
	arr[0] = arr[*tamanho_heap - 1];
	*tamanho_heap = *tamanho_heap - 1;
	minHeapify(arr, 0, *tamanho_heap);

	return minimo;
}

bool fila(int id, vertice arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (id == arr[i].id)
			return true;
	}
	return false;
}
vertice retornaVertice(int id, vertice arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (id == arr[i].id)
			return arr[id];
	}
	return arr[id];
}

void relax(vertice arr[], int id, int A, int n, int idPai, int APai)

{
	for (int j = 0; j < n; j++)
	{
		if (id == arr[j].id)
		{
			id = j;
			break;
		}
	}
	arr[id].A = A + APai;
	arr[id].paiID = idPai;
	while ((id > 0) && (arr[(id - 1) / 2].A > arr[id].A))
	{

		vertice trocar;
		trocar = arr[(id - 1) / 2];
		arr[(id - 1) / 2] = arr[id];
		arr[id] = trocar;
		id = (id - 1) / 2;
	}
}

void dijkstra(void *x, int n, int inicio)
{
	// conversão para matriz de inteiros
	int(*matriz)[n] = static_cast<int(*)[n]>(x);

	Vertice V[n];

	//seta distancias desconhecidas para infinito
	for (int i = 0; i < n; i++)
	{
		V[i].A = INFINITO;
		V[i].id = i;
		V[i].paiID = -1;
	}
	//distancia do vertice inicial pra ele mesmo é 0
	V[inicio].A = 0;

	//inicia nó na fila de prioridade
	Vertice Q[n];
	for (int i = 0; i < n; i++)
	{
		Q[i] = V[i];
	}

	build_min_Heap(Q, n);

	/* for (int i = 0; i < n; i++)
	{
		printf("ordenação %d , chave: %d\n", Q[i].id,Q[i].A);
	}*/

	// verifica se a fila de prioriadade não está vazia
	int aux = n;
	while (n > 0)
	{
		Vertice u = extrairMin(Q, &n);
		V[u.id] = u;
		for (int i = 0; i < aux; i++)
		{
			// Se i for adjacente
			if (matriz[u.id][i] != 0)
			{
				if ((fila(i, Q, n)) && (matriz[u.id][i] + u.A < retornaVertice(i, Q, n).A))
				{
					relax(Q, i, matriz[u.id][i], n, u.id, u.A);
				}
			}
		}
	}

	std::cout << "\nverticeID: " << V[aux - 1].id << " ;paiID: " << V[aux - 1].paiID << " ;A: " << V[aux - 1].A << std::endl;
}
