#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
struct Espiral{
    //atributos
    std::string nome;   //nome do produto
    int qtd=0;          //quantidade do produto na espiral
    float preco=0.00;    //preço do produto
    
    Espiral(std::string nome= "", int qtd=0, float preco=0.00){     //construtor da espiral
        this->nome=nome;
        this->qtd=qtd;
        this->preco=preco;
    }
    std::string toString(){
        if(nome==""){
            return + " [ empty : " + std::to_string(qtd) + " U : " ;
        }
        return + " [ " + nome + " : " + std::to_string(qtd) + " U : ";
    }
};

struct Maquina{
    std::vector<Espiral> espirais;
    float saldoCliente=0.00;
    float lucro=0.00;
    int maxProdutos=0;
    public:
        Maquina(int nespirais, int maxProdutos){
            this->maxProdutos=maxProdutos;
            
            for(int i=0; i<nespirais;i++){
                Espiral *aux=new Espiral();
                espirais.push_back(*aux);
            }
        }
        void toString2(){
            std::cout.precision(3);
            std::cout << "Saldo:"<< saldoCliente << "\n";
            for(int i=0; i< espirais.size(); i++){
                std::cout << std::to_string(i)  << espirais[i].toString()<<  espirais[i].preco << " RS ]\n";
            }
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
            if(indice>espirais.size()){
                std::cout <<"fail: indice invalido\n";
                return false;
            }
            else if(espirais[indice].nome==""){
                std::cout <<"fail: não tem nada nessa espiral\n";
                return false;
            }
            else if(espirais[indice].qtd==0){
                std::cout <<"fail: não tem mais produto nessa espiral\n";
                return false;
            }
            else if(getSaldo()>0 && getSaldo()>= espirais[indice].preco && espirais[indice].qtd>0){
                this->saldoCliente-=espirais[indice].preco;
                espirais[indice].qtd-=1;
                return true;
            }
            std::cout <<"fail: Você não tem saldo suficiente\n";
            return false;
        }
        void reporProduto(int indice, int qtd){
            if(indice>espirais.size()) std::cout << "fail: indice inválido\n";
            else if(espirais[indice].nome=="") std::cout << "fail: Não tem produto nessa espiral\n";
            else if(espirais[indice].qtd+qtd>maxProdutos) std::cout <<"fail: não cabe essa quantidade na espiral\n";
            else if(espirais[indice].qtd+qtd<=maxProdutos){ 
                espirais[indice].qtd+=qtd;
                std::cout << "Você adicionou mais "<< qtd << " de " << espirais[indice].nome << std::endl;
            }    
        }
        void addEspirais(){
            espirais.push_back(Espiral());
        }
        void inserirNovo(int indice){
            auto it = espirais.begin() + indice;
            Espiral *aux=new Espiral();
            if(it>=espirais.end()) espirais.push_back(*aux);
            else if(it >= espirais.begin() && it <espirais.end()) espirais.insert(it,*aux);
        }
        bool remove(int indice){
            if(indice >= 0 || indice < (int) espirais.size()){    
                auto i= espirais.begin() + indice;
                espirais.erase(i);
                inserirNovo(indice);
                return true;
            }
            std::cout << "fail: indice invalido\n";
            return false;
        }
        void removeAll(){
            espirais.clear();
        }
};
struct Terminal{
    Maquina *maquina=nullptr;
    void painel(){
        std::string line;
        while(true){
            std::cout << "-------------Junkfood-------------"<< std::endl
                      << "##################################"<< std::endl
                      << "               init        "<< std::endl             //inicia uma maquina com a quantidade de espirais e qtd max para cada produto
                      << "               show        "<< std::endl             //mostra todas as espirais e o saldo
                      << "               set         "<< std::endl             //coloca um produto em uma espiral desejada
                      << "             dinheiro      "<< std::endl             //adiciona dinheiro no saldo
                      << "              troco        "<< std::endl             //dar o troco da pessoa, se caso não tiver comprado nada, ele devolve tudo
                      << "              repor        "<< std::endl             //repõe a quantidade de um produto desejado
                      << "            addespiral     "<< std::endl             //coloca mais espirais na maquina
                      << "              limpar       "<< std::endl             //limpa uma espiral desejada
                      << "             comprar       "<< std::endl             //compra um produto, caso tenha saldo suficiente
                      << "               end         "<< std::endl             //encerra o programa
                      << "##################################"<< std::endl
                      << "----------------------------------------------"<< std::endl;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            std::string cmd;
            ss >> cmd; //pegando o primeiro token
            if(line == "end"){
                system("clear||cls");
                if(maquina!=nullptr){
                    free(maquina);
                    if(maquina->espirais.size()!=0 ){
                    maquina->removeAll();
                    }
                }    
                break;
            }else if(cmd == "init"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int nespirais, maxprodutos;
                ss >> nespirais>>maxprodutos;
                if(maquina==nullptr) maquina=new Maquina(nespirais, maxprodutos);
                else{
                    free(maquina);
                    maquina=new Maquina(nespirais, maxprodutos);
                }
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "show" ){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                if(maquina!=nullptr) maquina->toString2();
                else std::cout << "fail:crie uma máquina primeiro\n";
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "set" ){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int indice, qtd;
                float valor;
                std::string nome;
                ss >> indice >>nome >> qtd >> valor;
                if(maquina!=nullptr) maquina->alterarEspiral(indice,nome,qtd,valor);
                else std::cout << "fail:crie uma máquina primeiro\n";
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "dinheiro" ){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                float valor;
                ss >> valor;
                if(maquina!=nullptr) maquina->inserirDinheiro(valor);
                else std::cout << "fail:crie uma máquina primeiro\n";
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "troco"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                float troco;
                if(maquina!=nullptr){
                    troco=maquina->pedirTroco();
                    std::cout.precision(3);
                    std::cout << "Você recebeu "<< troco<< " RS\n";
                }
                else std::cout << "fail:crie uma máquina primeiro\n";        
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "repor"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int indice, qtd;
                ss >> indice >> qtd;
                if(maquina!=nullptr){
                    maquina->reporProduto(indice, qtd);
                }
                else std::cout << "fail:crie uma máquina primeiro\n";        
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "addespiral"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                if(maquina!=nullptr) maquina->addEspirais();
                else std::cout << "fail:crie uma máquina primeiro\n";
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "limpar"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int indice;
                ss >> indice;
                if(maquina==nullptr) std::cout << "fail:crie uma máquina primeiro\n";
                else if(maquina->espirais[indice].nome!="") maquina->remove(indice);
                std::cout << "------------------------------------------------"<< std::endl;
            }else if(cmd == "comprar"){
                system("clear||cls");
                std::cout << "$" << line << "\n";
                int indice;
                ss >> indice;
                if(maquina==nullptr ) std::cout << "fail:crie uma máquina primeiro\n";
                else if(maquina->vender(indice))std::cout << "Você comprou um "<< maquina->espirais[indice].nome << "\n"; 
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