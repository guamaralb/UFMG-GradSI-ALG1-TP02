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


    this->_usersEmCadaJob = new int[_matriz_N_J];
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
int* Graph::InicializaVetorN() {

    int* vetor = new int [this->_matriz_N_J];
    
    for (int i = 0; i < this->_matriz_N_J; i++){
        vetor[i] = -1;
    }

    return vetor;
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
bool Graph::EncontraJobDisponivel(int u, int* jobsExplorados){

    // Dado o USER u, vamos iterarar na matriz por todos os JOBS j
    for (int j = 0; j < this->_matriz_N_J; j++){
        
        // USER tem interesse no JOB
        if (this->_matriz[u][j] == 1){

            // USER ainda não explorou o JOB j
            if(jobsExplorados[j] == 0){
                jobsExplorados[j] = 1;

                int atual_user_alocado = this->_usersEmCadaJob[j];
    
                // Não há nenhum USER alocado para o JOB j
                // - Nesse caso, o atual USER é automaticamente alocado no JOB j
                if (atual_user_alocado == -1){
                    this->_usersEmCadaJob[j] = u;
                    return true;

                // Chama a 'EncontraJobDisponivel' para o atual USER alocado para o JOB e vê se é possível alocá-lo em outro JOB
                // - Nesse caso, a chamada recursiva funciona verificando se o USER que atualmente ocupa a vaga que
                //   o USER u "deseja" pode ser alocado em outro JOB. Caso esse outro USER somente possa ocupar uma
                //   vaga já ocupada por um terceiro USER, então a função é chamada mais uma vez, e assim sucessivamente.
                } else if(EncontraJobDisponivel(atual_user_alocado, jobsExplorados)){
                    this->_usersEmCadaJob[j] = u;
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

    this->_usersEmCadaJob = this->InicializaVetorN();

    // Itera por todos os USERS, buscando um JOB para alocá-los
    for (int u = 0; u < this->_matriz_M_U; u++){
        int jobsExplorados[this->_matriz_N_J];
        for (int i = 0; i < this->_matriz_N_J; i++){
            jobsExplorados[i] = 0;
        }
 
        EncontraJobDisponivel(u, jobsExplorados);
    }

    // Perpassa por toda a array de 'jobsAlocados' e verifica quantos JOBS de fato foram associados a algum USER.
    int alocs_totais = 0;
    for (int i = 0; i < this->_matriz_N_J; i++){
        if (this->_usersEmCadaJob[i] != -1){
            alocs_totais++;
        }
    }

    return alocs_totais;
}
