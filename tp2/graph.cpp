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
void Graph::ImprimeMatriz(int** matriz){
    cout << "[USERS \\ JOBS]" << endl;
    cout << " " << setw(TAM_NUM) << " ";
    
    for (int j = 0; j < this->_matriz_N_J; j++) {
        cout << "[" << right << setw(TAM_NUM - 1) << j << "]";
    }
    
    cout << endl;

    for (int i = 0; i < this->_matriz_M_U; i++) {
        cout << "[" << right << setw(TAM_NUM - 1) << i << "]";
        for (int j = 0; j < this->_matriz_N_J; j++) {
            if(matriz[i][j] == 0) {
            cout << right << setw(TAM_NUM) << "_" << " ";
            } else {
                cout << right << setw(TAM_NUM) << matriz[i][j] << " ";
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
    this->_matriz_M_U = n_users;
    this->_matriz_N_J = n_jobs;
    this->_matriz = this->InicializaMatriz();

    this->_id_prox_user = 0;
    this->_id_prox_job = 0;

    for (int i = 0; i < this->_matriz_N_J; i++){
        this->_usersEmCadaJob[i] = -1;
    }

}

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
int** Graph::InicializaMatriz() {

    int** grafo_matriz = new int* [this->_matriz_M_U];
    
    for (int i = 0; i < _matriz_M_U; i++){

        grafo_matriz[i] = new int[this->_matriz_N_J];
        for (int j = 0; j < _matriz_N_J; j++) {
            
            grafo_matriz[i][j] = 0;
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

    this->_matriz[aux_u][aux_j] = 1;
}






















































/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
bool Graph::BuscaJob(int u, int* jobsExplorados, int* jobsAlocados){

    // Dado o USER u, vamos iterarar na matriz por todos os JOBS j
    for (int j = 0; j < this->_matriz_N_J; j++){
        
        // USER tem interesse no JOB
        if (this->_matriz[u][j] == 1){

            // USER ainda não explorou o JOB j
            if(jobsExplorados[j] == 0){
                jobsExplorados[j] = 1;

                int atual_user_alocado = jobsAlocados[j];
    
                // Não há nenhum USER alocado para o JOB j
                if (atual_user_alocado == -1){
                    jobsAlocados[j] = u;
                    return true;

                // Chama a 'BuscaJob' para o atual USER alocado para o JOB e vê se é possível alocá-lo em outro JOB
                } else if(BuscaJob(atual_user_alocado, jobsExplorados, jobsAlocados)){
                    jobsAlocados[j] = u;
                    return true;
                }

            }
        }
    }
    return false;
}
/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
int Graph::AlgoritmoExato(){

    // Cria e inicializa uma array para guardar qual JOB está com qual USER agora
    int jobsAlocados[this->_matriz_N_J];
    for (int i = 0; i < this->_matriz_N_J; i++){
        jobsAlocados[i] = -1;
    }

    // Itera por todos os USERS, buscando um JOB para alocá-los
    for (int u = 0; u < this->_matriz_M_U; u++){
        int jobsExplorados[this->_matriz_N_J];
        for (int i = 0; i < this->_matriz_N_J; i++){
            jobsExplorados[i] = 0;
        }
 
        BuscaJob(u, jobsExplorados, jobsAlocados);
    }

    // Perpassa por toda a array de 'jobsAlocados' e verifica quantos JOBS de fato foram associados a algum USER.
    int alocs_totais = 0;
    for (int i = 0; i < this->_matriz_N_J; i++){
        if (jobsAlocados[i] != -1){
            alocs_totais++;
        }
    }

    return alocs_totais;
}
