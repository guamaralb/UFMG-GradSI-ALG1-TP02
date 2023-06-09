#include "graph.hpp"

using namespace std;

/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
Graph::Graph(int n_users, int n_jobs) {
    this->_matriz_M_U = n_users;
    this->_matriz_N_J = n_jobs;
    this->_matriz = this->InicializaMatriz();

    this->_id_prox_user = 0;
    this->_id_prox_job = 0;


    this->_alocacoesUserPorJob = new int[_matriz_N_J];
    for (int i = 0; i < this->_matriz_N_J; i++){
        this->_alocacoesUserPorJob[i] = -1;
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
int* Graph::InicializaVetor(int tam, int valor) {

    int* vetor = new int [tam];
    
    for (int i = 0; i < tam; i++){
        vetor[i] = valor;
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
int Graph::AlgoritmoGuloso(){

    this->_alocacoesUserPorJob = this->InicializaVetor(this->_matriz_N_J, -1);
    int* _usersJaAlocados = this->InicializaVetor(this->_matriz_M_U, -1);

    int alocs_totais = 0;

    // Itera por todos os JOBS, buscando um USER que o listou
    for (int j = 0; j < this->_matriz_N_J; j++){
        for (int u = 0; u < this->_matriz_M_U; u++){
            if(this->_matriz[u][j] == 1 && _usersJaAlocados[u] == -1){
                this->_alocacoesUserPorJob[j] = 1;
                _usersJaAlocados[u] = 1;
                alocs_totais++;
                break;
            }
        }
     }

    // Perpassa por toda a array de 'jobsAlocados' e verifica quantos JOBS de fato foram associados a algum USER.
    for (int i = 0; i < this->_matriz_N_J; i++){
        if (this->_alocacoesUserPorJob[i] != -1){
        }
    }

    return alocs_totais;
}


/*/--------------------------------------------------------------------//
//--------------------------------------------------------------------/*/
bool Graph::EncontraJobDisponivel(int u, int* jobsExplorados){

    // Dado o USER u, itera por todos os JOBS
    for (int j = 0; j < this->_matriz_N_J; j++){
        
        // USER tem interesse no JOB
        if (this->_matriz[u][j] == 1){

            // USER ainda não explorou o JOB
            if(jobsExplorados[j] == 0){
                jobsExplorados[j] = 1;

                int atual_user_alocado = this->_alocacoesUserPorJob[j];
    
                // Não há nenhum USER alocado para o JOB
                if (atual_user_alocado == -1){
                    this->_alocacoesUserPorJob[j] = u;
                    return true;

                // Chama a 'EncontraJobDisponivel' para o atual USER alocado para o JOB e vê se é possível alocá-lo em outro JOB
                // - Nesse caso, a chamada recursiva funciona verificando se o USER que atualmente ocupa a vaga que
                //   o USER u "deseja" pode ser alocado em outro JOB. Caso esse outro USER somente possa ocupar uma
                //   vaga já ocupada por um terceiro USER, então a função é chamada mais uma vez, e assim sucessivamente.
                } else if(EncontraJobDisponivel(atual_user_alocado, jobsExplorados)){
                    this->_alocacoesUserPorJob[j] = u;
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

    this->_alocacoesUserPorJob = this->InicializaVetor(this->_matriz_N_J, -1);

    // Itera por todos os USERS, buscando um JOB para alocá-los
    for (int u = 0; u < this->_matriz_M_U; u++){

        // Array auxiliar que registra as vagas que já foram exploradas para este candidato
        int* jobsExplorados = this->InicializaVetor(this->_matriz_N_J, 0);
 
        EncontraJobDisponivel(u, jobsExplorados);
    }

    // Perpassa por toda a array de 'jobsAlocados' e verifica quantos JOBS de fato foram associados a algum USER.
    int alocs_totais = 0;
    for (int i = 0; i < this->_matriz_N_J; i++){
        if (this->_alocacoesUserPorJob[i] != -1){
            alocs_totais++;
        }
    }

    return alocs_totais;
}