//cachorrinho de estimacao
#include <iostream>
#include <sstream>
#include <string>


using namespace std;
struct Pote{
    string tamanho;//pequeno medio ou grande
    string conteudo_do_pote;
    int qtd_do_conteudo;
    int qtd_max;
    Pote(string tamanho="", string conteudo=""){
        this->tamanho=tamanho;
        this->conteudo_do_pote=conteudo;
        if(this->tamanho=="pequeno") this->qtd_max=2;
        else if(this->tamanho=="medio") this->qtd_max=4;
        else if(this->tamanho=="grande") this->qtd_max=10;
    }
    void encher_pote(int quantidade){
        if(this->qtd_max==0) cout << "Você não tem pote, compre um pote\n";
        else if(this->qtd_do_conteudo==this->qtd_max){
                cout << "Não cabe mais nada no seu pote\n";
            }
        else if((quantidade>this->qtd_max || quantidade+this->qtd_do_conteudo>this->qtd_max) && this->qtd_do_conteudo<this->qtd_max){
                this->qtd_do_conteudo=this->qtd_max;
                cout << "Seu pote de "<< this->conteudo_do_pote<<" encheu que derramou\n";
            }
        else if((quantidade==this->qtd_max && this->qtd_do_conteudo==0) || quantidade+this->qtd_do_conteudo==this->qtd_max){
                this->qtd_do_conteudo=this->qtd_max;
                cout << "Você acabou de encher seu pote de " << this->conteudo_do_pote << "\n";
            }
        else if(quantidade+this->qtd_do_conteudo<this->qtd_max){
                this->qtd_do_conteudo+=quantidade;
                cout << "Ainda tem espaço para colocar mais "<< this->conteudo_do_pote<< endl;
            }
    }
    void usar_conteudo_do_pote(int quantidade){
        if(this->qtd_max==0) cout << "Você não tem pote, compre um pote\n";
        else if(this->qtd_do_conteudo==0){ 
            cout << "O pote está vazio\n";
        }    
        else if((quantidade==this->qtd_max && this->qtd_do_conteudo==this->qtd_max) || this->qtd_do_conteudo-quantidade==0){
            cout<<"Você secou o pote, encha ele depois\n";
            this->qtd_do_conteudo-=quantidade;
            
        }        
        else if(this->qtd_do_conteudo>quantidade && quantidade<this->qtd_max){
            this->qtd_do_conteudo-=quantidade;
            cout << "O pote agora tem "<< this->qtd_do_conteudo<<"kg de "<<this->conteudo_do_pote<< endl;
            
        }else if(quantidade>this->qtd_max){
            cout << "O seu pote é " << this->tamanho<< " para retirar essa quantidade compre um pote maior\n";
        }
        else if(this->qtd_do_conteudo<quantidade && quantidade<=this->qtd_max){
            cout << "O pote não possui toda essa quantidade de "<< this->conteudo_do_pote << " encha mais o pote\n";
            
        }    
    }
};
int main(){
    Pote *pote;
    system("clear||cls");
    while (true){
        system("clear||cls");
        cout << "comprar (pequeno, medio ou grande)(conteudo) encher (quantidade em kg) usar(quantidade) end" << endl;
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
            string tamanho, conteudo;
            ss>> tamanho;
            ss>>conteudo;
            pote=new Pote(tamanho, conteudo);
            cout<<"Pote comprado\n";
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