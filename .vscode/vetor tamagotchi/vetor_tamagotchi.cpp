#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>

using namespace std;
class Tamagotchi{
    public:
        Tamagotchi(int qtd_energia = 0, int qtd_fome=0, int qtd_limpeza=0){
            energiaMax=qtd_energia;
            fomeMax=qtd_fome;
            limpezaMax=qtd_limpeza;
            energia=qtd_energia;
            fome=qtd_fome;
            limpeza=qtd_limpeza;
            diamantes=idade=0;
            vida=true;
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
        void criarpet(Tamagotchi npet){


        }
        void show(){
            cout << "E:"<< getEnergia() <<"/"<< getEnergiaMax() <<", ";
            cout << "S:"<< getFome() <<"/"<< getFomeMax()<<", ";
            cout << "L:"<< getLimpeza() <<"/"<< getLimpezaMax() <<", ";
            cout << "D:"<< getDiamantes() <<", I:"<< getIdade() <<endl;
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
        vector <Tamagotchi> pet;
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
    Tamagotchi pet;
    void comecar(){
        string line;
        while(true){
            getline(cin, line);
            stringstream ss(line);
            cout << "$" << line << "\n";
            string cmd;
            ss >> cmd; //pegando o primeiro token
            if(line == "end"){
                break;
            }else if(cmd == "init"){
                int energia,fome,limpeza;
                ss >> energia >> fome >> limpeza;
                pet=Tamagotchi(energia,fome, limpeza);
            }else if(cmd == "show"){
                pet.show();
            }else if(cmd == "play"){
                pet.brincar();
            }else if(cmd == "eat"){
                pet.comer();
            }else if(cmd == "sleep"){
                pet.dormir();
            }else if(cmd == "shower"){
                pet.banhar();
            }else{
                cout << "Comando invalido\n";
            }
        }
    }
};

int main(){
    Jogo jogo;
    string line;
    string cmd;
    while(true){
        cout << "---------INÍCIO---------"
             << "         Começar        "
             << "          Sair          "
             << "------------------------";
            getline(cin, line);
            stringstream ss(line);
            ss >> cmd;
            if(cmd == "começar" || cmd == "comecar"){
                jogo.comecar();
            }
            else if(cmd=="sair"){
                return false;
            }else{
                cout << "Comando invalido\n";
            }
    }
    return 0;
}