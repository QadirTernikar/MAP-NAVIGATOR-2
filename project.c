#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

// Holds the name of the vertexes
char labels[100][MAX_STRING_LENGTH];

// Holds the parent vertex of that index vertex
int path[100];

// Holds the shortest distance
int distance[100];

// Holds the status of the vertex 0 if vertex is not visited and 1 if visited

int visited[100];

// Holds the index of vertex present in shortest path
int arr[100];


int c;


// Function to print the path recursively
void printPath(int path[], int j);

// Function to print the shortest path and its details
void printSolution(int s, int destination, int vertices, int graph[100][100]);

// Utility function for printing all paths between two vertices
void printAllPathsUtil(int u, int destination, int graph[100][100], int n, int visited[], int path[], int path_index);

// Function to print all possible paths between two vertices
void printAllPaths(int source, int destination, int graph[100][100], int n);

// Function to find the minimum distance vertex from the set of vertices not yet processed
int minimum(int distance[], int visited[], int n);

// Function to perform Dijkstra's algorithm to find the shortest path
void dijkstra(int graph[100][100], int n, int s, int destination);

// Function to update the file with vertex labels
void updateFile(int n);

// Function to update distances after adding a new vertex
void updateDistances(int n, int graph[100][100]);

// Function to add a new vertex to the graph
void addVertex(int *n, int graph[100][100]);

// Function to remove a vertex from the graph
void removeVertex(int *n, int graph[100][100]);

// Function to check the admin credentials
int checkAdminCredentials(const char *entered_admin_id, const char *entered_admin_password);

// Function to find the shortest path using Bellman-Ford Algorithm
void bellmanFordShortestPath(int source, int destination, int graph[100][100], int n);


// Function for admin login
void adminLogin();

// Function to clear the screen
void clearScreen();



// Function to find the shortest path using Bellman-Ford Algorithm
void bellmanFordShortestPath(int source, int destination, int graph[100][100], int n)
{

    int distance[100];

    int path[100];

    for (int i = 1; i <= n; i++)
    {

        distance[i] = INT_MAX;

        path[i] = -1;
    }

    distance[source] = 0;

    // Relax edges repeatedly
    for (int i = 1; i <= n - 1; i++)
    {

        for (int u = 1; u <= n; u++)
        {

            for (int v = 1; v <= n; v++)
            {

                if (graph[u][v] != 0 && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])
                {

                    distance[v] = distance[u] + graph[u][v];

                    path[v] = u;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 1; u <= n; u++)
    {

        for (int v = 1; v <= n; v++)
        {
            if (graph[u][v] != 0 && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])

            {

                printf("\nGraph contains a negative weight cycle. Bellman-Ford cannot be applied.\n");

                return;
            }
        }
    }

    // Print the shortest path and distance
    printf("\nShortest path using Bellman-Ford from %s to %s is: ", labels[source], labels[destination]);

    printPath(path, destination);

    printf("\nShortest distance: %d\n", distance[destination]);

}

void printPath(int path[], int j)
{
    //condition
    if (path[j] == -1)
        return;

    //recursively calling same function
    printPath(path, path[j]);

    //incrementing c
    c += 1;

    //assigning j value to the array arr at c index
    arr[c] = j;

    printf("%s -> ", labels[j]);

}

void printSolution(int s, int destination, int vertices, int graph[100][100])
{

    printf("\n**************************************\n");

    float time;

    time = (distance[destination]/60.0);

    printf("\nShortest path length from %s to %s is: %d km and time taken is %.2f h with constant speed 60km/h", labels[s], labels[destination], distance[destination],time);

    printf("\n**************************************\n");

    printf("\n\nThe path is: %s -> ", labels[s]);

    printPath(path, destination);

    printf("\n**************************************\n");

    printf("\n");

    printf("\nThe in-between distances are\n");

    for (int i = 1; i <= c - 1; i++)
    {
        float t;

        t = graph[arr[i]][arr[i + 1]]/60.0;

        printf("\nThe distance between %s to %s is %d km and the time taken is %.2f with constant speed 60km/h\n", labels[arr[i]], labels[arr[i + 1]], graph[arr[i]][arr[i + 1]],t);
    }
    printf("\n**************************************\n");
}

void printAllPathsUtil(int u, int destination, int graph[100][100], int n, int visited[], int path[], int path_index)
{
    //making vertex u as visited by assigning 1
    visited[u] = 1;

    path[path_index] = u;

    path_index++;

    if (u == destination)
    {
        //initially making total distance as 0
        int total_distance = 0;

        // Print the path and its total distance
        for (int i = 0; i < path_index - 1; i++)
        {
            printf("%s -> ", labels[path[i]]);

            total_distance += graph[path[i]][path[i + 1]];
        }

        // calculating the time required to travel desired location
        float time=(total_distance/60.0);

        printf("%s (Total Distance: %d km and the time taken is %.2f h h with constant speed 60km/h\n", labels[path[path_index - 1]],total_distance,time);
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i] && graph[u][i] != 0)
            {
                printAllPathsUtil(i, destination, graph, n, visited, path, path_index);
            }
        }
    }

    //decrementing path index
    path_index--;

    //assigning the vertex u as not visited
    visited[u] = 0;
}

