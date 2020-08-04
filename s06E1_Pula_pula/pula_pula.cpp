#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>
#include<stdlib.h>

using namespace std;
class Caixa{
    private:
        int saldo=0;
        string nome;
        void setSaldo(int valor){
            this->saldo=valor;
        }
    public:
        Caixa(string nome, int saldo=0){
            this->nome=nome;
            this->saldo=saldo;
        }
        ~Caixa(){}
        string toString(){
            stringstream saida;
            saida << "Nome:" << nome << " Saldo:" << saldo;
            return saida.str();
        }
        string getNome(){
            return this->nome;
        }
        int getSaldo(){
            return this->saldo;
        }
        void addSaldo(){
            setSaldo(getSaldo() - getSaldo());
        }
        void subSaldo(){
            setSaldo(getSaldo()-2);
        }
};
class Kid{
    private:
        string nome;
        int idade;
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
        vector<Caixa> conta;
        int caixatotal=0;     //valor que ja recebeu
        int freceber=0;       //valor que falta receber

    public:
        int getCaixaTotal(){
            return this->caixatotal;
        }
        int getFreceber(){
            return this->freceber;
        }
        void fReceber(){
            int valor=0;
            for(size_t i=0; i<conta.size(); i++){
                valor+=conta[i].getSaldo();
            }
            this->freceber=valor;
        }
        void pagarConta(string nome){
            if(procuraConta2(conta, nome)==true){
                size_t pos=procurarConta(conta, nome);
                if(conta[pos].getSaldo()!=0){
                    this->freceber-=conta[pos].getSaldo();
                    this->caixatotal-=conta[pos].getSaldo();
                    conta[pos].addSaldo();
                }else cout << "Seu filho não deve nada!\n";
            }else cout << "Seu filho não tem conta!\n";
        }
        void criarConta(string nome){
            Caixa *aux= new Caixa(nome, 0);
            conta.push_back(*aux);
        }
        void mostrarContas(){
            for(size_t i=0; i<conta.size(); i++){
                cout << conta[i].toString() << " ";
            }
            cout << endl;
        }
        int procurarConta(vector<Caixa>& vetor, string nome){
            for(size_t i = 0; i < vetor.size(); i++){
                if(vetor[i].getNome()==nome) return i;
            }
            return 0;
        }
        bool procuraConta2(vector<Caixa>& vetor, string nome){
            for(size_t i = 0; i < vetor.size(); i++){
                if(vetor[i].getNome()==nome) return true;
            }
            return false;
        }
        void saldoConta(string nome){
            if(procuraConta2(conta, nome)==true){
                int pos=procurarConta(conta, nome);
                cout << "Saldo(Pagar): "<< conta[pos].getSaldo() << endl;
            }else cout << "Seu filho não deve nada!\n";
        }

