#include <iostream>
#include <vector>
#include <sstream>
#include<bits/stdc++.h>

using namespace std;

//mostra o vetor
void vet_show(vector<int>& vet){
    cout << "[ ";
    for(size_t i = 0; i < vet.size(); i++)
        cout << vet[i] << " ";
    cout << "]\n";
}

void vet_rshow(vector<int>& vet){
    cout << "[ ";
    for (auto i = vet.end()-1; i >= vet.begin(); --i)
        cout << *i << ' ';
    cout << "]\n";
}

//retorna o índice que contém value ou -1 se não existir
int vet_find(vector<int>& vet, int value){
    auto it=find (vet.begin(), vet.end(), value);
    if (it != vet.end()) {  
        return it - vet.begin(); 
    } 
    else
        return -1; 
}
void remove(vector<int>& vet, size_t pos){
    auto it = vet.begin();
    it+=pos;
    vet.erase(it);
}
void inserir(vector<int>& vet, int pos, int valor){
    auto it = vet.begin();
    it+=pos;
    if(it > vet.end()){
        vet.push_back(valor);
    }else if(it>=vet.begin() && it <=vet.end()){
        vet.insert(it,valor);
    }
}
void set_in(vector<int>& vet, int pos, int valor){
    auto it = vet.begin();
    it+=pos;
    if(it >= vet.begin() && it <vet.end()){
        *it=valor;
    }
}

int main(){
    vector<int> vet;
    string line;
    while(true){
        getline(cin, line);
        stringstream ss(line);
        cout << "$" << line << "\n";
        string cmd;
        ss >> cmd; //pegando o primeiro token

        if(line == "end"){
            break;
        }else if(cmd == "add"){
            int value;
            while(ss >> value) //enquanto conseguir retirar valores
                vet.push_back(value);
        }else if(cmd == "show"){
            vet_show(vet);
        }else if(cmd == "rshow"){
            vet_rshow(vet);
        }else if(cmd == "find"){
            int valor;
            cout << "[";
            while(ss>>valor){
                int i=vet_find(vet, valor);
                if(i!=-1){
                    cout << i << " ";
                }else {
                    cout << " -1 ";
                }
            }
            cout << "]\n";
        }else if(cmd == "rmi"){
            size_t pos;
            ss >> pos;
            remove(vet,pos);
        }else if(cmd == "ins"){
            int valor, pos;
            ss >> pos >> valor;
            inserir(vet, pos , valor);
        }else if(cmd == "rma"){
            vet.clear();
        }else if(cmd == "get"){
            int pos;
            ss >> pos;
            cout << vet[pos] << "\n";
        }else if(cmd == "set"){
            int pos, valor;
            ss >> pos >> valor;
            set_in(vet, pos, valor);

        }else{
            cout << "Comando invalido\n";
        }
    }
    return 0;
}