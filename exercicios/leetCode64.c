#include <stdio.h>
#include <stdlib.h>
#define INF 201

typedef struct Edge edge;
struct Edge 
{
    int weight;
    int destiny;
    edge *prox;
};

typedef struct Node node;
struct Node
{
    edge *edges;
};

void addNode(int source, int destiny, int weight, node *nodes)
{   
    edge *new = malloc(sizeof(edge));
    new -> destiny = destiny;
    new -> weight = weight;

    new -> prox = nodes[source].edges;
    nodes[source].edges = new;
}

int minCost(node *nodes, int currentNode, int **matriz, int currentRow, int qtdNodes, int lastNodeWeight)
{   
    int menor = matriz[currentRow - 1][currentNode];
    for(edge *aux = nodes[currentNode].edges; aux != NULL; aux = aux -> prox) // Pecorre os vizinhos
    {   
        // Encontra o menor valor para aquela célula anlisando os pesos e os valores dos vizinhos na matriz
        int sumTemp =  aux -> weight + matriz[currentRow - 1][aux -> destiny];

        // if(aux -> destiny == qtdNodes - 1)
        //     sumTemp += lastNodeWeight;

        if( sumTemp < menor)
            menor = sumTemp;
    }

    return menor;
}

void bellmanFord(node *nodes, int qtdNodes, int **matriz, int lastNodeWeight)
{
    for(int i = 1; i < qtdNodes; i++)
    {   
        for(int j = 0; j < qtdNodes; j++)
        {
            matriz[i][j] = minCost(nodes,j, matriz, i, qtdNodes, lastNodeWeight);
        }
    }
}

int minPathSum(int** grid, int gridSize, int* gridColSize) 
{   
    if(gridSize == 1 && gridColSize[0] == 1)
    {
        return grid[0][0];
    }

    // Monta o grafo
    int qtdNodes = gridSize *  gridColSize[0];
    node *nodes = malloc(sizeof(node) * qtdNodes);

    for(int i = 0; i < qtdNodes; i++)
    {
        // nodes[i].edges = malloc(sizeof(edge));
        nodes[i].edges = NULL;
    }

    // Preenche o grafo
    // Conectamos cada nó no seu vizinho na linha, aresta bidirecionais
    int currentNode = -1;
    for(int i = 0; i < gridSize; i++)
    {   
        currentNode++;
        for (int j = 0; j < gridColSize[0] - 1; j++)
        {
            addNode(currentNode, currentNode + 1, grid[i][j], nodes); // Conecta o nó atual com o da direita 
            addNode(currentNode + 1,currentNode, grid[i][j + 1], nodes); // Conecta o nó da direita com o atual 
            currentNode++;
        }
    }

    // Conectamos cada nó no seu vizinho na coluna, aresta bidirecionais
    currentNode = 0;
    for(int i = 0; i < gridSize - 1; i++)
    {   
        for (int j = 0; j < gridColSize[0]; j++)
        {
            addNode(currentNode, currentNode + gridColSize[0], grid[i][j], nodes);
            addNode(currentNode + gridColSize[0], currentNode, grid[i + 1][j], nodes);
            currentNode++;
        }
    }

    // Print para teste
    // for(int i = 0; i < qtdNodes; i++)
    // {   
    //     printf("no: %d\n",i);
    //     for(edge *current = nodes[i].edges; current != NULL; current = current -> prox)
    //         printf("peso: %d Destino: %d\n",current-> weight ,current->destiny );
        
    // }

    // Matriz auxiliar do Bellman-Ford
    int **matriz = malloc(sizeof(int *) * qtdNodes);
    for (int i = 0; i < qtdNodes; i++)
    {
        matriz[i] = malloc(sizeof(int) * qtdNodes);
    }

    // Preenche a primeira linha
    for(int i = 0; i < qtdNodes - 1; i++)
    {
        matriz[0][i] = INF;
    }
    matriz[0][qtdNodes - 1] = 0;
    
    bellmanFord(nodes, qtdNodes, matriz, grid[gridSize - 1][gridColSize[0] - 1]);
    
    // Print para teste
    for(int i = 0; i < qtdNodes; i++)
    {
        for(int j = 0; j < qtdNodes; j++)
        printf("%d ",matriz[i][j]);
        
        printf("\n");
    }

    int result = matriz[qtdNodes - 1][0];
    return result + grid[gridSize - 1][gridColSize[0] - 1] ;
}

// int main()
// {
//     int grid[3][3] = {{1,3,1}, {1,5,1}, {4,2,1}};
//     int gridSize = 3;
//     int gridColSize[3] = {3,3,3};
//     int result = minPathSum(grid,gridSize, gridColSize);
//     printf("result : %d\n", result);
//     return 0;
// }