#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
struct Espiral{
    //atributos
    std::string nome;
    int qtd=0;
    float preco=0.0;
    
    Espiral(std::string nome= "", int qtd=0, float preco=0.00){
        this->nome=nome;
        this->qtd=qtd;
        this->preco=preco;
    }
    std::string toString(){
        std::stringstream saida;
        if(nome==""){
            saida << " [ empty : " << std::to_string(qtd) << " U : " <<std::to_string(preco) << " RS ]";
            return saida.str();
        }
        saida << " [ " << nome << " : " << std::to_string(qtd) << " U : " << std::to_string(preco) << " RS ]";
        return saida.str();
    }
};

struct Maquina{
    std::vector<Espiral> espirais;
    float saldoCliente=0;
    float lucro=0;
    int maxProdutos=0;
    public:
        Maquina(int nespirais, int maxProdutos){
            this->maxProdutos=maxProdutos;
            
            for(int i=0; i<nespirais;i++){
                Espiral *aux=new Espiral();
                espirais.push_back(*aux);
            }
        }
        std::string toString2(){
            std::stringstream saida;
            saida << "Saldo:"<< std::to_string(saldoCliente) << "\n";
            for(int i=0; i< espirais.size(); i++){
                saida << std::to_string(i)  << espirais[i].toString()<<"\n";
            }
            return saida.str();
        }
        float getSaldo(){
            return this->saldoCliente;
        }
        bool alterarEspiral(int indice, std::string nome, int qtd, float preco){
            //1. Não pegar um indice que nao existe
            if(indice < 0 || indice >= (int) espirais.size()){    
                std::cout << "fail: indice invalido\n";
                return false;
            }
            //2. Não colocar um produto em uma espiral ocupada
            if(espirais[indice].nome!=""){
                std::cout << "fail: espiral ocupada\n";
                return false;
            }
            if(qtd>this->maxProdutos){
                std::cout << "fail: Não cabe essa quantidade de produtos\n";
                return false;
            }
            //3. Não inserir um produto se ele já existe
            for(int i=0; i<espirais.size(); i++){
                if(espirais[i].nome == nome){
                    std::cout << "fail: pessoa ja esta no cinema\n";
                    return false;
                }
            }
            Espiral *aux=new Espiral(nome, qtd, preco);
            espirais[indice] = *aux;
            return true;
        }
        float pedirTroco(){
            float aux=this->saldoCliente;
            this->saldoCliente=0;
            return aux;
        }
        bool inserirDinheiro(float valor){
            this->saldoCliente+=valor;
            return true;
        }
        bool vender(int indice){
            if(espirais[indice].nome==""){
                std::cout <<"fail: não tem nada nessa espiral\n";
            }
            else if(espirais[indice].qtd==0){
                std::cout <<"fail: não tem mais produto nessa espiral\n";
            }
            else if(getSaldo()>0 && getSaldo()>= espirais[indice].preco && espirais[indice].qtd>0){
                this->saldoCliente-=espirais[indice].preco;
                espirais[indice].qtd-=1;
                return true;
            }
            std::cout <<"fail: Você não tem saldo suficiente\n";
            return false;
        }
        void remove(int indice){
            auto i= espirais.begin();
            i+=indice;
            espirais.erase(i);
            Espiral *aux=new Espiral();
            espirais.push_back(*aux);
        }
        void removeAll(){
            espirais.clear();
        }
};
struct Terminal{
    Maquina *maquina;
    void painel(){
        std::string line;
        while(true){
            std::cout << "-------------Junkfood-------------"<< std::endl
                      << "##################################"<< std::endl
                      << "               init        "<< std::endl             //coloca quantas crianças quiser na fila
                      << "               show        "<< std::endl             //coloca uma criança de cada vez no pula pula
                      << "               set         "<< std::endl             //retira uma criança tanto da fila quanto do pula pula                          << "              limpar       "<< std::endl             //mostra quem esta na fila e no pula pula
                      << "             dinheiro      "<< std::endl             //mostra o valor total arrecadado no pula pula
                      << "              troco        "<< std::endl             //paga a todo o valor que a criança deve ao pula pula
                      << "              limpar         "<< std::endl
                      << "             comprar       "<< std::endl             //mostra todas as contas
                      << "               end         "<< std::endl             //encerra o programa
                      << "##################################"<< std::endl
                      << "----------------------------------------------"<< std::endl;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            std::string cmd;
            ss >> cmd; //pegando o primeiro token
            if(line == "end"){
                system("clear||cls");
                if(maquina->espirais.size()!=0){
                    maquina->removeAll();
                }
                break;
            }else if(cmd == "init"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int nespirais, maxprodutos;
                ss >> nespirais>>maxprodutos;
                maquina=new Maquina(nespirais, maxprodutos);
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "show" ){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                std::cout << maquina->toString2()<< std::endl;
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "set" ){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int indice, qtd;
                float valor;
                std::string nome;
                ss >> indice >>nome >> qtd >> valor;
                maquina->alterarEspiral(indice,nome,qtd,valor);
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "dinheiro" ){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                float valor;
                ss >> valor;
                maquina->inserirDinheiro(valor);
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "troco"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                float troco;
                troco=maquina->pedirTroco();
                std::cout.precision(3);
                std::cout << "Você recebeu "<< troco<< " RS\n";    
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "limpar"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int indice;
                ss >> indice;
                if(maquina->espirais[indice].nome!=""){
                    maquina->remove(indice);
                }
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "comprar"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int indice;
                ss >> indice;
                if(maquina->vender(indice)){
                    std::cout << "Você comprou um "<< maquina->espirais[indice].nome << "\n";
                }
                std::cout << "------------------------------------------------"<< std::endl;
            }else{
                system("clear||cls");
                std::cout << "Comando invalido\n";
                std::cout << "------------------------------------------------"<< std::endl;
            }
        }
    }
};
int main(){
    Terminal terminal;
    terminal.painel();
    return 0;
}