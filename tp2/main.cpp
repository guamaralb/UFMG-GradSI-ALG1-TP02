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

    Grafo.ImprimeMatriz();

    string nomeU, nomeJ;

    for (int i = 0; i < E; i++){
        cin >> nomeU >> nomeJ;
        Grafo.AdicionaAresta(nomeU, nomeJ);
    }

    Grafo.ImprimeUsersMap();
    Grafo.ImprimeJobsMap();
/*
    int x1 = -1;
    int x2 = -1;
    int d = -1;

    for (int i = 0; i < A; i++){
        cin >> x1 >> x2 >> d;
        Grafo.AdicionaAresta(x1, x2, d);
    }

    cout << "top" << endl;

    cout << Grafo.EncontraCaminhoMaisCurto() << endl;
*/

    cout << "FIM" << endl;
    return 0;
}
