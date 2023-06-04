#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <map>

using namespace std;

class Graph {
    public:
        Graph(int n_users, int n_jobs);
        void AdicionaAresta(string u, string j);
        int AlgoritmoGuloso();
        int AlgoritmoExato();

        void ImprimeMatriz();
        void ImprimeUsersMap();
        void ImprimeJobsMap();


    private:
        int** InicializaMatriz();
        bool ProcuraEAdicionaNoMap(map<string, int>& map, string s, int i, int& aux);

        void BFS(int n, int m);

        int** _matriz;
        int _matriz_N;
        int _matriz_M;

        map<string, int> _users;
        int _id_prox_user;

        map<string, int> _jobs;
        int _id_prox_job;

};

#endif // GRAPH_HPP