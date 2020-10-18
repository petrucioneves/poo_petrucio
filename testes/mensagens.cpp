#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct Msg{
    string idSender;
    string text;
    Msg(string sender, string text):
        idSender(sender), text{text}{
    }
    friend ostream& operator<<(ostream& os, Msg msg){
        os << "[" << msg.idSender << ":" << msg.text << "]";
        return os;
    }
};

struct Medico{
    string id;
    vector<Msg> inbox;
    int contadorNaoLidas;
    Medico(string id = ""): id{id}, contadorNaoLidas{0}{}
    
    void send(Medico& destinatario, string text){
        Msg msg(this->id, text);
        destinatario.inbox.push_back(msg);
        destinatario.contadorNaoLidas += 1 ;
    }

    string readMsgs(){
        stringstream ss;
        for(size_t i = inbox.size() - contadorNaoLidas; i < inbox.size(); i++)
            ss << inbox[i] << "\n";
        contadorNaoLidas = 0;
        return ss.str();
    }



};
struct Paciente{
    string id;
    vector<Msg> inbox;
    int contadorNaoLidas;
    Paciente(string id = ""): id{id}, contadorNaoLidas{0}{}
    
    void send(Paciente& destinatario, string text){
        Msg msg(this->id, text);
        destinatario.inbox.push_back(msg);
        destinatario.contadorNaoLidas += 1 ;
    }

    string readMsgs(){
        stringstream ss;
        for(size_t i = inbox.size() - contadorNaoLidas; i < inbox.size(); i++)
            ss << inbox[i] << "\n";
        contadorNaoLidas = 0;
        return ss.str();
    }



};
struct Sistema{

    map<string, Medico> medicos;
    map<string, Paciente> pacientes;
    void create(string id , string name){
        if(id=="Medico") medicos[name]= Medico(name);
        else if(id=="Paciente") pacientes[name]= Paciente(name);
    }

    void send(strind id, string sender, string receiver, string text){
        
        Medico& enviador = pessoas.at(sender);
        Pessoa& receptor = pessoas.at(receiver);
        enviador.send(receptor, text);
    }

    string readMsgs(string name){
        return pessoas.at(name).readMsgs();
    }
};

int main(){
    Sistema sis;
    sis.create("joao");
    sis.create("luna");
    sis.send("joao", "luna", "ru voltou?");
    sis.send("joao", "luna", "quero voltar pra quixada");
    cout << sis.readMsgs("luna") << endl;
    
    // Pessoa joao("joao");
    // Pessoa luna("luna");
    // joao.send(luna, "ta com fome");
    // joao.send(luna, "eu to aqui dando agonia");
    // joao.send(luna, "e essa aula nao acaba");
    
    // cout << "Luna vai ler as mensagens 1" << endl;
    // cout << luna.readMsgs();
    
    // cout << "Luna vai ler as mensagens 2" << endl;
    // cout << luna.readMsgs();

    // joao.send(luna, "bora pro mclanche");
    // cout << "Luna vai ler as mensagens 3" << endl;
    // cout << luna.readMsgs();
}