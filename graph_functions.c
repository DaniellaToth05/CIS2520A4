#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    // Implement the function logic here
    return NULL;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    // Implement the function logic here
    return NULL;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    // Implement the function logic here
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
    // Implement the function logic here
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    // Implement the function logic here
    int queue[MAX_VERTICES]; // queue to store the vertices
    int front = 0; // front of the queue
    int rear = 0; // rear of the queue

    bool discoveredSet[MAX_VERTICES] = {false}; // set to keep track of discovered vertices

    queue[rear] = startVertex; // add the start vertex to the queue
    discoveredSet[startVertex] = true; // mark the start vertex as discovered

    // loop until the queue is empty
    while(front < rear) { 
        int currentVertex = queue[front++]; // get the front vertex from the queue

        printf("%d ", currentVertex + 1); // print the vertex number

        Node *neighbor = graph->adjList[currentVertex]; // get the neighbors of the current vertex
        
        // loop through the neighbors of the current vertex
        while(neighbor){
            // if the neighbor is not discovered, add it to the queue and mark it as discovered
            if(!discoveredSet[neighbor->vertex]){
                queue[rear++] = neighbor->vertex; // add the neighbor to the queue
                discoveredSet[neighbor->vertex] = true; // mark the neighbor as discovered
            }
            neighbor = neighbor->next; // move to the next neighbor
        }
    }
    printf("\n"); 
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    // Implement the function logic here
    int stack[MAX_VERTICES]; // stack to store the vertices
    int top = -1; // top of the stack

    bool visitedSet[MAX_VERTICES] = {false}; // set to keep track of visited vertices

    stack[++top] = startVertex; // add the start vertex to the stack

    // loop until the stack is empty
    while(top >=0){
        int currentVertex = stack[top--]; // get the top vertex from the stack

        // if the vertex is not visited, visit it
        if(!visitedSet[currentVertex]){
            printf("%d ", currentVertex + 1); // print the vertex number
            visitedSet[currentVertex] = true; // mark the vertex as visited

            Node *neighbor = graph->adjList[currentVertex]; // get the neighbors of the current vertex  
            
            // loop through the neighbors of the current vertex
            while(neighbor){
                // if the neighbor is not visited, add it to the stack
                if(!visitedSet[neighbor->vertex]){
                    stack[++top] = neighbor->vertex; // add the neighbor to the stack
                }
                neighbor = neighbor->next; // move to the next neighbor
            }
        }   
    }
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    // Implement the function logic here
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    // Implement the function logic here
}
