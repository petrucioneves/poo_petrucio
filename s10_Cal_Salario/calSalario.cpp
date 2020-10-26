#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

class Conta{
private:
    int id;                                             //numero da conta exe-> 01 : conta
    float saldo;                                        //quanto de dinheiro ainda tem
    string idCliente;                                   //nome do cliente
    string type;                                        //CC conrrente e CP poupança
public:
    Conta(string idCliente, string type){}
    void sacar(float valor){
        if(this->saldo > 0 && )
    }
    void depositar(float valor){}
    void transferir(Conta destinataria, float valor){}
    void atualizacaoMensal(){}
};


class ContaPoupanca: public Conta{
private:
    float rendimento;
public:
    ContaPoupanca(string id, string idCliente){}
    void atualizacaoMensal(){}
    
};
class ContaCorrente: public Conta{
private:
    float tarifaMensal;
public:
    ContaCorrente(string id, string idCliente);
    void atualizacaoMensal(){}
};

class Cliente{
private:
    string id;
    map<string, Conta&> contas;
public:
    Cliente(string id): id(id){}
    
};
class Agencia{
private:
    map<string, Cliente> clientes;
    map<string, Conta> contas;
public:
    Agencia(string id);
    void adicionarCliente(string id){
        if(validarCliente(id)==true){
            clientes[id]=Cliente(id);
            contas[id]=Conta(id, "CC");
            contas[id]=Conta(id, "CP");
        }
    }
    bool validarCliente(string id){
        auto it = clientes.find(id);
        if(it == clientes.end()) return false;
        return true;
    }
};

int main(){
    return 0;;
}