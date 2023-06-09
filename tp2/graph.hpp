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


    private:
        int** InicializaMatriz();
        int* InicializaVetor(int tam, int valor);
        bool ProcuraEAdicionaNoMap(map<string, int>& map, string s, int i, int& aux);

        bool EncontraJobDisponivel(int u, int* jobsExplorados);

        int** _matriz;
        int _matriz_N_J;
        int _matriz_M_U;

        int* _alocacoesUserPorJob;

        map<string, int> _users;
        int _id_prox_user;

        map<string, int> _jobs;
        int _id_prox_job;

};

#endif // GRAPH_HPP