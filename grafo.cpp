#include "grafo.hpp"

using namespace std;

// auxilio para ler do txt
string slice(string v, int m, int n)
{

      auto first = v.cbegin() + m;
      auto last = v.cbegin() + n + 1;

      string vec(first, last);
      return vec;
  
}

// auxilio para ler do txt
void split(string vec, string &a, string &b){

    int space=0;
    for(int i=0;i<(int)vec.size();i++){

        if(vec[i]==' ')
            space = i;
            
    }


    a = slice(vec,0,space-1);
    b = slice(vec,space+1,vec.size()-1);



}

// faz a matriz de adjacencia a partir do arquivo pre_requisitos.txt, a ordem deve ser a mesta apresentada no grafo.hpp de 0 a ...
vector<node*> getGrafo(){

    
    ifstream fp;

    fp.open("pre_requisitos.txt");
    
    if(!fp.is_open()){
        cout << "Falha ao abrir aquivo" << endl;
        exit(1);
    }

    string line;
    string a;
    string b;
    vector<t_node*> grafo;



    getline(fp,line,'\n');

    split(line,a,b);

    grafo.resize(stoi(a));

    for(unsigned i=0;i<grafo.size();i++){


        t_node* aux = new t_node;
        aux->disciplina = disciplinas[i];
        aux->grau = 0;
        grafo[i] = aux;
        

    }
        
    // peenche lista de adjacencia
    while(getline(fp,line)){


        split(line,a,b);

        grafo[stoi(a)]->adj.push_back(grafo[stoi(b)]);


    }

    // seta os graus
    for(unsigned i=0;i<grafo.size();i++){

        for(unsigned j=0;j<grafo[i]->adj.size();j++){

            grafo[i]->adj[j]->grau = grafo[i]->adj[j]->grau + 1;

        }

    }



    fp.close();

    return grafo;

}


// ordemnação topológica por bfs com prioridade de pesos das arestas(creditos da materia)
struct compare { 
    bool operator()(t_node* const& p1, t_node* const& p2) 
    { 
 
        return get<1>(p1->disciplina) > get<1>(p2->disciplina); 
    } 
}; 

vector<t_node*> ordenacaoTopologica(vector<t_node*> grafo){

    vector<t_node*> ordenacao;

    // inicia fila com graus 0
    
    std::priority_queue<t_node*,vector<t_node*>,compare> fila;

    for(unsigned i=0;i<grafo.size();i++){
        if(grafo[i]->grau==0)
            fila.push(grafo[i]);
    }

    while(!fila.empty()){

        t_node* aux = fila.top();
        fila.pop();
        

        ordenacao.push_back(aux);

        for(unsigned i=0;i<aux->adj.size();i++){
            aux->adj[i]->grau --;
            if(aux->adj[i]->grau == 0)
                fila.push(aux->adj[i]);
        }


    }

    if(grafo.size() != ordenacao.size()){
        cout << "Nao ah ordenacao topologica" << endl;
        exit(1);
    }

    return ordenacao;
   

}

// maior caminho partindo de um vertice
vector<t_node*> caminho(t_node* noInicial, bool porPesos, vector<t_node*> exclude){

    vector<t_node*> aux;
    aux.push_back(noInicial);


    vector<t_node*> aux3;
    for(unsigned i=0;i<noInicial->adj.size();i++){

        vector<t_node*> aux2 = caminho(noInicial->adj[i],porPesos, exclude);

        if(!porPesos){
            if(aux3.size() < aux2.size())
                aux3 = aux2;
        }
        else{

            int sumA =0;
            int sumB =0;
            for(unsigned j =0;j< aux3.size();j++){
                sumA += get<1>(aux3[j]->disciplina);
            }
            for(unsigned j =0;j< aux2.size();j++){
                sumB += get<1>(aux2[j]->disciplina);
            }
            if(sumA < sumB && search(exclude.begin(), exclude.end(), aux2.begin(), aux2.end()) == exclude.end())
                aux3 = aux2;


            }
    
    }

     aux.insert(aux.end(),aux3.begin(),aux3.end());

    return aux;

}


