#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>
#include<stdlib.h>

using namespace std;
string global;
class Caixa{
    private:
        int saldo;
        void setSaldo(int valor){
            saldo=valor;
        }
    public:
        Caixa(int saldo=0){
            this->saldo = saldo;
        }
        ~Caixa(){}
        int getSaldo(){
            return this->saldo;
        }
        void addcaixa(){
            setSaldo(getSaldo()+2);
        }
        void subcaixa(){
            setSaldo(getSaldo()-2);
        }
    
         
};
class Kid{
    private:
        string nome;
        int idade;
        Caixa * conta ;
    public:
        Kid(string nome="0", int idade=0){
            this->nome=nome;
            this->idade=idade;
        }
        ~Kid(){}
        string toString(){
            stringstream saida;
            saida << "nome:"<< nome << " idade:" << idade;
            return saida.str();
        }
        string getNome(){
            return this->nome;
        }
        int getIdade(){
            return this->idade;
        }
};

class Trampolim{
    private:
        vector<Kid> fila;
        vector<Kid> pula_pula;
        int caixatotal;
    public:
        void chegar(string nome, int idade){
            Kid *aux= new Kid(nome,idade);
            fila.push_back(*aux);
        }
        void mostrar(){
            cout << "=>";
            
            for (int i = fila.size()-1; i >= 0; i--){
                cout << " " << fila[i].toString() << " ";
            }
            cout << "=>";
            cout << "[";
            for (int i = pula_pula.size()-1; i >= 0; i--){
                cout << " " << pula_pula[i].toString() << " ";
            }
            cout << "]\n";
        }
        void entrar(){
            auto it = fila.begin();
            pula_pula.push_back(*it);
            fila.erase(it);
        }
        int procurarkid(vector<Kid>& vetor, string nome){
            for(size_t i = 0; i < vetor.size(); i++){
                if(vetor[i].getNome()==nome) return i;
            }
        }
        bool procuraKid2(vector<Kid>& vetor, string nome){
            for(size_t i = 0; i < vetor.size(); i++){
                if(vetor[i].getNome()==nome) return true;
            }
            return false;
        }
        void remove(string nome){
            if(procuraKid2(fila,nome)==true){
                size_t vetor= procurarkid(fila, nome);
                auto it = fila.begin();
                it+=vetor;
                fila.erase(it);
            }
            else if(procuraKid2(pula_pula,nome)==true){
                size_t vetor = procurarkid(pula_pula, nome);
                auto it = pula_pula.begin();
                it+=vetor;
                pula_pula.erase(it);
            }
            else cout << "Moço, seu filho não estar aqui.\n";
        }
        void tirarUm(){
            auto it = pula_pula.begin();
            fila.push_back(*it);
            pula_pula.erase(it);
        }
        void comecar(){
            string line;
            while(true){
               // system("clear||cls");
                cout << "-------------------PULA-PULA-------------------"<< endl
                     << "###########################################"<< endl
                     << "Escolha uma opção:"<< endl
                     << "      Chegar         "<< endl
                     << "      Entrar         "<< endl
                     << "   Papai_chegou      "<< endl
                     << "       Fila          "<< endl
                     << "     Tirar_um        "<< endl
                     << "      Fechar         "<< endl
                     << "       Sair          "<< endl
                     << "###########################################"<< endl
                     << "------------------------------------------------"<< endl;
                getline(cin, line);
                stringstream ss(line);
                string cmd;
                ss >> cmd; //pegando o primeiro token
                if(line == "sair"){
                    system("clear||cls");
                    break;
                }else if(cmd == "Chegar" || cmd == "chegar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    string nome;
                    int idade;
                    while(ss >> nome >> idade) //enquanto conseguir retirar valore
                        chegar(nome, idade);
                    //system("pause");
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Entrar" || cmd == "entrar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(fila.size()!=0) entrar();
                    else cout << "Não possui mais ninguem na fila!\n";
                    //system("read enter");
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Papai_chegou" || cmd == "papai_chegou"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    string nome;
                    ss >> nome;
                    remove(nome);
                    //system("read enter");
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Fila" || cmd == "fila"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(fila.size()!=0 || pula_pula.size()!=0) mostrar(); 
                    else {
                        cout << "Aproveite a fila estar vazia!\n";
                        //system("read enter");
                    }
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Tirar_um" || cmd == "tirar_um"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pula_pula.size()!=0) tirarUm();
                    else cout << "Não possui mais ninguem no pula-pula!\n";
                    //system("read enter");
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Fechar" || cmd == "fechar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pula_pula.size()!=0 || fila.size()!=0){
                        pula_pula.clear();
                        fila.clear();
                    }
                    else cout << "O pula-pula fechou!\n";
                    //system("read enter");
                    cout << "------------------------------------------------"<< endl;
                }else{
                    system("clear||cls");
                    cout << "Comando invalido\n";
                    //system("read enter");
                    cout << "------------------------------------------------"<< endl;
                }
            }
        }
};
//+ toString(): String
int main(){
    Trampolim trampolim;
    system("clear||cls");
    trampolim.comecar();
    return 0;
}