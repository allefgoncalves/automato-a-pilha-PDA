#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>  // Para isalpha
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
        }else{
            cout<<"Erro: Pilha vazia!"<<endl;
        }
    }

    char topo(){
        if(!pilha.empty()){
            return pilha.back();
        }else{
            //cout<<"Pilha vazia!"<<endl;
            return '\0';
        }
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

bool verificaPalavra(const string& palavra, const vector<vector<string>>& transicoes, const vector<int>& estados_finais){
    PilhaAutomato pilha;
    int estado_atual = 0;
    int pos = 0;

    while(true){
        string simbolo_lido;
        if(pos < palavra.size()){
            simbolo_lido = string(1, palavra[pos]);
        }else{
            simbolo_lido = "&";
        }

        bool transicaoEncontrada = false;

        for(const auto& transicao : transicoes){
            int estadoOrigem = stoi(transicao[0]);
            string leitura = transicao[1];
            string topoPilha = transicao[2];
            string empilhar = transicao[3];
            int proximoEstado = stoi(transicao[4]);

            bool leituraOk = (leitura == simbolo_lido || leitura == "&");
            bool topoOk = (topoPilha == string(1, pilha.topo()) || topoPilha == "&");

            if(estado_atual == estadoOrigem && leituraOk && topoOk){
                if(topoPilha != "&"){
                    pilha.pop();
                }

                if(empilhar != "&"){
                    for(int i = empilhar.size() - 1; i >= 0; i--){
                        pilha.push(empilhar[i]);
                    }
                }

                estado_atual = proximoEstado;

                if(leitura != "&"){
                    pos++;
                }

                transicaoEncontrada = true;
                break;
            }
        }

        if(!transicaoEncontrada){
            break;
        }

        // Verifica se chegou ao fim da palavra e está em estado de aceitação
        if(pos >= palavra.size()){
            for(int estado_final : estados_finais){
                if(estado_atual == estado_final){
                    return true;
                }
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
        
    if(qtd_estados>0)// ajustando a quantidade de estados para começar em 0
        qtd_estados--;

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

/*
    cout << "\nTransições armazenadas:" << endl; // Exibir todas as transições lidas
    for(const auto& transicao : transicoes){
        for(const auto& elemento : transicao){
            cout << elemento << " ";
        }
        cout << endl;
    }
*/

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

/*    
    cout<<"vetor de palavras: "<< endl; //exibindo o vertor com as palavras para analizar
    for(const string& p : palavras){
            cout << p << endl;
    }
*/
    for(const string& p : palavras){
        
        if(verificaPalavra(p, transicoes, estados_finais)){
            cout << p <<": "<<"sim"<<endl;
        }else{
            cout << p <<": "<<"nao"<<endl;
        }
    }
    return 0;
}
