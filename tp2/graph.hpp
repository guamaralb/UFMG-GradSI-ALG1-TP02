#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <map>

using namespace std;

class Graph {
    public:
        Graph(int n_users, int n_jobs);
        void AdicionaAresta(string u, string j);

        void ImprimeMatriz();
        void ImprimeUsersMap();
        void ImprimeJobsMap();


    private:
        int** InicializaMatriz();
        bool AdicionaNoMap(map<string, int> map, string s, int i);

        int** _matriz;
        int _matriz_N;
        int _matriz_M;

        map<string, int> _users;
        int _id_prox_user;

        map<string, int> _jobs;
        int _id_prox_job;






        int EncontraCaminhoMaisCurto();
        void ExpandeFronteira(pair<int, int> vert_atual, vector<pair<int, int>>& explorados, vector<pair<int, int>>& fronteira);
        void AdicionaEmFronteira(vector<pair<int, int>>& fronteira, int id, int d);
        bool VerificaSeExplorado(int vert, vector<pair<int, int>>& exp);
        pair<int, int> CaminhaNaFronteira(vector<pair<int, int>>& fronteira);
        void RemoveDaFronteiraPorId(vector<pair<int, int>>& fronteira, int id);

        int _n_vert;
        int _n_matriz;

};

#endif // GRAPH_HPP