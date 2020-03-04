//cachorrinho de estimacao
#include <iostream>
#include <sstream>
#include <string>


using namespace std;
struct cachorrinho{
    string nome;
    int energia=0;
    int max_energia=8;
    float barriga_vazia=0;
    float barriga_cheia=10;
    float sede=0;
    float hidratado=6;

    void dar_nome(){
        cout << "Digite o nome do seu cachorrinho: ";
        cin >> this->nome;
        cout << this->nome <<" é seu cachorrinho agora\n";
        cout << "Aperte enter para continuar..\n";
        getchar();
    }
    void alimentar(float qtd_racao){ 
        if(qtd_racao+this->barriga_vazia>=this->barriga_cheia){
            cout << this->nome <<" está de barriga cheia...\n";
            this->barriga_vazia=this->barriga_cheia;
            return;
        }
        else if(qtd_racao+this->barriga_vazia>this->barriga_cheia/2 && qtd_racao+this->barriga_vazia<this->barriga_cheia){
            cout << this->nome <<" está bem alimentado...\n";
            this->barriga_vazia+=qtd_racao;
            return;
        }
        else if(qtd_racao+this->barriga_vazia<=this->barriga_cheia/2){
            cout << this->nome << " quer mais comida...\n";
            this->barriga_vazia+=qtd_racao;
            return;
        }
    }
    void hidratar(float qtd_agua){
        if(qtd_agua+this->sede>=this->hidratado){
            cout << this->nome <<" está super hidratado...\n";
            this->sede=this->hidratado;
            return;
        }
        else if(qtd_agua+this->sede>this->hidratado/2 && qtd_agua+this->sede<this->hidratado){
            cout << this->nome << " está bem hidratado...\n";
            this->sede+=qtd_agua;
            return;
        }
        else if(qtd_agua+this->sede<=this->hidratado/2){
            cout << this->nome <<" ainda quer mais agua...\n";
            this->sede+=qtd_agua;
            return;
        }
    }
    void botar_para_descansar(int tempo){
        if(tempo+this->energia>=this->max_energia){
            cout << this->nome <<" quer brincar muitooo\n";
            this->energia=this->max_energia;
            return;
        }
        else if(tempo+this->energia>this->max_energia/2 && tempo+this->energia<this->max_energia){
            cout << this->nome << " já está quase se cansando\n";
            this->energia+=tempo;
            return;
        }
        else if(tempo+this->energia<=this->max_energia/2){
            cout << this->nome <<" não quer acordar\n";
            this->energia+=tempo;
            return;
        }
    }
    void brincar(string brincadeira){
        if(this->sede>=this->hidratado/2 && this->energia>=this->max_energia/2 && this->barriga_vazia>=barriga_cheia/2){
            if(brincadeira=="bola"){
                cout << this->nome<< " correu para ir buscar a bola, chame ele para trazer a bola\n";
                this->energia-=1;
                this->sede-=1;
                this->barriga_vazia-=1;
                return;
            }
            else if(brincadeira == "passear"){
                cout << this->nome << " ama passear, mas cuidado para ele não comer as coisas do chão\n";
                this->energia-=2;
                this->sede-=2;
                this->barriga_vazia-=2;
                return;
            }
            else if(brincadeira == "correr"){
                cout << this->nome << " está correndo de um lado para o outro\n";
                this->energia-=2;
                this->sede-=2;
                this->barriga_vazia-=2;
                return;
            }
            else{
                cout << this->nome << " não sabe brincar disso\n";
                return;
            }
        }
        else if (this->sede<this->hidratado/2 && this->energia<this->max_energia/2 && this->barriga_vazia<this->barriga_cheia/2){
            cout << this->nome <<" está com sede, com fome e cansado\n";
            return;
        }
        else if (this->sede<this->hidratado/2 && this->energia>=this->max_energia/2 && this->barriga_vazia>=this->barriga_cheia/2){
            cout << this->nome <<" está com sede, coloque agua\n";
            return;
        }
        else if (this->sede>=this->hidratado/2 && this->energia<this->max_energia/2 && this->barriga_vazia>=this->barriga_cheia/2){
            cout << this->nome <<" está cansado, deixa ele dormir um pouco\n";
            return;
        }
        else if (this->sede>=this->hidratado/2 && this->energia>=this->max_energia/2 && this->barriga_vazia<this->barriga_cheia/2){
            cout << this->nome <<" está com fome, dê comida para ele\n";
            return;
        }else if (this->sede<this->hidratado/2 && this->energia<this->max_energia/2 && this->barriga_vazia>=this->barriga_cheia/2){
            cout << this->nome <<" está com sede e com sono, dê agua e deixe descansar um pouco\n";
            return;
        }
        else if (this->sede<this->hidratado/2 && this->energia>=this->max_energia/2 && this->barriga_vazia<this->barriga_cheia/2){
            cout << this->nome <<" está com sede e com fome, dê agua e comida \n";
            return;
        }
        else if (this->sede>=this->hidratado/2 && this->energia<this->max_energia/2 && this->barriga_vazia<this->barriga_cheia/2){
            cout << this->nome <<" está com fome e com sono, dê comida e deixe descansar um pouco\n";
            return;
        }
    }
};
int main(){
    system("clear||cls");
    cachorrinho * cachorro= new cachorrinho();
    cout << "Você acabou de adotar um cachorrinho, vamos dar um nome para ele..\n";
    cout << "Aperte enter para continuar..\n";
    getchar();
    system ("clear||cls");
    cachorro->dar_nome();
    getchar();
    while (true){
        system("clear||cls");
        cout << "Agora vamos cuidar do "<< cachorro->nome << endl;
        cout << "alimentar(kg de ração) hidratar(litros de agua) dormir(Tempo de descanso) brincar(bola, passear ou correr) end\n";
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        if(cmd == "end"){
            system("clear||cls");
            break;
        }  
        else if(cmd == "alimentar"){
            float qtd_racao;
            ss >> qtd_racao;
            cachorro->alimentar(qtd_racao);
            cout << "Aperte enter para continuar..\n";
            getchar();
        }
        else if(cmd == "hidratar"){
            float qtd_agua;
            ss >> qtd_agua;
            cachorro->hidratar(qtd_agua);
            cout << "Aperte enter para continuar..\n";
            getchar();
        }
        else if(cmd == "dormir"){
            int tempo;
            ss >> tempo;
            cachorro->botar_para_descansar(tempo);
            cout << "Aperte enter para continuar..\n";
            getchar();
        }
        else if(cmd == "brincar"){
            string brincadeira;
            ss >> brincadeira;
            cachorro->brincar(brincadeira);
            cout << "Aperte enter para continuar..\n";
            getchar();
        }
        else{
            cout << "Comando invalido\n";
            cout << "Aperte enter para continuar..\n";
            getchar(); 
        }   
    }
    
}