#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

class Fone{
public:
    int index;
    string id;
    string fone;

    Fone(int index, string id = "", string fone = ""){
        this->index = index;
        this->id = id;
        this->fone = fone;
    }

    static bool validar(string number){
        string valid = "0123456789()-.";
        for(char c : number)
            if(valid.find(c) == string::npos)
                return false;
        return true;
    }
};

ostream& operator<<(ostream& ost, const Fone& fone){
    ost << "[" << fone.index << ":" << fone.id << ":" << fone.fone << "]";
    return ost;
}

class Contato{
public:
    string name;
    vector<Fone> fones;
    bool favoritado;
    Contato(string name = "", vector<Fone> fones = vector<Fone>()):
        name(name), fones(fones){
            this->favoritado=false;
    }

    string getName(){
        return name;
    }
    void addFone(string id, string fone){
        if(Fone::validar(fone))
            fones.push_back(Fone(this->fones.size(), id, fone));
        else
            cout << "fail: fone invalido" << endl;
    }
    void rmFone(int index){
        if(index < 0 || index >= (int) fones.size())
            return;
        fones.erase(fones.begin() + index);
        for(int i = 0; i < (int) fones.size(); i++)
            fones[i].index = i;
    }
    void rmAllFones(){
        fones.clear();
    }
    vector<Fone> getFones(){
        return fones;
    }
    bool operator<(Contato other){
        return this->name < other.name;
    }
};


ostream& operator<<(ostream& ost, Contato& contato){
    ost << (contato.favoritado ? "@" : "-");
    ost << " " << contato.getName() << " ";
    for(auto fone: contato.fones)
        cout << fone;
    ost << endl;    
    return ost;
}

template <class T>
T get(stringstream& ss){
    T t;
    ss >> t;
    return t;
}
class Agenda{
public:
    map<string, Contato> contatos;
    map<string, Contato*> favoritos;

    bool validarContato(string name){
        if(getContato(name, contatos)==nullptr) return false;
        return true;
    }
    
    bool addContato(Contato contato){
        if(getContato(contato.name, contatos)==nullptr){
            contatos[contato.name]=contato;
            return true;
        }else{
            for(Fone fon : contato.fones){
                contatos[contato.name].addFone(fon.id, fon.fone);
            }
        }
        return false;
    }
    void rmFone(string name, int index){
        if(validarContato(name)==true){ 
            contatos[name].rmFone(index);
            if(contatos[name].favoritado==true) favoritos[name]->rmFone(index);
        }        
    }
    void rmContato(string name){
        if(validarContato(name)==true){
            if(contatos[name].favoritado==true) favoritos.erase(name);
            contatos.erase(name);
        }    
    }
    Contato * getContato(string nome, map<string, Contato> aux){
        auto it = aux.find(nome);
        if(it== aux.end()) return nullptr;
        return &it->second;
    }
    map<string, Contato> search(string parttern){
        map<string, Contato> resp;
        for(auto par: contatos){
            if(par.first.find(parttern) != string::npos){
                resp[par.first]= (par.second);
            }    
        }
        return resp;
    }
    friend ostream& operator<<(ostream& ost, Agenda& agenda){
        for(auto contato : agenda.contatos)
            cout << contato.second;
        return ost;
    }
    bool favoritar(string nome){
        if(getContato(nome, contatos)!=nullptr && contatos[nome].favoritado==false){
            contatos[nome].favoritado=true;
            favoritos[nome]=&contatos[nome];
            return true;
        }
        else if(getContato(nome, contatos)==nullptr) cout << "fail: contato " << nome << " nao existe\n";
        return false;
    }
    bool desfavoritar(string nome){
        if(getContato(nome, contatos)!=nullptr && contatos[nome].favoritado==true){
            contatos[nome].favoritado=false;
            favoritos.erase(nome);
            return true;
        }
        return false;
    }
    map<string, Contato*> getFavoritos(){
        map<string, Contato*> aux;
        for(auto it: favoritos){
            aux[it.first]= it.second;
        }
        return aux;
    }
};
struct Terminal{
    void menu(){
        Agenda agenda;
        while(true){
            string line, cmd;
            getline(cin, line);
            cout << "$" << line << endl;
            stringstream ss(line);
            ss >> cmd;

            if(cmd == "end"){
                break;
            }
            else if(cmd == "add"){
                string nome;
                Contato contato;
                ss >> nome;
                contato=Contato(nome);
                string id_fone;//id:fone                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        v))Contato contato(nome);
                while(ss >> id_fone){
                    stringstream sif(id_fone); 
                    string id, fone; 
                    getline(sif, id, ':'); 
                    sif >> fone;
                    contato.addFone(id,fone);
                }
                agenda.addContato(contato);
            }
            else if(cmd == "rmContato"){
                agenda.rmContato(get<string>(ss));
            }
            else if(cmd == "rmFone"){
                string nome;
                int index;
                ss >> nome >> index;
                agenda.rmFone(nome,index);
            }
            else if(cmd == "search"){
                string parttern;
                ss >> parttern;
                for(auto aux : agenda.search(parttern)){
                    cout << aux.second; 
                }
            }
            else if(cmd == "agenda"){
                cout << agenda << "\n";
            }
            else if(cmd == "fav"){
                string nome;
                ss >> nome;
                agenda.favoritar(nome);
            }
            else if(cmd == "favorited"){
                for(auto aux: agenda.getFavoritos()){
                    cout << *aux.second; 
                }
            }
            else if(cmd == "unfav"){
                string nome;
                ss >> nome;
                agenda.desfavoritar(nome);
            }
            else{
                cout << "fail: comando invalido";
            }
        }   
    }  
};

int main(int argc, char const *argv[]){
    Terminal terminal;
    terminal.menu();
    return 0;
}
/*
int main(){
    string line;
    getline(cin, line);
    stringstream ss(line);
    string cmd;
    ss >> cmd;
    if(cmd == "add"){
        string nome;
        ss >> nome;
        string id_fone;//id:fone
        Contato contato(nome);
        while(ss >> id_fone){
            stringstream sif(id_fone);
            string id, fone;
            getline(sif, id, ':');
            sif >> fone;
            contato.addFone(id, fone);
        }
    }
    std::sort(vet.begin(), vet.end(), )
}
*/