void printAllPaths(int source, int destination, int graph[100][100], int n)
{
    //initially making visited as 0
    int visited[100] = {0};

    //declaring path array
    int path[100];

    //making path_index as 0
    int path_index = 0;

    printf("\nAll possible paths from %s to %s are:\n", labels[source], labels[destination]);

    printAllPathsUtil(source, destination, graph, n, visited, path, path_index);
}

int minimum(int distance[], int visited[], int n)
{
    //Taking min as INT MAX to find minimum of distance

    int min = INT_MAX, selected_vertix;

    for (int i = 1; i <= n; i++)
    {
        //checking the condition whether there is any vertex which has smaller distance
        if (distance[i] <= min && visited[i] == 0)
        {

            min = distance[i];

            selected_vertix = i;
        }
    }

    return selected_vertix;
}

void dijkstra(int graph[100][100], int n, int s, int destination)
{
    // Initialization
    for (int i = 1; i <= n; i++)
    {
        //initially making all the distance as INT MAX
        distance[i] = INT_MAX;

        //Making all visited vertex as 0 initially
        visited[i] = 0;

        //making parent of all vertex as -1 initially
        path[i] = -1;
    }

    // Distance from source to itself is 0
    distance[s] = 0;

    // Main loop
    for (int i = 1; i < n; i++)
    {
        // Find the vertex with the minimum distance value
        int selected_vertix = minimum(distance, visited, n);

        //making selected vertex as visited by assign 1
        visited[selected_vertix] = 1;

        // Update distance value of the neighboring vertices
        for (int v = 1; v <= n; v++)
        {
            if (!visited[v] && graph[selected_vertix][v] != 0 && distance[selected_vertix] != INT_MAX &&
                    distance[selected_vertix] + graph[selected_vertix][v] < distance[v])
            {
                distance[v] = distance[selected_vertix] + graph[selected_vertix][v];
                path[v] = selected_vertix;
            }
        }
    }

    if (distance[destination] == INT_MAX)
    {
        printf("There is no path between source and destination\n");
        return;
    }

}

void updateFile(int n)
{
    FILE *file = fopen("nameofvertices.txt", "w");

    for (int i = 1; i <= n; i++)
    {

        fprintf(file, "%s\n", labels[i]);

    }

    fclose(file);

    FILE *p=fopen("vertices.txt","w");

    fprintf(p,"%d",n);

    fclose(p);
}
void updateDistances(int n, int graph[100][100])
{

    for (int i = 1; i <= n - 1; i++)
    {
        //asks the newadded vertex distance with all other vertice
        printf("Enter the distance from %s to %s: ", labels[i], labels[n]);

        scanf("%d", &graph[i][n]);

        graph[n][i] = graph[i][n]; // Update symmetric distance in the matrix
    }
}

void addVertex(int *n, int graph[100][100])
{

    char b[MAX_STRING_LENGTH];

    if (*n < 100)
    {

        (*n)++;

        printf("Enter the label for the new vertex: ");

        getchar();

        fgets(b,sizeof(b), stdin);

        b[strcspn(b, "\n")] = '\0';

        strcpy(labels[*n],b);

        // Update distances in the adjacency matrix with the new vertex
        for (int i = 1; i <= *n; i++)
        {

            graph[i][*n] = 0;
            // Set distances from the new vertex to other vertices

            graph[*n][i] = 0;
            // Set distances from other vertices to the new vertex
        }

        // Prompt for and set distances from the new vertex to other vertices
        updateDistances(*n, graph);

        // Update the file with the new vertex
        updateFile(*n);

        // Update the adjacency file with the new row and column

        FILE *adjacencyFile = fopen("adjacency.txt", "a");

        fprintf(adjacencyFile, "\n");

        for (int i = 1; i <= *n; i++)
        {

            fprintf(adjacencyFile, "0 ");

        }

        fclose(adjacencyFile);

        printf("New vertex '%s' added successfully.\n", labels[*n]);
    }
    else

    {
        printf("Cannot add more vertices. Maximum limit reached.\n");
    }
}

