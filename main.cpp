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
        cout<<"Empilhado: "<<simbolo<<endl;
    }

    void pop(){
        if(!pilha.empty()){
            cout<<"Desempilhado: "<<pilha.back()<<endl;
            pilha.pop_back();
        }else{
            cout<<"Erro: Pilha vazia!"<<endl;
        }
    }

    char topo(){
        if(!pilha.empty()){
            return pilha.back();
        }else{
            cout<<"Pilha vazia!"<<endl;
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

int main(){
    PilhaAutomato pilha;
    /*
    //funçoes exemplo para manipulação da pilha
    pilha.push('a'); //adiciona a 
    pilha.exibirPilha(); //exibe a pilha 
    pilha.pop(); // remove do topo
    cout << "Topo da pilha: " << pilha.topo() << endl; //exibe o topo
    */
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
    }*/
   
    vector<string> palavras;
    string linha;
    while(true){ //loop para receber as palavras
        //cout <<"digite a palavra: "<< endl;
        getline(cin, linha);
        if(linha == "*")
            break;

        palavras.push_back(linha);
    }
    
    cout<<"vetor de palavras: "<< endl; //exibindo o vertor com as palavras para analizar
    for(const string& p : palavras){
            cout << p << endl;
    }
/*
    for(const auto& transicao : transicoes){
            int estadoOrigem = stoi(transicao[0]);
    }
*/
    return 0;
}
