#include "graph.hpp"
#include <iostream>
#include <string>
#include <map>
#include <iomanip>

#define TAM_TEXT 25
#define TAM_NUM 3

using namespace std;

/*/--------------------------------------------------------------------//
APAGAR
//--------------------------------------------------------------------/*/
void Graph::ImprimeMatriz(){
    cout << "[u\\j]";
    
    for (int j = 0; j < this->_matriz_M; j++) {
        cout << "[" << right << setw(TAM_NUM - 1) << j << "]";
    }
    
    cout << endl;

    for (int i = 0; i < this->_matriz_N; i++) {
        cout << "[" << right << setw(TAM_NUM - 1) << i << "]";
        for (int j = 0; j < this->_matriz_M; j++) {
            if(this->_matriz[i][j] == 0) {
            cout << right << setw(TAM_NUM) << "_" << " ";
            } else {
                cout << right << setw(TAM_NUM) << this->_matriz[i][j] << " ";
            }
        }
        cout << endl;
    }
}

/*/--------------------------------------------------------------------//
APAGAR
//--------------------------------------------------------------------/*/
void Graph::ImprimeUsersMap(){
    cout << "--- USERS (" << this->_users.size() << ") ---" << endl;
    for (auto& x: this->_users){
        cout << left << setw(TAM_TEXT) << x.first << ':' << right << setw(TAM_NUM) << x.second << endl;
    }
}

/*/--------------------------------------------------------------------//
APAGAR
//--------------------------------------------------------------------/*/
void Graph::ImprimeJobsMap(){
    cout << "--- JOBS (" << this->_jobs.size() << ") ---" << endl;
    for (auto& x: this->_jobs){
        cout << left << setw(TAM_TEXT) << x.first << ':' << right << setw(TAM_NUM) << x.second << endl;
    }
}


/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
Graph::Graph(int n_users, int n_jobs) {
    this->_matriz_N = n_users;
    this->_matriz_M = n_jobs;
    this->_matriz = this->InicializaMatriz();

    this->_id_prox_user = 0;
    this->_id_prox_job = 0;

}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
int** Graph::InicializaMatriz() {

    int** grafo_matriz = new int* [this->_matriz_N];
    
    for (int i = 0; i < _matriz_N; i++){
        grafo_matriz[i] = new int[this->_matriz_M];
        for (int j = 0; j < _matriz_M; j++) {
            grafo_matriz[i][j] = -1;
        }
    }

    return grafo_matriz;
}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
bool Graph::AdicionaNoMap(map<string, int> map, string s, int i){
    
    if(map.find(s) == map.end()){
        map.emplace(s, i);
        return true;
    }

    return false;
}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
void Graph::AdicionaAresta(string u, string j){

    if(AdicionaNoMap(this->_users, u, this->_id_prox_job)){
        this->_id_prox_job++;
    }


    /*
    this->_matriz[u][j] = 1;
    this->_matriz[j][u] = 1;
    */
}








































/*/--------------------------------------------------------------------//
> Executa Dijkstra
> vector<pair<int, int>> é usado para armazenar sempre as seguintes infos do vertice: id + distancia até a origem 
> "explorados" contém vértices para os quais já se sabe o menor caminho
> "fronteira" contém os vértices que podem ser alcançados a partir de vértices já explorados
//--------------------------------------------------------------------/*/
int Graph::EncontraCaminhoMaisCurto(){
    int destino = (this->_n_vert) - 1;
    vector<pair<int, int>> explorados;
    vector<pair<int, int>> fronteira;

    pair<int, int> vert_atual = make_pair(0, 0);


    this->ExpandeFronteira(vert_atual, explorados, fronteira);
    explorados.emplace_back(vert_atual);
    
    do{
        vert_atual = CaminhaNaFronteira(fronteira);
        this->ExpandeFronteira(vert_atual, explorados, fronteira);
        explorados.emplace_back(vert_atual);
        this->RemoveDaFronteiraPorId(fronteira, vert_atual.first);

    } while((fronteira.size() > 0) && vert_atual.first != destino);

    if (vert_atual.first == destino){
        return vert_atual.second;
    } else {
        return -1;
    }
}

/*/--------------------------------------------------------------------//
> Natualmente, o mesmo vértice pode ser enviado para a fronteira duas vezes, no entanto, se isso ocorrer a função vai garantir que a distancia guardada na fronteira é a menor possível
//--------------------------------------------------------------------/*/
void Graph::AdicionaEmFronteira(vector<pair<int, int>>& fronteira, int id, int d){
    bool add_nova = true;

    for (int i = 0; i < (int)fronteira.size(); i++){        
        if(fronteira[i].first == id){
            add_nova = false;

            if(fronteira[i].second > d){
                fronteira[i].second = d;
            }
        }
    }
    
    if (add_nova){
        fronteira.emplace_back(make_pair(id, d));
    }
}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
void Graph::RemoveDaFronteiraPorId(vector<pair<int, int>>& fronteira, int id){
    for (int i = 0; i < (int)fronteira.size(); i++){
        if(fronteira[i].first == id){
            fronteira.erase(fronteira.begin() + i);
        }
    }
}



/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
void Graph::ExpandeFronteira(pair<int, int> vert_atual, vector<pair<int, int>>& explorados, vector<pair<int, int>>& fronteira){
    int id_atual = vert_atual.first;
    int d_atual = vert_atual.second;

    for (int j = 0; j < this->_n_matriz; j++){
        if (this->_matriz[id_atual][j] >= 0){
            if(!VerificaSeExplorado(j, explorados)){
                this->_matriz[id_atual][j] += d_atual;
                this->AdicionaEmFronteira(fronteira, j, this->_matriz[id_atual][j]);
            }
        }
    }

}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
bool Graph::VerificaSeExplorado(int vert, vector<pair<int, int>>& explorados){
    for (int i = 0; i < (int)explorados.size(); i++){
        if(explorados[i].first == vert){
            return true;
        }
    }

    return false;
}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
pair<int, int> Graph::CaminhaNaFronteira(vector<pair<int, int>>& fronteira){
    int aux_id = fronteira[0].first;
    int aux_d_min = fronteira[0].second;

    for (int i = 0; i < (int)fronteira.size(); i++){
        if(fronteira[i].second < aux_d_min){

            aux_id = fronteira[i].first;
            aux_d_min = fronteira[i].second;
        }
    }

    return make_pair(aux_id, aux_d_min);
}