void removeVertex(int *n, int graph[100][100])
{
    char v[MAX_STRING_LENGTH];

    int vertexToRemove;

    printf("Enter the vertex to remove\n");

    getchar();

    fgets(v, sizeof(v), stdin);

    v[strcspn(v, "\n")] = '\0';

    for(int i=1; i<=*n; i++)
    {
        if((strcmp(v,labels[i]))==0)
        {
            vertexToRemove=i;
        }
    }

    if (vertexToRemove < 1 || vertexToRemove > *n)
    {
        printf("Invalid vertex index.\n");

        return;
    }

    // Shift labels and update distances in the adjacency matrix

    for (int i = vertexToRemove; i <= *n - 1; i++)
    {
        strcpy(labels[i], labels[i + 1]);

        for (int j = 1; j <= *n; j++)
        {
            graph[j][i] = graph[j][i + 1];
        }
    }

    for (int i = vertexToRemove; i < *n; i++)
    {
        for (int j = 1; j <= *n; j++)

        {
            graph[i][j] = graph[i + 1][j];

        }
    }

    (*n)--;
     // Decrease the number of vertices


    // Update the files with the removed vertex
    updateFile(*n);

    FILE *file = fopen("adjacency.txt", "w");

    for (int i = 1; i <= *n; i++)
    {
        for (int j = 1; j <= *n; j++)
        {

            fprintf(file, "%d ", graph[i][j]);

        }
        fprintf(file, "\n");
    }

    fclose(file);

    printf("Vertex removed successfully.\n");

}

int checkAdminCredentials(const char *entered_admin_id, const char *entered_admin_password) {

    char admin_id[MAX_STRING_LENGTH];

    char admin_password[MAX_STRING_LENGTH];

    FILE *adminFile = fopen("admin.txt", "r");

    if (adminFile == NULL) {

        printf("Error opening admin file.\n");

        return 0;
    }

    fscanf(adminFile, "%s %s", admin_id, admin_password);

    fclose(adminFile);

        //check weather both admin_id and admin_password are correct or not .

    if (strcmp(admin_id, entered_admin_id) == 0 && strcmp(admin_password, entered_admin_password) == 0)

        {
        return 1; // Credentials match
      }

    else {
        printf("\nInvalid admin credentials. ");

        //incorrect admin id .

        if (strcmp(admin_id, entered_admin_id) != 0) {

            printf("Incorrect admin ID.\n");
        }

        //incorrect admin password.

        if(strcmp(admin_password, entered_admin_password)!=0) {

            printf("Incorrect admin password.\n");
        }

        return 0; // Credentials do not match
    }
}

