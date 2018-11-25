#include <stdio.h>
#include <stdlib.h>

struct node
{
    int vertex;
    struct node *next;
};

struct node *
createNode(int vertex);

struct Graph
{
    int vertices;
    int *visited;
    struct node **adjList;
};

struct Graph *
createGraph(int);
void addEdge(struct Graph *, int, int);
void printGraph(struct Graph *);
void dfs(struct Graph *, int);

int main()
{
    struct Graph *g = createGraph(9);

    addEdge(g, 0, 1);
    addEdge(g, 0, 3);

    addEdge(g, 1, 0);
    addEdge(g, 1, 2);
    addEdge(g, 1, 4);

    addEdge(g, 2, 1);
    addEdge(g, 2, 5);

    addEdge(g, 3, 0);
    addEdge(g, 3, 4);
    addEdge(g, 3, 6);

    addEdge(g, 4, 1);
    addEdge(g, 4, 3);
    addEdge(g, 4, 5);
    addEdge(g, 4, 7);

    addEdge(g, 5, 2);
    addEdge(g, 5, 4);
    addEdge(g, 5, 8);

    addEdge(g, 6, 3);
    addEdge(g, 6, 7);

    addEdge(g, 7, 6);
    addEdge(g, 7, 4);
    addEdge(g, 7, 8);

    addEdge(g, 8, 5);
    addEdge(g, 8, 7);

    printGraph(g);
    dfs(g, 0);

    return 0;
}

struct Graph *createGraph(int vertices)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = malloc(vertices * sizeof(struct node *));
    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++)
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

struct node *createNode(int v)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    // Add edge from src to dest
    struct node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void printGraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->vertices; v++)
    {
        struct node *temp = graph->adjList[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void dfs(struct Graph *graph, int vertex)
{
    struct node *adjList = graph->adjList[vertex];
    struct node *temp = adjList;

    graph->visited[vertex] = 1;
    printf("Visited %d \n", vertex);

    while (temp != NULL)
    {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0)
        {
            dfs(graph, connectedVertex);
        }
        temp = temp->next;
    }
}
