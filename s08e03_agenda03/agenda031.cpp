#include <iostream>
#include <vector>
#include <list>
#include <string>
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
    string toString(){
        return "[" + this->id + " " + this->fone + "]";
    }
    friend ostream& operator<<(ostream& ost, const Fone& fone){
        ost << "[" << fone.index << ":" << fone.id << ":" << fone.fone << "]";
    return ost;
}
};

class Contato{
public:
    string name;
    vector<Fone> fones;
    bool favorito;
    Contato(string name = "", vector<Fone> fones = vector<Fone>()):
        name(name), fones(fones){
            this->favorito=false;
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
    string toString(){
        string saida = favorito ? "@" : "-";
        saida += " " + name + " ";
        for(auto fone: fones){
            saida += fone.toString();
        }
        return saida;
    }
};


template <class T>
T get(stringstream& ss){
    T t;
    ss >> t;
    return t;
}
class Agenda{
public:     
    vector<Contato*> contatos;
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
        Contato *contato=nullptr;
        if(validarContato(nome)==false){
            contato=new Contato(nome);
            contato->addFone(id,fone);
            contatos.push_back(contato);
        }    
        else{
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
    Contato * getContato(string nome){
        int i= findContato(nome, contatos);
        if(i==-1) return nullptr;
        else{
            Contato * aux= contatos[i];
            return aux;
        }
    }   
    friend ostream& operator<<(ostream& ost, Agenda agenda){
        for(Contato *contato : agenda.getContatos())
            cout << contato->toString() << endl;
        return ost;
    }
    
};

class ServicoFavoritagem{
    Agenda *agenda;
    vector<Contato*> favoritos;
    
    ServicoFavoritagem(Agenda * agenda): agenda(agenda){}
    void favoritar(string nome){
        Contato *aux= agenda->getContato(nome);
        if(aux==nullptr){
            cout << "Fail: esse contato não existe\n";
        }
        else if (aux->favorito==true){
            cout << "Fail: Esse contato já está nos favoritos\n";
        }
        else if (aux->favorito==false){
            aux->favorito==true;
            favoritos.push_back(aux);
        }
        std::sort(favoritos.begin(), favoritos.end());
    }
    void desfavoritar(string nome){
        Contato *aux= agenda->getContato(nome);
        if(aux==nullptr){
            cout << "Fail: esse contato não existe\n";
        }
        else if (aux->favorito==false){
            cout << "Fail: Esse contato não está favoritado\n";
        }
        else if (aux->favorito==true){
            aux->favorito==false;
            rmContatoFavorito(nome);
        }
        std::sort(favoritos.begin(), favoritos.end());
    }
    void rmFoneFavoritos(string name, int index){
        if(validarContato(name)==false) return;
        for(int i=0;i< (int) favoritos.size() ;i++){
            if(favoritos[i]->getName()==name){
                favoritos[i]->rmFone(index);
            }
        }
    }
    void rmContatoFavorito(string name){
        if(validarContato(name)==false) return;
        for(int i=0;i< (int) favoritos.size() ;i++){
            if(favoritos[i]->getName()==name){
                favoritos[i]->rmAllFones();
                favoritos.erase(favoritos.begin()+i);
            }
        }
    }
    Contato * getfavorito(string nome){
        int i= agenda->findContato(nome, favoritos);
        if(i==-1) return nullptr;
        else{
            Contato * aux= favoritos[i];
            return aux;
        }
    }
    vector<Contato*> getFavoritos(){
        vector<Contato*> auxFavo;
        for(int i=0;i< (int) favoritos.size() ;i++){
            auxFavo.push_back(favoritos[i]);
        }
        return auxFavo;
    }
    bool validarContato(string name){
        for(int i=0;i< (int) favoritos.size() ;i++){
            if(favoritos[i]->getName()==name) return true;
        }
        return false;
    }
};

/*struct Terminal{
    void menu(){
        Agenda agenda;
        ServicoFavoritagem servico;
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
                string id_fone;//id:fon                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         v))Contato contato(nome);
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
                agenda.servico->favoritar(nome);
            }
            else if(cmd == "favorited"){
                auto aux= agenda.servico->getFavoritos();
                for(int i=0; i<(int) aux.size(); i++){
                    cout << aux[i] << "\n"; 
                }
            }
            else if(cmd == "unfav"){
                string nome;
                ss >> nome;
                agenda.servico->desfavoritar(nome);
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