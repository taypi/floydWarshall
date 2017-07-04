#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
 
int readFile(char **);
void getGraph(char **, int, float *);
void printSolution(int, float *);
void floydWarshall (int, float *);
 
int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    int v;

    v = readFile(argv);

    float graph[v*v];

    getGraph(argv, v, graph);

    floydWarshall(v, graph);

    return 0;
}

int readFile(char* argv[]) {
    int v;
    string line;

    ifstream myfile;

    myfile.open(argv[1], fstream::in);
    if (myfile.is_open()) {
        getline(myfile,line);
        stringstream s(line);
        s >> v;
    }
    else {
        printf("Error reading from file\n");
        exit(0);
    }
    myfile.close();
    return v;
}

void getGraph(char* argv[], int v, float* graph) {
    int i = 0, j = 0, columns = 0;
    string line;
    ifstream myfile;
    string graphString[v][v];

    myfile.open(argv[1], fstream::in);
    if (myfile.is_open()) {
        getline(myfile,line);
        stringstream s(line);
        while(getline(myfile,line)) {
            stringstream s(line);
            while (s >> graphString[i][j]) j++;
            if (j != v) {
                printf("Invalid number of columns\n");
                exit(0);
            }
            j = 0;
            i++;
        }
    }
    else {
        printf("Error reading from file\n");
        exit(0);
    }
    myfile.close();

    if (i != v){
        printf("Invalid number of rows\n");
        exit(0);
    }

    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            if (graphString[i][j] == "inf"){
                graph[i*v + j] = HUGE_VALF;
            }
            else{
                graph[i*v + j] = stof(graphString[i][j].c_str());
            }
            
        }
    }
}

void printSolution(int v, float *dist) {
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
            printf ("%.0f\t", dist[i*v + j]);
        printf("\n");
    }
}
 
void floydWarshall (int v, float *graph) {

    float dist[v*v];
 
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            dist[i*v + j] = graph[i*v + j];
 
    for (int k = 0; k < v; k++)
    {
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                if (dist[i*v + k] + dist[k*v + j] < dist[i*v + j])
                    dist[i*v + j] = dist[i*v + k] + dist[k*v + j];
            }
        }
    }
 
    printSolution(v, dist);
}