#include <iostream>
#include <string>

#include "graph.hpp"

#define INF 0x3f3f3f3f

using namespace std;

int main(int argc, char const *argv[]) {
    int U = -1;
    int J = -1;
    int E = -1;

    cin >> U >> J >> E;

    Graph Grafo(U, J);

    string nomeU, nomeJ;

    for (int i = 0; i < E; i++){
        cin >> nomeU >> nomeJ;
        Grafo.AdicionaAresta(nomeU, nomeJ);
    }

    Grafo.ImprimeMatriz();
    Grafo.ImprimeUsersMap();
    Grafo.ImprimeJobsMap();

    //cout << Grafo.AlgoritmoGuloso() << endl;
    cout << Grafo.AlgoritmoExato() << endl;    
}
