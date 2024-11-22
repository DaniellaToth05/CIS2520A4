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
Graph *readGraph(const char *filename){
    // Implement the function logic here
    FILE *file = fopen(filename, "r"); // open the file in read mode
    
    // check if the file was opened successfully
    if (file == NULL) {
        printf("\nError, was unable to open file %s\n", filename);
        return NULL;
    }

    int numVertices = 0; // number of vertices in the graph
    char line[1024]; // string to store the line that is read from the file
    // loop through the file to get the number of vertices
    while (fgets(line, sizeof(line), file)) {
        numVertices++; // increment the number of vertices
    }
    
    Graph *graph = (Graph *)malloc(sizeof(Graph)); // allocate memory for the graph

    // check if memory allocation was successful
    if (graph == NULL) {
        printf("\nError, memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    graph->numVertices = numVertices; // set the number of vertices in the graph

    fclose(file); // close the file

    // reopen the file to read the adjacency matrix
    file = fopen(filename, "r");

    // check if the file was reopened successfully
    if (file == NULL) {
        printf("\nError, was unable to reopen file %s\n", filename);
        free(graph); // free the graph
        return NULL;
    }

    // loop through the file to read the adjacency matrix
    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i] = NULL; // initialize the adjacency list

        // read the adjacency matrix row by row
        for (int j = 0; j < numVertices; j++) {
            // read the value for edge (i, j) from the file
            if (fscanf(file, "%d", &graph->adjMatrix[i][j]) != 1) {
                printf("\nError reading adjacency matrix value"); // print an error message if the value was not read
                fclose(file); // close the file
                free(graph); // free the graph
                return NULL; // return NULL
            }
        }
    }

    fclose(file);  // close the file
    //printf("\nGraph successfully read!\n");
    return graph; 
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    // Implement the function logic here
    Node *newNode = (Node *)malloc(sizeof(Node)); // allocate memory for the new node
    // if memory allocation was successful, set the vertex number and next pointer
    if(newNode != NULL){
        newNode->vertex = vertex; // set the vertex number
        newNode->next = NULL; // set the next pointer to NULL
        return newNode; // return the new node
    }
    // if memory allocation failed, print an error message
    else {
        printf("Error allocating memory for node\n");
        return NULL; // return NULL if an error occurs
    }
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    // Implement the function logic here
    for(int i = 0; i < graph->numVertices; i++){
        Node *current = graph->adjList[i]; // get the current node
        printf("Vertex %d:", i + 1); // print the vertex number
        // loop through the adjacency list and print the neighbors
        while(current != NULL){
            printf(" -> %d (%d)", current->vertex + 1, graph->adjMatrix[i][current->vertex]); // print the neighbor vertex number
            current = current->next; // move to the next neighbor
        }
        printf(" NULL\n"); // print NULL when the end of the list is reached
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph){
    // Implement the function logic here
    
    // loop through the adjacency matrix to create the adjacency list
    for (int i = 0; i < graph->numVertices; i++) {
       
        // loop through the neighbors of the current vertex
        for (int j = 0; j < graph->numVertices; j++) {
            
            // if there is an edge between the vertices...
            if (graph->adjMatrix[i][j] > 0) {
                Node *newNode = createNode(j); // create a new node for the neighbor vertex

                // if the adjacency list is empty, add the new node
                if (graph->adjList[i] == NULL) {
                    graph->adjList[i] = newNode;
                } 
                // if the adjacency list is not empty, add the new node to the end
                else {
                    Node *current = graph->adjList[i]; // get the current node
                    // loop until the end of the list is reached
                    while (current->next != NULL) {
                        current = current->next; // move to the next node
                    }
                    current->next = newNode; // add the new node to the end of the list
                }
            }
        }
    }
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

    queue[rear++] = startVertex; // add the start vertex to the queue
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

            int temp[MAX_VERTICES]; // temporary stack to store the neighbors
            int tempCount = 0; // count of neighbors in the temporary stack

            Node *neighbor = graph->adjList[currentVertex]; // get the neighbors of the current vertex  
            
            // loop through the neighbors of the current vertex
            while(neighbor){
                // if the neighbor is not visited, add it to the stack
                while (neighbor) {
                    if (!visitedSet[neighbor->vertex]) {
                        temp[tempCount++] = neighbor->vertex;
                    }
                    neighbor = neighbor->next;
                }
                for (int i = tempCount - 1; i >= 0; i--) {
                    stack[++top] = temp[i];
                }
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
    int distance[MAX_VERTICES]; // array to store the distance from the start vertex
    int previous[MAX_VERTICES]; // array to store the previous vertex in the shortest path
    bool visitedSet[MAX_VERTICES] = {false}; // set to keep track of visited vertices
    int numVertices = graph->numVertices; // number of vertices in the graph

    // initialize the distance and previous arrays
    for(int i = 0; i < numVertices; i++){
        distance[i] = INT_MAX; // set the distance to infinity
        previous[i] = -1; // set the previous vertex to -1
    }
    distance[startVertex] = 0; // set the distance of the start vertex to 0

    // loop through all the vertices
    for(int i = 0; i < numVertices; i++){
        int minDistance = INT_MAX; // set the minimum distance to infinity
        int u = -1; // set the current vertex to -1
        for(int v = 0; v < numVertices; v++){
            // find the vertex with the minimum distance that has not been visited
            if(!visitedSet[v] && distance[v] < minDistance){
                minDistance = distance[v]; // update the minimum distance
                u = v; // update the current vertex
            }
        }

        if(u == -1){
            break; // break if no vertex is found
        }
        visitedSet[u] = true; // mark the current vertex as visited

        Node *neighbor = graph->adjList[u]; // get the neighbors of the current vertex
        while(neighbor){
            int v = neighbor->vertex; // get the neighbor vertex
            int alt = distance[u] + graph->adjMatrix[u][v]; // calculate the new distance
            if(alt < distance[v]){
                distance[v] = alt; // update the distance
                previous[v] = u; // update the previous vertex
            }
            neighbor = neighbor->next; // move to the next neighbor
        }

    }

    printf("\n");
    for (int i = 0; i < numVertices; i++) {
        printf("Shortest distance from vertex %d to vertex %d: %d\n", startVertex + 1, i + 1, distance[i]);
    }
    //printf("\n");

}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    // Implement the function logic here
    if (graph != NULL){
        for(int i = 0; i < graph->numVertices; i++){
            Node *current = graph->adjList[i]; // get the current node
            Node *next = NULL; // get the next node
            while(current != NULL){
                next = current->next; // get the next node
                free(current); // free the current node
                current = next; // move to the next node
            }
        }
        free(graph); // free the graph
    }
    else {
        printf("Graph is NULL\n");
        return;
    }
}