// maior caminho dentro todos os vertices da ordem topologica
pair<vector<t_node*>,vector<t_node*>> caminhoCritico(vector<t_node*> ordem, bool porPesos){

    vector<t_node*> caminhoCritic ;
    vector<t_node*> caminhoCritic2 ;
    for(unsigned i=0;i<ordem.size();i++){
        
        vector<t_node*> aux = caminho(ordem[i],porPesos,vector<t_node*>{});

        if(!porPesos){
            if(caminhoCritic.size() <  aux.size()){
                caminhoCritic = aux;
            }
        }
        else{

            int sumA =0;
            int sumB =0;
     

            for(unsigned j =0;j< caminhoCritic.size();j++){
                sumA += get<1>(caminhoCritic[j]->disciplina);
            }
           
            for(unsigned j =0;j< aux.size();j++){
                sumB += get<1>(aux[j]->disciplina);
            }
            if(sumA < sumB)
                caminhoCritic = aux;

        }

        aux = caminho(ordem[i],porPesos,caminhoCritic);


        if(!porPesos){

            if(caminhoCritic2.size() <  aux.size() && search(caminhoCritic.begin(), caminhoCritic.end(), aux.begin(), aux.end()) == caminhoCritic.end()){
                caminhoCritic2 = aux;
            }
        }
        else{

            int sumB =0;
            int sumC =0;

            for(unsigned j =0;j< caminhoCritic2.size();j++){
                sumC += get<1>(caminhoCritic2[j]->disciplina);
            }
            for(unsigned j =0;j< aux.size();j++){
                sumB += get<1>(aux[j]->disciplina);
            }


            if(sumC < sumB)
                caminhoCritic2 = aux;


        }

       
    }

    return pair<vector<t_node*>, vector<t_node*>>(caminhoCritic,caminhoCritic2);

}

void printGraph(  vector<t_node*> grafo ,string filename ){

    ofstream fp;

    fp.open(filename);


    fp << "digraph {" << endl;
    for(int i=0;i<(int)grafo.size();i++){

        if(grafo[i]->adj.size() == 0)
            fp << get<2>(grafo[i]->disciplina) << ";" << endl;

        for(int j=0;j<(int)grafo[i]->adj.size();j++){

            fp << get<2>(grafo[i]->disciplina) << " -> ";

            fp << get<2>(grafo[i]->adj[j]->disciplina) << ";";

            fp << endl;

            
        }
    
    }

    fp << "}";

    fp.close();



}

void printOrdem(vector<t_node*> grafo , vector<t_node*> ordem, string filename){

    ofstream fp;

    fp.open(filename);


    fp << "digraph {" << endl;

    fp << "rankdir= LR ; "<< endl;  

    for(int i=0;i<20;i++){
        fp << "subgraph {" << endl;

        fp << "node[style=field, color=lightgrey];" << endl;

        for(unsigned i=0;i<ordem.size()-1;i++){
            fp << get<2>(ordem[i]->disciplina) << " -> ";
        }
        fp << get<2>(ordem[ordem.size() -1]->disciplina) << endl;

        fp << "[color = black, style=dotted];" << endl;

        fp << "}" << endl;
    }

    for(int i=0;i<(int)grafo.size();i++){

        if(grafo[i]->adj.size() == 0)
            fp << get<2>(grafo[i]->disciplina) << ";" << endl;

        for(int j=0;j<(int)grafo[i]->adj.size();j++){

            fp << get<2>(grafo[i]->disciplina) << " -> ";

            fp << get<2>(grafo[i]->adj[j]->disciplina) << ";";

            fp << endl;

            
        }
    
    }

    fp << "}";

    fp.close();

}

