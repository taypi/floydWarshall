#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
 
int readFile(char **);
void getGraph(char **, int, float *);
void path(int i, int j, int v, int *nxt);
void printSolution(int, float *, int *);
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

    for (i = 0; i < v; i++){
        for (j = 0; j < v; j++){
            if (graphString[i][j] == "inf"){
                graph[i*v + j] = HUGE_VALF;
            }
            else{
                graph[i*v + j] = stof(graphString[i][j].c_str());
            }
            
        }
    }
}

void path(int i, int j, int v, int *nxt) {
    if (i == j) cout << i << " ";
    else if (nxt[i*v + j] == -1) cout << "no path exists";
    else {
        path(i, nxt[i*v + j], v, nxt);
        cout << j << " ";
    }
}

void printSolution(int v, float *dist, int *nxt) {

    printf("\nMatrix D:\n\n");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++)
            cout << dist[i*v + j] << "\t";
        cout << "\n";
    }

    printf("\nMatrix P:\n\n");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (nxt[i*v + j] == -1) cout << "NIL\t";
            else cout << nxt[i*v + j] << "\t";
        }
        printf("\n");
    }

    printf("\nPaths:\n\n");
    printf("Pair\tDist\tPath\n");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (i != j){
                cout << i << "->" << j << "\t " << dist[i*v + j] << "\t";
                path(i, j, v, nxt);
                cout << endl;
            }
        }
    }
}
 
void floydWarshall (int v, float *graph) {

    float dist[v*v];
    int nxt[v*v];
 
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++){
            dist[i*v + j] = graph[i*v + j];
            if (i == j || isinf(graph[i*v + j])) nxt[i*v + j] = -1;
            else nxt[i*v + j] = i;
        }
 
    for (int k = 0; k < v; k++)
    {
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                if (dist[i*v + k] + dist[k*v + j] < dist[i*v + j]){
                    dist[i*v + j] = dist[i*v + k] + dist[k*v + j];
                    nxt[i*v + j] = nxt[k*v + j];
                }
            }
        }
    }
 
    printSolution(v, dist, nxt);
}