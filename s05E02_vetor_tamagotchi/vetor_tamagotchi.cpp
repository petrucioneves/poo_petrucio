#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>


using namespace std;
string global;
class Tamagotchi{
    public:
        Tamagotchi( string nome2="0", int qtd_energia = 0, int qtd_fome=0, int qtd_limpeza=0){
            petnome=nome2;
            energiaMax=qtd_energia;
            fomeMax=qtd_fome;
            limpezaMax=qtd_limpeza;
            energia=qtd_energia;
            fome=qtd_fome;
            limpeza=qtd_limpeza;
            diamantes=idade=0;
            vida=true;
        }
        ~Tamagotchi(){}
        string getNome(){
            return petnome;
        }
        int getEnergia(){
            return energia;
        }
        int getEnergiaMax(){
            return energiaMax;
        }
        int getFomeMax(){
            return fomeMax;
        }
        int getFome(){
            return fome;
        }
        int getLimpezaMax(){
            return limpezaMax;
        }
        int getLimpeza(){
            return limpeza;
        }
        int getDiamantes(){
            return diamantes;
        }
        int getIdade(){
            return idade;
        }
        bool getVida(){
            return vida;
        }
        bool vivo(){
            if(vida==true) return true;
            else{
                cout << "fail: pet esta morto\n";
                return false;
            }
        }
        void show(){
            cout << "Nome:" << getNome() << endl
                 << "Energia:" << getEnergia() <<"/"<< getEnergiaMax() <<", "
                 << "Fome:" << getFome() <<"/"<< getFomeMax()<<", "
                 << "Limpeza:" << getLimpeza() <<"/"<< getLimpezaMax() <<", "
                 << "Diamates:" << getDiamantes() <<", Idade:"<< getIdade() << endl;
        }
        void brincar(){
            if(!vivo()){
                return;
            }
            setEnergia(getEnergia()-2);
            setFome(getFome()-1);
            setLimpeza(getLimpeza()-3);
            diamantes+=1;
            idade+=1;
        }
        void comer(){
            if(!vivo()){
                return;
            }
            setEnergia(getEnergia()-1);
            setFome(getFome()+4);
            setLimpeza(getLimpeza()-2);
            idade+=1;
        }
        void dormir(){
            if(!vivo()){
                return;
            }
            else if(getEnergiaMax()-getEnergia()<5){
                cout << "fail: nao esta com sono\n";
                return;
            }
            idade+=getEnergiaMax()-getEnergia();
            setEnergia(getEnergiaMax());
            setFome(getFome()-1);
        }
        void banhar(){
            if(!vivo()){
                return;
            }
            setEnergia(getEnergia()-3);
            setFome(getFome()-1);
            setLimpeza(getLimpezaMax());
            idade+=2;
        }
    private:
        string petnome;
        int energiaMax, fomeMax, limpezaMax;
        int energia, fome, limpeza;
        int diamantes, idade;
        bool vida;
        void setEnergia(int valor){
            if(valor<=0){
                energia=0;
                cout << "fail: pet morreu de fraqueza\n";
                vida=false;
            }else if(valor>=energiaMax){
                energia=energiaMax;
            }else{
                energia=valor;
            }
        }
        void setFome(int valor){
            if(valor<=0){
                fome=0;
                cout << "fail: pet morreu de fome\n";
                vida=false;
            }else if(valor>=fomeMax){
                fome=fomeMax;
            }else{
                fome=valor;
            }
        }
        void setLimpeza(int valor){
            if(valor<=0){
                limpeza=0;
                cout << "fail: pet morreu de sujeira\n";
                vida=false;
            }else if(valor>=limpezaMax){
                limpeza=limpezaMax;
            }else{
                limpeza=valor;
            }

        }
};
struct Jogo{
    private:
        vector<Tamagotchi> pet;                                                 //criação do vetor pet
        void remove(size_t pos){                                                //função feita para remover o pet do vetor depois que morre
            auto it = pet.begin();
            it+=pos;
            pet.erase(it);
        }
        void criar(){                                                           //função feita para criar os pets:
            cout << "$" << line << "\n";                                        //chamando e passando os paramentos para o contrutor Tamagotchi
            cout << "Digite o nome, a energia, a fome e a limpeza do seu pet:\n";
            string nome="0";
            int energia=0,fome=0,limpeza=0;
            getline(cin, line);
            stringstream ss(line);
            ss >> nome >> energia >> fome >> limpeza;
            if(nome=="0")nome="Bichinho";
            Tamagotchi *aux = new Tamagotchi(nome,energia,fome,limpeza);
            pet.push_back(*aux);
        }
        void mostrar(){                                                         //função que mostra todos os pets
            cout << "--------------------------------------------------------"<< endl;
            for(size_t i = 0; i < pet.size(); i++){
                pet[i].show();
                cout << endl;
            }
            cout << "--------------------------------------------------------"<< endl;
        }
        int procurarPet(string animal){                                         //função para procurar os pets no vetor pelo nome
            for(size_t i = 0; i < pet.size(); i++){
                if(pet[i].getNome()==animal) return i;
            }
            return 0;
        }
        void verifica(){                                                        //função feita para verificar quais os pets mortos e assim remove-los
            if(pet.size()!=0){                                                  //e assim atualiza a lista de pets no vetor
                for(size_t i = 0; i < pet.size(); i++){
                if(!pet[i].vivo()) remove(i);
                }
            }
        }
    public:
        string line;
        void comecar(string dono){
            while(true){
                verifica();
                cout << "-------------------Casa do(a) "<< dono<<"-------------------"<< endl
                     << "###########################################"<< endl
                     << "Escolha uma opção para fazer com seus pets:"<< endl
                     << "         Criar          "<< endl
                     << "          Ver           "<< endl
                     << "        Brincar         "<< endl
                     << "       Alimentar        "<< endl
                     << "         Dormir         "<< endl
                     << "         Banhar         "<< endl
                     << "          Sair          "<< endl
                     << "###########################################"<< endl
                     << "------------------------------------------------------------"<< endl;
                getline(cin, line);
                stringstream ss(line);
                string cmd;
                ss >> cmd; //pegando o primeiro token
                if(line == "sair"){
                    system("clear||cls");
                    break;
                }else if(cmd == "Criar" || cmd == "criar"){
                    system("clear||cls");
                    criar();
                }else if(cmd == "Ver" || cmd == "ver"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pet.size()==0)cout << "Você não possui pets\n";
                    else mostrar();
                }else if(cmd == "Brincar" || cmd == "brincar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pet.size()==0)cout << "Você não possui pets\n";
                    else{
                        cout << "Quais dos pets abaixo vai querer brincar?\n";
                        mostrar();
                        cout << "Digite o nome do pet desejado:\n";
                        string bicchinho;
                        getline(cin,line);
                        stringstream ss(line);
                        ss >> bicchinho;
                        pet[procurarPet(bicchinho)].brincar();
                    }
                    cout << "--------------------------------------------------------"<< endl;
                }else if(cmd == "Alimentar" || cmd == "alimentar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pet.size()==0)cout << "Você não possui pets\n";
                    else{    
                        cout << "Quais dos pets abaixo vai querer alimentar?\n";
                        mostrar();
                        cout << "Digite o nome do pet desejado:\n";
                        string bicchinho;
                        getline(cin,line);
                        stringstream ss(line);
                        ss >> bicchinho;
                        pet[procurarPet(bicchinho)].comer();
                    }
                    cout << "--------------------------------------------------------"<< endl;
                }else if(cmd == "Dormir" || cmd == "dormir"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pet.size()==0)cout << "Você não possui pets\n";
                    else{
                        cout << "Quais dos pets abaixo vai querer colocar para dormir?\n";
                        mostrar();
                        cout << "Digite o nome do pet desejado:\n";
                        string bicchinho;
                        getline(cin,line);
                        stringstream ss(line);
                        ss >> bicchinho;
                        pet[procurarPet(bicchinho)].dormir();
                    }
                    cout << "--------------------------------------------------------"<< endl;
                }else if(cmd == "Banhar" || cmd == "banhar"){
                    system("clear||cls");
                    cout << "$" << line << "\n";
                    if(pet.size()==0)cout << "Você não possui pets\n";
                    else{
                        cout << "Quais dos pets abaixo vai querer dar banho?\n";
                        mostrar();
                        cout << "Digite o nome do pet desejado:\n";
                        string bicchinho;
                        getline(cin,line);
                        stringstream ss(line);
                        ss >> bicchinho;
                        pet[procurarPet(bicchinho)].banhar();
                    }
                    cout << "--------------------------------------------------------"<< endl;
                }else{
                    cout << "Comando invalido\n";
                }
            }
        }
    
};

int main(){
    Jogo jogo;
    string nomedono;
    string line;
    cout << "Vamos começar. Digite o seu nome:\n";
    getline(cin, line);
    stringstream ss(line);
    ss >> nomedono;
    jogo.comecar(nomedono);
    return 0;
}