void adminLogin() {
    char entered_admin_id[MAX_STRING_LENGTH];
    char entered_admin_password[MAX_STRING_LENGTH];

    int loginSuccess = 0;

    do {
        printf("\nEnter admin ID: ");
        scanf("%s", entered_admin_id);

        printf("Enter admin password: ");
        scanf("%s", entered_admin_password);

        loginSuccess = checkAdminCredentials(entered_admin_id, entered_admin_password);

        if (!loginSuccess) {
            printf("Retry entering admin credentials.\n");
        }

    } while (!loginSuccess);

    printf("\nAdmin login successful.\n");
    // Place the admin menu code here
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main()
{
    int n, s_ind, d_ind, choice, u_choice;
    //n-no of vertexes
    //s_ind source index.
    //d_ind destination index.

        char source[MAX_STRING_LENGTH], destination[MAX_STRING_LENGTH];

    //open vertex file
    FILE *verticesFile = fopen("vertices.txt", "r");

    //open nameofvertices file
    FILE *labelsFile = fopen("nameofvertices.txt", "r");

    //openadjacency file
    FILE *adjacencyFile = fopen("adjacency.txt", "r");

    if (verticesFile == NULL || labelsFile == NULL || adjacencyFile == NULL)
    {

        printf("Error opening one of the files.\n");

        return 1;
    }

    // Read the number of vertices

    fscanf(verticesFile, "%d", &n);
    //n=19 initially

    for (int i = 1; i <= n; i++)
    {
        fgets(labels[i], sizeof(labels[i]), labelsFile);

        // Remove the newline character if present

        if (labels[i][strlen(labels[i]) - 1] == '\n')
        {

            labels[i][strlen(labels[i]) - 1] = '\0';
        }
    }

    // Read the adjacency matrix

    int graph[100][100];

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fscanf(adjacencyFile, "%d", &graph[i][j]);
        }
    }

    //closing the vertex file
    fclose(verticesFile);

    //closing nameofverteces file
    fclose(labelsFile);

    //closing the adjacency file
    fclose(adjacencyFile);

    printf("\n**************************************\n");

    printf("\nWelcome to Map Navigator\n");

    printf("\n**************************************\n");

    while (1)
    {
        c=1;

        printf("1. User login\n");

        printf("2. Admin login\n");

        printf("3. Exit\n");

        printf("\n**************************************\n");

        printf("Enter the choice: ");

        scanf("%d", &choice);

        clearScreen();
        // Clear screen after each operation

        printf("\n**************************************\n");

        switch (choice)
        {
        case 1:

            for (int i = 1; i <= n; i++)
            {

                printf("%s\n", labels[i]);

            }

            printf("\nEnter the source location name and destination location name:\n");

            getchar();

            printf("\nEnter the source location name:\n");

            int source_found = 0;

            while (!source_found)
            {
                 // Consume newline left in buffer
                fgets(source, sizeof(source), stdin);

                source[strcspn(source, "\n")] = '\0'; // Remove newline character

                for (int i = 1; i <= n; i++)
                {
                    if (strcmp(labels[i], source) == 0)
                    {
                        //stores the index of the source vertex
                        s_ind = i;

                        //if source
                        source_found = 1;

                        break;
                    }
                }

                if (!source_found)
                {

                    printf("Source vertex not found. Please enter a valid source vertex name.\n");

                }
            }

            printf("\nEnter the destination vertex name:\n");

            int destination_found = 0;

            while (!destination_found)
            {

                fgets(destination, sizeof(destination), stdin);

                destination[strcspn(destination, "\n")] = '\0'; // Remove newline character

                for (int i = 1; i <= n; i++)
                {
                    if (strcmp(labels[i], destination) == 0)
                    {
                        //stores the index of destination
                        d_ind = i;

                        //if destination vertex is found it is assigned as 1
                        destination_found = 1;

                        break;
                    }
                }

                if (!destination_found)
                {

                    printf("Destination vertex name has been found. Please enter a valid destination vertex.\n");

                }
            }

            printf("\n**************************************\n");

// ...


            arr[c] = s_ind;

            while (1)
            {

                printf("\n**************************************\n");

                printf("1. Find shortest path\n");

                printf("2. Show all possible paths\n");

                printf("3. Exit\n");

                printf("\n**************************************\n");

                printf("Enter the choice: ");

                scanf("%d", &u_choice);

                clearScreen();  // Clear screen after each operation

                printf("\n**************************************\n");

                switch (u_choice)
                {

                case 1:
                    //calling dijkstra function
                    dijkstra(graph, n, s_ind, d_ind);

                    //calling the printSolution function
                    printSolution(s_ind, d_ind, n, graph);

                    //calling the bellmanFordShortestPaths
                    bellmanFordShortestPath(s_ind,d_ind,graph,n);

                    break;

                case 2:

                    //calling of printAllpaths
                    printAllPaths(s_ind, d_ind, graph, n);

                    break;

                case 3:

                    break;

                default:

                    printf("Invalid choice\n");

                }

                if (u_choice == 3)

                    break;
            }

            break;

        case 2:

            adminLogin();

            while (1)

            {

                printf("\n**************************************\n");

                printf("1. Add new vertex\n");

                printf("2. Remove a vertex\n");

                printf("3. Show all vertices\n");

                printf("4. Exit\n");

                printf("\n**************************************\n");

                printf("Enter the choice: ");

                scanf("%d", &u_choice);

                printf("\n**************************************\n");

                switch (u_choice)

                {

                case 1:

                    addVertex(&n, graph);

                    FILE *p;

                    p = fopen("adjacency.txt","w");

                    if(p==NULL)

                    {
                        printf("Error while opening the file\n");

                        return;
                    }

                    for(int i=1; i<=n; i++)
                    {

                        for(int j=1; j<=n; j++)
                        {


                            fprintf(p,"%d ",graph[i][j]);

                        }

                        fprintf(p,"\n");
                    }

                    fclose(p);

                    break;

                case 2:

                    removeVertex(&n, graph);

                    break;

                case 3:


                    // Display the array of strings

                    printf("\nThe array of strings is\n");

                    for (int i = 1; i <= n; i++)
                    {

                        printf("%s\n", labels[i]);

                    }

                    break;


                case 4:

                    getchar();

                    // Consume newline left in buffer

                    break;

                default:

                    printf("Invalid choice\n");

                }

                if (u_choice == 4)

                    break;
            }
            break;

        case 3:

            exit(0);

            break;

        default:

            printf("Invalid choice\n");
        }
    }
    return 0;
}
