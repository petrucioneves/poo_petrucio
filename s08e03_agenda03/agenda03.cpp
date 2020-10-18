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
    ost << (contato.favoritado ? "@" : "- ");
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
    vector<Contato*> contatos;
    vector<Contato*> favoritos;

    int findContato(string name, vector<Contato*> aux){
        for(int i=0;i< (int) aux.size() ;i++){
            if(aux[i]->getName()==name) return i;
        }
        return -1;
    }
    bool validarContato(string name){
        for(int i=0;i< (int) contatos.size() ;i++){
            if(contatos[i]->getName()==name) return true;
        }
        return false;
    }
    
    void addContato(string nome, string id, string fone){
        Contato *contato=getContato(nome);
        if(contato == nullptr){
            contato=new Contato(nome);
            contato->addFone(id,fone);
            contatos.push_back(contato);
        }    
        else if(contato!=nullptr){
            for(int i=0; i< contatos.size(); i++){
                if(contatos[i]->getName()==nome){
                    contatos[i]->addFone(id,fone);
                }
            }
        }
        std::sort(contatos.begin(), contatos.end());
    }
    void rmFone(string name, int index){
        if(validarContato(name)==false) return;
        for(int i=0;i< (int) contatos.size() ;i++){
            if(contatos[i]->getName()==name){
                contatos[i]->rmFone(index);
            }
        }
    }
    void rmContato(string name){
        if(validarContato(name)==false) return;
        for(int i=0;i< (int) contatos.size() ;i++){
            if(contatos[i]->getName()==name){
                desfavoritar(name);
                contatos[i]->rmAllFones();
                contatos.erase(contatos.begin()+i);
            }
        }
    }
    vector<Contato*> getContatos(){
        vector<Contato*> aux;
        for(int i=0;i< (int) contatos.size() ;i++){
            aux.push_back(contatos[i]);
        }
        return aux;
    }
    vector<Contato*> search(string parttern){
        vector<Contato*> resp;
        for(auto par: contatos){
            if(par->getName().find(parttern) != string::npos){
                resp.push_back(par);
            }    
        }
        return resp;
    }
    Contato *getContato(string name){
        if(validarContato(name)==true){
            Contato *aux = contatos[findContato(name, contatos)];
            return aux;
        }return nullptr;
    }
    friend ostream& operator<<(ostream& ost, Agenda& agenda){
        for(Contato *contato : agenda.getContatos())
            cout << *contato ;
        return ost;
    }
    void favoritar(string name){
        Contato *aux= getContato(name);
        if(aux==nullptr){
            cout << "Fail: Contato não existente\n";
            return;
        }else if(aux!=nullptr && aux->favoritado == false){
            aux->favoritado=true;
            favoritos.push_back(aux);
        }else if(aux!=nullptr && aux->favoritado == true) cout << "Fail: contato já estar favoritado\n";
        std::sort(favoritos.begin(), favoritos.end());
    }
    void desfavoritar(string name){
        Contato *aux= getFavorito(name);
        if(aux->favoritado == true){
            aux->favoritado=false;
            aux->rmAllFones();
            favoritos.erase(favoritos.begin()+findContato(name, favoritos));
        }else if(aux->favoritado == false) cout << "Fail: contato não estar favoritado\n";
    }
    vector<Contato*> getFavoritos(){
        vector<Contato*> aux;
        for(int i=0;i< (int) favoritos.size() ;i++){
            aux.push_back(favoritos[i]);
        }
        return aux;
    }
    Contato *getFavorito(string name){
        if(findContato(name, favoritos) !=-1){
            Contato *aux = favoritos[findContato(name,favoritos)];
            return aux;
        }return nullptr;
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
                ss >> nome;
                string id_fone;//id:fone                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        v))Contato contato(nome);
                while(ss >> id_fone){
                    stringstream sif(id_fone); 
                    string id, fone; 
                    getline(sif, id, ':'); 
                    sif >> fone; 
                    agenda.addContato(nome,id,fone); 
                }
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
                auto aux=agenda.search(parttern);
                for(int i=0; i<(int) aux.size(); i++){
                    cout << aux[i] << "\n"; 
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
                auto aux= agenda.getFavoritos();
                for(int i=0; i<(int) aux.size(); i++){
                    cout << *aux[i]; 
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