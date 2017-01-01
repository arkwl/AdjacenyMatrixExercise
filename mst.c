#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// A C / C++ program for Prim's Minimum Spanning Tree (MST) algorithm. 
// The program is for adjacency matrix representation of the graph
 
#include <limits.h>


#define INFINITY 9999
#define MAX 500

int adM[MAX][MAX];
int visited[MAX];
int number_of_verticies;
int result[MAX];

void primMST();
int printMST(int parent[], int n);
int minKey(int key[], int mstSet[]);

int main(int argc, char** argv){
	FILE* fp;
	char* line = malloc(100);
	size_t len = 0;
	ssize_t read = 0;
	char* fileLines[50];

	fp = fopen(argv[1], "r");
	if(fp == NULL){
		exit(EXIT_FAILURE);
	}
 
	int i = 0;
	while(fgets(line, 300 ,fp) != NULL){
		fileLines[i] = malloc(100);
		strcpy(fileLines[i], line);
		i++;
	}

	fclose(fp);
	if(line)
		free(line);

	int j;
	number_of_verticies = atoi(fileLines[0]);
	int number_of_edges = atoi(fileLines[1]);

	//change strings into numbers
	memset(adM, 0, sizeof(adM));
	memset(visited, 0, sizeof(visited));

	//printf("number_of_edges : %d   and number_of_verticies: %d\n", number_of_edges, number_of_verticies);
	//create adjacency matrix
	int i1, i2;
	for(i = 2 ; i < number_of_edges+2; i++){
		sscanf(fileLines[i], "%d    %d", &i1, &i2);
		//printf("one : %d  two: %d\n", i1, i2);
		adM[i1][i2] = 1;
		adM[i2][i1] = 1;
	}

	primMST();

	printf("\n");
	

	exit(EXIT_SUCCESS);

}

void primMST()
{
     int parent[number_of_verticies]; // Array to store constructed MST
     int key[number_of_verticies];   // Key values used to pick minimum weight edge in cut
     int mstSet[number_of_verticies];  // To represent set of vertices not yet included in MST
 
     // Initialize all keys as INFINITE
     for (int i = 0; i < number_of_verticies; i++){
        key[i] = INFINITY;
        mstSet[i] = 0;
    }
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have number_of_verticies vertices
     for (int count = 0; count < number_of_verticies-1; count++){
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = 1;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < number_of_verticies; v++)
 
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (adM[u][v] && mstSet[v] == 0 && adM[u][v] <  key[v])
             parent[v]  = u, key[v] = adM[u][v];
     }
 
     // print the constructed MST
     printMST(parent, number_of_verticies);
}

int printMST(int parent[], int n)
{
   printf("Edge   Weight\n");
   for (int i = 1; i < number_of_verticies; i++)
      printf("%d - %d    %d \n", parent[i], i, adM[i][parent[i]]);
}

int minKey(int key[], int mstSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < number_of_verticies + 1; v++)
     if (mstSet[v] == 0 && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}