void printCritpath(vector<t_node*> grafo ,vector<t_node*> ordem,  vector<t_node*> caminhoCrit, string filename){

    ofstream fp;

fp.open(filename);


    fp << "digraph {" << endl;

    fp << "rankdir= LR ; "<< endl;  

    for(int i=0;i<20;i++){
        fp << "subgraph {" << endl;

        fp << "node[style=field, color=lightgrey];" << endl;

        for(unsigned i=0;i<ordem.size()-1;i++){
            fp << get<2>(ordem[i]->disciplina) << " -> ";
        }
        fp << get<2>(ordem[ordem.size() -1]->disciplina) << endl;

        fp << "[color = white, style=dotted];" << endl;

        fp << "}" << endl;

    }

        fp << "subgraph {" << endl;

        fp << "node[style=field, color=lightgrey];" << endl;

        for(unsigned i=0;i<caminhoCrit.size()-1;i++){
            fp << get<2>(caminhoCrit[i]->disciplina) << " -> ";
        }
        fp << get<2>(caminhoCrit[caminhoCrit.size() -1]->disciplina) << endl;

        fp << "[color = red];" << endl;

        fp << "}" << endl;

    for(int i=0;i<(int)grafo.size();i++){

        if(grafo[i]->adj.size() == 0)
            fp << get<2>(grafo[i]->disciplina) << ";" << endl;

        for(int j=0;j<(int)grafo[i]->adj.size();j++){

            fp << get<2>(grafo[i]->disciplina) << " -> ";

            fp << get<2>(grafo[i]->adj[j]->disciplina) << ";";

            fp << endl;

            
        }
    
    }

    fp << "}";

    fp.close();


}


// main e prints de listas de adjacencias e ordens 
int main(int argc, char *argv[] ){


    // grafo
    vector<t_node*> grafo  = getGrafo();
    for(int i=0;i<(int)grafo.size();i++){

        cout << get<2>(grafo[i]->disciplina) << " ("<< get<0>(grafo[i]->disciplina) << ") "<< " {"<< grafo[i]->grau << "} " << " -- ";

        for(int j=0;j<(int)grafo[i]->adj.size();j++){

            cout << get<2>(grafo[i]->adj[j]->disciplina) << " (" << get<0>(grafo[i]->adj[j]->disciplina)  << ") "<< " [" << get<1>(grafo[i]->adj[j]->disciplina) << "] ";
        }
        cout << endl;

    }

    // ordem topologica 
    vector<t_node*> ordem = ordenacaoTopologica(grafo);
    cout << endl;
    for(unsigned i=0;i<ordem.size();i++){
        cout << get<2>(ordem[i]->disciplina) << " (" << get<0>(ordem[i]->disciplina) << ") ";
    }
    cout << endl;


    // caminho critico
    pair<vector<t_node*>,vector<t_node*>> caminhos = caminhoCritico(ordem,true);
    
    vector<t_node*> caminhoCrit1 = get<0>(caminhos);
    vector<t_node*> caminhoCrit2 = get<1>(caminhos);
    int sum=0;

    cout << endl;
    for(unsigned i=0;i<caminhoCrit1.size();i++){
        cout << get<2>(caminhoCrit1[i]->disciplina) << " (" << get<0>(caminhoCrit1[i]->disciplina) << ") ";
    }

    sum=0;
    for(unsigned j =0;j< caminhoCrit1.size();j++){
        sum += get<1>(caminhoCrit1[j]->disciplina);
    }
    cout << " == " << sum;
    cout << endl;


    for(unsigned i=0;i<caminhoCrit2.size();i++){
        cout << get<2>(caminhoCrit2[i]->disciplina) << " (" << get<0>(caminhoCrit2[i]->disciplina) << ") ";
    }
 

    sum=0;
    for(unsigned j =0;j< caminhoCrit2.size();j++){
        sum += get<1>(caminhoCrit2[j]->disciplina);
    }
    cout << " == " << sum;

    cout << endl;

    

    printGraph(grafo,"grafo.txt");
    printOrdem(grafo,ordem,"ordem.txt");
    printCritpath(grafo,ordem,caminhoCrit1,"critpath.txt");
    printCritpath(grafo,ordem,caminhoCrit2,"critpath2.txt");

    


    

    
    
}
