//cachorrinho de estimacao
#include <iostream>
#include <sstream>
#include <string>


using namespace std;
struct Comida {
    string tipo;
    int qtd_do_conteudo;
    Comida(string tipo = "", int qtd_do_conteudo=0){
        this->tipo = tipo;
        this->qtd_do_conteudo=qtd_do_conteudo;
        cout << this->tipo << " comprado\n"; 
    }
    ~Comida(){
        cout << this->tipo << " acabou\n";
    }
};
struct Pote{
    Comida *alimento {nullptr};
    string tamanho;//pequeno medio ou grande
    
    int qtd_max;
    Pote(string tamanho = ""){
        this->tamanho=tamanho;
        if(this->tamanho=="pequeno") this->qtd_max=2;
        else if(this->tamanho=="medio") this->qtd_max=4;
        else if(this->tamanho=="grande") this->qtd_max=10;
    }
    void comprar_comida(Comida * alimento){
        if(this->alimento != nullptr){
            cout << "Já tem um tipo de comida dentro do pote, apenas compre mais dessa comida\n";
        }else{
            this->alimento=alimento;
        }
    }
    void encher_pote(int quantidade){
        if(this->qtd_max==0) cout << "Você não tem pote, compre um pote\n";
        else if (alimento==nullptr) cout << "Compre algum alimento para colocar no pote";
        else if(alimento->qtd_do_conteudo==this->qtd_max){
                cout << "Não cabe mais nada no seu pote\n";
            }
        else if((quantidade>this->qtd_max || quantidade+alimento->qtd_do_conteudo>this->qtd_max) && alimento->qtd_do_conteudo<this->qtd_max){
                alimento->qtd_do_conteudo=this->qtd_max;
                cout << "Seu pote de "<< alimento->tipo <<" encheu que derramou\n";
            }
        else if((quantidade==this->qtd_max && alimento->qtd_do_conteudo==0) || quantidade+alimento->qtd_do_conteudo==this->qtd_max){
                alimento->qtd_do_conteudo=this->qtd_max;
                cout << "Você acabou de encher seu pote de " << alimento->tipo << "\n";
            }
        else if(quantidade+alimento->qtd_do_conteudo<this->qtd_max){
                alimento->qtd_do_conteudo+=quantidade;
                cout << "Ainda tem espaço para colocar mais "<< alimento->tipo<< endl;
            }
    }
    void usar_conteudo_do_pote(int quantidade){
        if(this->qtd_max==0) cout << "Você não tem pote, compre um pote\n";
        else if(alimento->qtd_do_conteudo==0){ 
            cout << "O pote está vazio\n";
        }    
        else if((quantidade==this->qtd_max && alimento->qtd_do_conteudo==this->qtd_max) || alimento->qtd_do_conteudo==0){
            cout<<"Você secou o pote, encha ele depois\n";
            alimento->qtd_do_conteudo-=quantidade;
            
        }        
        else if(alimento->qtd_do_conteudo>quantidade && quantidade<this->qtd_max){
            alimento->qtd_do_conteudo-=quantidade;
            cout << "O pote agora tem "<< alimento->qtd_do_conteudo<<"kg de "<<this->alimento->tipo<< endl;
            
        }else if(quantidade>this->qtd_max){
            cout << "O seu pote é " << this->tamanho<< " para retirar essa quantidade compre um pote maior\n";
        }
        else if(alimento->qtd_do_conteudo<quantidade && quantidade<=this->qtd_max){
            cout << "O pote não possui toda essa quantidade de "<< this->alimento->tipo << " encha mais o pote\n";
            
        }    
    }
};
int main(){
    Pote *pote;
    system("clear||cls");
    while (true){
        system("clear||cls");
        cout << "comprar(pote= pequeno, medio ou grande) comida(tipo e quantidade) encher (quantidade em kg) usar(quantidade) end" << endl;
        cout << "\n";
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        if(cmd == "end"){
            system("clear||cls");
            break;
        }
        else if(cmd == "comprar"){
            string tamanho;
            ss>> tamanho;
            pote=new Pote(tamanho);
            cout<<"Pote comprado\n";
            getchar();
        }
        else if(cmd == "comida"){
            string tipo;
            int qtd;
            ss >> tipo >> qtd;
            pote->comprar_comida(new Comida(tipo, qtd));
            cout<<"Pacote de "<< pote->alimento->tipo<<" comprado\n";
            getchar();
        }  
        else if(cmd == "encher"){
            int qtd;
            ss>>qtd;
            pote->encher_pote(qtd);
            getchar();
        }
        else if(cmd == "usar"){
            int qtd;
            ss>>qtd;
            pote->usar_conteudo_do_pote(qtd);
            getchar();
        }
        else{
            cout << "Comando invalido\n";
            cout << "Aperte enter para continuar..\n";
            getchar(); 
        }   
    }
}