        void chegar(string nome, int idade){
            Kid *aux= new Kid(nome,idade);
            fila.push_back(*aux);
            criarConta(nome);
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
            size_t pos=procurarConta(conta, fila[0].getNome());
            conta[pos].subSaldo();
            auto it = fila.begin();
            pula_pula.push_back(*it);
            fila.erase(it);
            fReceber();
        }
        int procurarkid(vector<Kid>& vetor, string nome){
            for(size_t i = 0; i < vetor.size(); i++){
                if(vetor[i].getNome()==nome) return i;
            }
            return 0;
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
                size_t pos=procurarConta(conta, nome);
                if(conta[pos].getSaldo()!=0){
                    this->freceber-=conta[pos].getSaldo();
                    this->caixatotal-=conta[pos].getSaldo();
                    conta[pos].addSaldo();
                }
                auto it2=conta.begin()+pos;
                conta.erase(it2);    
            }
            else if(procuraKid2(pula_pula,nome)==true){
                size_t vetor = procurarkid(pula_pula, nome);
                auto it = pula_pula.begin() + vetor;
                pula_pula.erase(it);
                size_t pos=procurarConta(conta, nome);
                if(conta[pos].getSaldo()!=0){
                    this->freceber-=conta[pos].getSaldo();
                    this->caixatotal-=conta[pos].getSaldo();
                    conta[pos].addSaldo();
                }
                auto it2=conta.begin()+pos;
                conta.erase(it2);
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
                     << "      Chegar (nome,idade)         "<< endl             //coloca quantas crianças quiser na fila
                     << "      Entrar                      "<< endl             //coloca uma criança de cada vez no pula pula
                     << "   Papai_chegou (nome)            "<< endl             //retira uma criança tanto da fila quanto do pula pula
                     << "       Fila                       "<< endl             //mostra quem esta na fila e no pula pula
                     << "      Caixa                       "<< endl             //mostra o valor total arrecadado no pula pula
                     << "   Pagar_conta (nome)             "<< endl             //paga a todo o valor que a criança deve ao pula pula
                     << "      Contas                      "<< endl             //mostra todas as contas
                     << "      Saldo (nome)                "<< endl             //mostra o saldo de uma so criança
                     << "     Tirar_um                     "<< endl             //tira uma criança do pula pula e coloca na fila de volta
                     << "      Fechar                      "<< endl             //fecha todas as contas, tira todos da fila e do pula pula
                     << "       Sair                       "<< endl             //encerra o programa
                     << "###########################################"<< endl
                     << "------------------------------------------------"<< endl;
                getline(cin, line);
                stringstream ss(line);
                string cmd;
                ss >> cmd; //pegando o primeiro token
                if(line == "sair"){
                    system("clear||cls");
                    if(fila.size()!=0||pula_pula.size()!=0||conta.size()!=0){
                        fila.clear();
                        pula_pula.clear();
                        conta.clear();
                    }
                    break;
                }else if(cmd == "Chegar" || cmd == "chegar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    string nome;
                    int idade;
                    while(ss >> nome >> idade) //enquanto conseguir retirar valore
                        chegar(nome, idade);
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Entrar" || cmd == "entrar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(fila.size()!=0) entrar();
                    else cout << "Não possui mais ninguem na fila!\n";
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Papai_chegou" || cmd == "papai_chegou"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    string nome;
                    ss >> nome;
                    remove(nome);
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Fila" || cmd == "fila"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(fila.size()!=0 || pula_pula.size()!=0) mostrar(); 
                    else {
                        cout << "Aproveite a fila estar vazia!\n";
                    }
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Caixa" || cmd == "caixa"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(getCaixaTotal()!=0 || getFreceber()<0){ 
                        cout << "Caixa do pula-pula\n"
                             <<"Saldo:" << getCaixaTotal() << endl
                             <<"Receber:" << getFreceber() << endl;
                    } 
                    else {
                        cout << "O pula pula ainda não tem saldo!\n";
    
                    }
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Pagar_conta" || cmd == "pagar_conta"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    string nome;
                    ss >> nome;
                    if(conta.size()!=0) pagarConta(nome); 
                    else {
                        cout << "Ninguem tem conta!\n";
    
                    }
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Contas" || cmd == "contas"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(conta.size()!=0) mostrarContas(); 
                    else {
                        cout << "Ninguem tem conta!\n";
    
                    }
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Saldo" || cmd == "saldo"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    string nome;
                    ss >> nome;
                    if(conta.size()!=0) saldoConta(nome); 
                    else {
                        cout << "Ninguem tem conta!\n";
    
                    }
                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Tirar_um" || cmd == "tirar_um"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pula_pula.size()!=0) tirarUm();
                    else cout << "Não possui mais ninguem no pula-pula!\n";

                    cout << "------------------------------------------------"<< endl;
                }else if(cmd == "Fechar" || cmd == "fechar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pula_pula.size()!=0 || fila.size()!=0){
                        pula_pula.clear();
                        fila.clear();
                        conta.clear();
                    }
                    else cout << "O pula-pula fechou!\n";

                    cout << "------------------------------------------------"<< endl;
                }else{
                    system("clear||cls");
                    cout << "Comando invalido\n";

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