#include "graph.h"

/*
 * A basic menu based structure has been provided
 */

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // read the graph from the file
    Graph *graph = readGraph(argv[1]);
    if(graph == NULL){
        printf("Error reading graph from file\n");
        return 1;
    }

    createAdjacencyList(graph); // create the adjacency list

    int choice;
    int startVertex = 0;

    do
    {

        // Display the options
        prompt();

        // Get user input
        printf("Enter a Choice: ");
        scanf("%d", &choice);

        /*
         * You will need to add all the cases here.
         * Call the relevant functions in each case.
         * Make sure to handle invalid inputs or edge cases.
         */

        switch (choice) {
            case 1:
                // Code for case 1
                printf("Adjacency List:\n");
                displayAdjacencyList(graph);
                break;
            case 2:
                printf("BFS (Breadth-First Search) starting from vertex %d:\n", startVertex + 1);
                bfs(graph, startVertex);
                break;
            case 3:
                printf("DFS (Depth-First Search) starting from vertex %d:\n", startVertex + 1);
                dfs(graph, startVertex);
                break;
            case 4:
                printf("Dijkstra's Algorithm to find shortest path, starting from vertex %d:\n", startVertex + 1);
                dijkstra(graph, startVertex);
                break;
            case 5:
                printf("Exiting the program. Bye!\n");
                freeGraph(graph);
                return 0;
            default:
                // Code for default case
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (true);

    return 0;
}
