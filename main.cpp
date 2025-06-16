#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

class PilhaAutomato{
private:
    vector<char> pilha;
public:
    PilhaAutomato(){
        pilha.push_back('Z');
    }

    void push(char simbolo){
        pilha.push_back(simbolo);
        //cout<<"Empilhado: "<<simbolo<<endl;
    }

    void pop(){
        if(!pilha.empty()){
            //cout<<"Desempilhado: "<<pilha.back()<<endl;
            pilha.pop_back();
        }
    }

    char topo(){
        if(!pilha.empty()){
            return pilha.back();
        }else{
            return '\0';
        }
    }

    PilhaAutomato(const PilhaAutomato& outra) {
        pilha = outra.pilha; //Copia da pilha para usar nos caminhos alternativos
    }

    void exibirPilha(){
        cout<<"Pilha atual (topo -> base): ";
        for(int i = pilha.size() - 1; i >= 0; i--){
            cout<<pilha[i]<<" ";
        }
        cout<<endl;
    }

    bool estaVazia(){
        return pilha.empty();
    }
};

struct Configuracao{
    int estado;
    int posicao; // Posição na palavra
    PilhaAutomato pilha;
};

bool verificaPalavra(const string& palavra, const vector<vector<string>>& transicoes, const vector<int>& estados_finais){
    queue<Configuracao> fila;
    fila.push({0, 0, PilhaAutomato()}); //Começa no estado 0, posição 0, pilha com Z
  
    while(!fila.empty()){
        Configuracao atual = fila.front();
        fila.pop();

        string simbolo_lido=(atual.posicao<palavra.size())? string(1, palavra[atual.posicao]) : "&";

        for(const auto& transicao : transicoes){
            int estadoOrigem = stoi(transicao[0]);
            string leitura = transicao[1];
            string topoPilha = transicao[2];
            string empilhar = transicao[3];
            int proximoEstado = stoi(transicao[4]);

            bool leituraOk = (leitura == simbolo_lido || leitura == "&");
            bool topoOk = (topoPilha == string(1, atual.pilha.topo()) || topoPilha == "&");

            if(atual.estado == estadoOrigem && leituraOk && topoOk){
                Configuracao nova = atual;
                nova.estado = proximoEstado;

                if(topoPilha != "&" && !nova.pilha.estaVazia()){
                    nova.pilha.pop();
                }

                if(empilhar != "&"){
                    for(int i = empilhar.size() - 1; i >= 0; i--){
                         nova.pilha.push(empilhar[i]);
                    }
                }
                
                if(leitura != "&"){
                    nova.posicao++;
                }

                //Se consumir toda a palavra e estiver num estado final
                if(nova.posicao >= palavra.size()){
                    for(int final : estados_finais){
                        if(nova.estado == final) 
                            return true;
                    }
                }

                fila.push(nova);
            }
        }
    }
    return false;
}

int main(){
    //cout<<"variaveis qtd_estados e loop"<< endl;
    int qtd_estados, loop;
    cin >> qtd_estados >> loop;
    cin.ignore();

    vector<vector<string>> transicoes;

    for(int i=0; i<loop; i++){ //armazenando as transiçoes
        //cout <<"lendo a linha "<< i << endl;
        string linha;
        getline(cin, linha);

        stringstream ss(linha);
        string parte;
        vector<string> partes;

        while(ss >> parte){
            partes.push_back(parte);
        }
        transicoes.push_back(partes);
    }

    int num_estados_finais; //recebendo os estados finais
    cin>>num_estados_finais;
    cin.ignore();

   
    vector<int> estados_finais;
    string linha_finais;
    getline(cin, linha_finais);
    
    stringstream ssFinais(linha_finais);
    int estado_final;

    while(ssFinais >> estado_final) {
        estados_finais.push_back(estado_final);
    }
   
    vector<string> palavras;
    string linha;
    
    while(true){ //loop para receber as palavras
        //cout <<"digite a palavra: "<< endl;
        getline(cin, linha);
        if(linha == "*")
            break;
        palavras.push_back(linha);
    }

    for(const string& p : palavras){
        
        if(verificaPalavra(p, transicoes, estados_finais)){
            cout << p <<": "<<"sim"<<endl;
        }else{
            cout << p <<": "<<"nao"<<endl;
        }
    }
    return 0;
}
