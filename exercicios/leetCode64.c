#include <stdio.h>
#include <stdlib.h>

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

void addNo(int source, int destiny, int weight, node *nodes)
{   
    edge *new = malloc(sizeof(edge));
    new -> destiny = destiny;
    new -> weight = weight;

    new -> prox = nodes[source].edges;
    nodes[source].edges = new;
}

int minPathSum(int grid[][3], int gridSize, int* gridColSize) 
{   
    // Monta o grafo
    int qtdNodes = gridSize *  gridColSize[0];
    node *nodes = malloc(sizeof(node) * qtdNodes);

    for(int i = 0; i < qtdNodes; i++)
    {
        nodes[i].edges = malloc(sizeof(edge));
    }

    // Preenche o grafo
    // Conectamos cada nó no seu vizinho na linha, aresta bidirecionais
    int currentNode = -1;
    for(int i = 0; i < gridSize; i++)
    {   
        currentNode++;
        for (int j = 0; j < gridColSize[0] - 1; j++)
        {
            addNo(currentNode, currentNode + 1, grid[i][j] + grid[i][j + 1], nodes); // Conecta o nó atual com o da direita 
            addNo(currentNode + 1,currentNode, grid[i][j] + grid[i][j + 1], nodes); // Conecta o nó da direita com o atual 
            currentNode++;
        }
    }

    // Conectamos cada nó no seu vizinho na coluna, aresta bidirecionais
    currentNode = 0;
    for(int i = 0; i < gridSize - 1; i++)
    {   
        for (int j = 0; j < gridColSize[0]; j++)
        {
            addNo(currentNode, currentNode + gridColSize[0], grid[i][j] + grid[i + 1][j], nodes);
            addNo(currentNode + gridColSize[0], currentNode, grid[i][j] + grid[i + 1][j], nodes);
            currentNode++;
        }
    }

    for(int i = 0; i < qtdNodes; i++)
    {   
        printf("no: %d\n",i);
        for(edge *current = nodes[i].edges; current != NULL; current = current -> prox)
            printf("peso: %d Destino: %d\n",current-> weight ,current->destiny );
        
    }
    // // Conectamos cada nó no seu vizinho na coluna
    // for(int i = 0; i < gridSize - 1; i++)
    // {

    // }

}



int main()
{
    int grid[3][3] = {{1,3,1}, {1,5,1}, {4,2,1}};
    int gridSize = 3;
    int gridColSize[3] = {3,3,3};
    minPathSum(grid,gridSize, gridColSize);

    return 0;
}