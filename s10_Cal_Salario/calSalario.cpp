#include <iostream>
#include <list>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;
class Funcionario{
public:
    string nome_Func;
    int max_diarias_Func;
    int qtd_diarias_Func;
    double bonus_Func;
    double salario_Func;
    Funcionario(string nome, int max_diarias){
        this->nome_Func=nome;
        this->max_diarias_Func=max_diarias;
        this->qtd_diarias_Func=0;
    }
    void setBonus(double bonus){
        this->bonus_Func=bonus;
    }
    void addDiaria(){
        if(max_diarias_Func==0) cout << "fail: terc nao pode receber diaria\n";    
        else if(qtd_diarias_Func<max_diarias_Func) qtd_diarias_Func++;
        else if(qtd_diarias_Func==max_diarias_Func) cout << "fail: limite de diarias atingido\n";
    }
    double _calcSalario(){
        double salario;
        salario=bonus_Func+(100*qtd_diarias_Func);
        return salario;
    }
};
class Professor : public Funcionario{
public:
    string classe_Pro;
    Professor(string nome, string classe):Funcionario(nome, 2), classe_Pro(classe) {    
    }
    double calcSalario_pro(){
        double salario;
        if(this->classe_Pro == "A") salario=3000;
        else if(this->classe_Pro == "B") salario=5000;
        else if(this->classe_Pro == "C") salario=7000;
        else if(this->classe_Pro == "D") salario=9000;
        else if(this->classe_Pro == "E") salario=11000;
        salario += _calcSalario();
        return salario;
    }
    void show_prof(){
        cout.precision(12);
        cout << "Pro " << this->nome_Func << " classe " << this->classe_Pro 
            << "\n" << "Salario " << calcSalario_pro() << "\n";    
    }
};
class STA : public Funcionario{
public:
    int nivel_STA;
    STA(string nome, int nivel): Funcionario(nome, 1), nivel_STA(nivel){
    }
    double calcSalario_sta(){
        double salario= 3000 + (300*nivel_STA);
        salario += _calcSalario();
        return salario;
    }
    void show_sta(){
        cout.precision(12);
        cout << "Sta " << this->nome_Func << " nivel " << this->nivel_STA <<
            "\n" << "Salario " << calcSalario_sta() << "\n";    
    }
};

class Terceirizado: public Funcionario{
public:
    int horas_trab;
    bool insalubre;
    Terceirizado(string nome, int horas, string insalubre): Funcionario(nome, 0),horas_trab(horas){
        if(insalubre== "sim") this->insalubre=true;
        else if (insalubre== "nao") this->insalubre=false;
    }
    double calcSalario_terc(){
        double salario = (4*horas_trab)+500;
        salario += _calcSalario();
        return salario;
    }
    void show_terc(){
        cout.precision(12);
        cout << "Sta " << this->nome_Func << " " << this->horas_trab << "h" << (this->insalubre?" insalubre ":" nao insalubre ") <<
            "\n" << "Salario " << calcSalario_terc() << "\n";
    }
};
class Empresa{
public:    
    map<string, Professor*> professores;
    map<string, STA*> STa;
    map<string, Terceirizado*> tercerizado;
    int qtd_func;
    void addFuncionario_Pro(string nome, string classe){
        if(professores.count(nome)==1) return;
        professores[nome]= new Professor(nome, classe);
        qtd_func++;
    }
    void addFuncionario_STA(string nome, int nivel){
        if(STa.count(nome)==1) return;
        STa[nome]= new STA(nome, nivel);
        qtd_func++;
    }
    void addFuncionario_Ter(string nome, int horas, string insalubre){
        if(tercerizado.count(nome)==1) return;
        tercerizado[nome]= new Terceirizado(nome, horas, insalubre);
        qtd_func++;
    }
    void calBonus(double bonus){
        double bonusdiv= bonus/qtd_func;
        for(auto aux : professores){
            aux.second->bonus_Func=bonusdiv;
        }
        for(auto aux : STa){
            aux.second->bonus_Func=bonusdiv;
        }
        for(auto aux : tercerizado){
            aux.second->bonus_Func=bonusdiv;
        }
    }
    void remove_funcionario(string id){
        for(auto aux: professores)
            if(aux.first==id){
                professores.erase(id);
                qtd_func--;
                return;
            }    
        for(auto aux: STa)
            if(aux.first==id){
                STa.erase(id);
                qtd_func--;
                return;
            }    
        for(auto aux: tercerizado)
            if(aux.first==id){
                tercerizado.erase(id);
                qtd_func--;
                return;
            }    
        cout << "funcionario " << id << " nao existe\n";
    }
    void addDiara_emp(string id){
        for(auto aux: professores)
            if(aux.first==id){
                aux.second->addDiaria();
                return;
            }    
        for(auto aux: STa) 
            if(aux.first==id){
                aux.second->addDiaria();
                return;
            }    
        for(auto aux: tercerizado) 
            if(aux.first==id){
                aux.second->addDiaria();
                return;
            }
        cout << "funcionario " << id << " nao existe\n";    
    }
    void show(string id){
        for(auto aux: professores)
            if(aux.first==id){
                aux.second->show_prof();
                return;
            }    
        for(auto aux: STa) 
            if(aux.first==id){
                aux.second->show_sta();
                return;
            }    
        for(auto aux: tercerizado) 
            if(aux.first==id){
                aux.second->show_terc();
                return;
            }    
        cout << "funcionario " << id << " nao existe\n";    
    }
};
int main(){
    Empresa empresa;
    while(true){
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "end"){
            break;
        }
        else if(cmd == "addProf"){
            string nome, classe;
            ss >> nome >> classe;
            empresa.addFuncionario_Pro(nome, classe);
        }
        else if(cmd == "addSta"){
            string nome;
            int nivel;
            ss >> nome >> nivel;
            empresa.addFuncionario_STA(nome, nivel);
        }
        else if(cmd == "addTer"){
            string nome, insalubre;
            int hora;
            ss >> nome >> hora >> insalubre;
            empresa.addFuncionario_Ter(nome, hora, insalubre);
        }
        else if(cmd == "rm"){
            string nome;
            ss >> nome;
            empresa.remove_funcionario(nome);
        }
        else if(cmd == "addDiaria"){
            string nome;
            ss >> nome;
            empresa.addDiara_emp(nome);
        }
        else if(cmd == "setBonus"){
            double bonus;
            ss >> bonus;
            empresa.calBonus(bonus);
        }
        else if(cmd == "show"){
            string id;
            ss >> id;
            empresa.show(id);
        }
        else{
            cout << "fail: comando invalido";
        }
    }
    return 0;
}