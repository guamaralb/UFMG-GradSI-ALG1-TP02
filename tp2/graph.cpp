#include "graph.hpp"
#include <iostream>
#include <iomanip>
#include <queue>

#define TAM_TEXT 25
#define TAM_NUM 5

using namespace std;

/*/--------------------------------------------------------------------//
APAGAR
//--------------------------------------------------------------------/*/
void Graph::ImprimeMatriz(){
    //cout << "[JOBS \\ USERS]" << endl;
    cout << " " << setw(TAM_NUM) << " ";
    
    for (int j = 0; j < this->_matriz_M; j++) {
        cout << "[" << right << setw(TAM_NUM - 1) << j << "]";
    }
    
    cout << endl;

    for (int i = 0; i < this->_matriz_N; i++) {
        cout << "[" << right << setw(TAM_NUM - 1) << i << "]";
        for (int j = 0; j < this->_matriz_M; j++) {
            if(this->_matriz[i][j] == -1) {
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
        cout << right << setw(TAM_NUM) << x.second << " : " << left << setw(TAM_TEXT) << x.first << endl;
    }
}

/*/--------------------------------------------------------------------//
APAGAR
//--------------------------------------------------------------------/*/
void Graph::ImprimeJobsMap(){
    cout << "--- JOBS (" << this->_jobs.size() << ") ---" << endl;
    for (auto& x: this->_jobs){
        cout << right << setw(TAM_NUM) << x.second << " : " << left << setw(TAM_TEXT) << x.first << endl;
    }
}


/*/--------------------------------------------------------------------//
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
//--------------------------------------------------------------------/*/




/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
Graph::Graph(int n_users, int n_jobs) {
    this->_matriz_N = n_jobs;
    this->_matriz_M = n_users;
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
bool Graph::ProcuraEAdicionaNoMap(map<string, int>& map, string s, int i, int& aux){

    std::map<string,int>::iterator it; 
    it = map.find(s);

    if(it == map.end()){
        map.emplace(s, i);
        aux = i;
        return true;
    } else{
        aux = it->second;
        return false;
    }

}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
void Graph::AdicionaAresta(string u, string j){

    int aux_u = -1;
    int aux_j = -1;
    

    if(ProcuraEAdicionaNoMap(this->_users, u, this->_id_prox_user, aux_u)){
        this->_id_prox_user++;
    }

    if(ProcuraEAdicionaNoMap(this->_jobs, j, this->_id_prox_job, aux_j)){
        this->_id_prox_job++;
    }

    this->_matriz[aux_j][aux_u] = 1;
}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
void Graph::BFS(int n, int m){
    cout << n << " - " << m << endl;
    
}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
int Graph::AlgoritmoGuloso(){


    if(this->_jobs.size() < this->_users.size())
        return this->_jobs.size();
    else
        return this->_users.size();
}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
int Graph::AlgoritmoExato(){

    this->BFS(0, 0);
    /*
    for(int i = 0; i < this->_matriz_N; i++){
        for(int j = 0; j < this->_matriz_M; j++){
            if(this->_matriz[i][j] == 1){
                this->BFS(i, j);
            }
        }
    }
    */

    if(this->_jobs.size() < this->_users.size())
        return this->_jobs.size();
    else
        return this->_users.size();
}

