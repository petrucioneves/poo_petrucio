#include <iostream>
#include <list>
#include <sstream>
#include <algorithm>
#include <list>
using namespace std;

class Tweet{
public:    
    int idTw_Twe;
    string userName_Twe;
    string msg_Twe;
    list<string> likes_Twe;
    Tweet(int idTw, string userName, string msg):
        idTw_Twe(idTw), userName_Twe(userName), msg_Twe(msg){
    }
    void darLike(string userName){
        for(auto aux: likes_Twe){
            if(aux==userName) return;
        }
        likes_Twe.push_front(userName);
    }
    string to_string(){
        string saida= std::to_string(idTw_Twe)+":"+userName_Twe+"( "+msg_Twe+" )";
        if(likes_Twe.size()>0){
            saida+= "[ ";
            for(string aux: likes_Twe){
                saida += aux + " ";
            }
            saida+="]\n";
        }
        return saida; 
    }
};
class User{
public:    
    string userName_User;
    int naoLidos_User;

    list<Tweet> timeline_User;
    list<Tweet> myTweets_User;

    list<User> seguidores_User;
    list<User> seguidos_User;
  
    User(string userName): userName_User(userName){
        naoLidos_User=0;
    }
    void follow_User(User other_User){
        for(auto aux: seguidos_User){
            if(aux.userName_User==other_User.userName_User){
                cout << "fail: " << aux.userName_User << " ja segue "<< other_User.userName_User << "\n";
                return;
            }
        }
        seguidos_User.push_back(other_User);
        other_User.seguidores_User.push_back(*this);
    }
    void twittar_User(Tweet msg){
        myTweets_User.push_front(msg);
        for(auto aux: seguidores_User){
            naoLidos_User++;
            aux.timeline_User.push_front(msg);
        }
    }
    void darLike_User(int idTw){
        for(auto aux: timeline_User){
            if(aux.idTw_Twe==idTw){
                aux.darLike(this->userName_User);
            }
        }
    }
    list<Tweet> get_unread_User(){
        list<Tweet> naoLidos_tweets;
        for(auto it = timeline_User.begin(); naoLidos_User>0; it++){
            naoLidos_tweets.push_front(*it);
            naoLidos_User--;
        }
        return naoLidos_tweets;
    }
    list<Tweet> get_timeline_User(){
        list<Tweet> timeline_tweets;
        for(auto it : timeline_User){
            timeline_tweets.push_front(it);
        }
        return timeline_tweets;
    }
    string toString_User(){
        string saida_User=this->userName_User + "\n";
        saida_User+="  seguidos   [ ";
        for(auto aux= seguidos_User.begin(); aux!= seguidos_User.end(); aux++){
            saida_User += aux.userName_User + " ";
        }
        saida_User+="]\n";
        saida_User+="  seguidores [ ";
        for(auto aux : seguidores_User){
            saida_User+=aux.userName_User+" ";
        }
        saida_User+="]\n";
        return saida_User;
    }
};
class Tweet_Generator{
    list<Tweet*> r_tw_Ge;
    int nextId;
    Tweet_Generator(list<Tweet*> r_tw): r_tw_Ge(r_tw){}
    Tweet * create_Tw_Generator(string userName, string msg){
        Tweet *aux= new Tweet(nextId, userName, msg);
        r_tw_Ge.push_front(aux);
        nextId++;
        return aux;
    }
};
class Twiter{
public:    
    list<User> usuarios;
    list<Tweet_Generator> repositorio;
    void addUser_Twi(string userName){
        for(auto it: usuarios){
            if(it.userName_User==userName){
                cout << "fail: usuario já existe\n";
                return;
            }
        }
        usuarios.push_back(User(userName));
    }
    void follow_Twi(string user, string other){
        for(auto aux: usuarios){
            if(aux.userName_User==user){
                aux.follow_User(User(other));
                return;
            }
        }
        cout << "fail: usuario "<< user << " não existe\n";
    }
    void show_Twi(){
        for (auto aux: usuarios){
            cout << aux.toString_User();
        }
    }
};


int main(){
    Twiter twitter;
    while(true){
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "end"){
            break;
        }
        else if(cmd == "addUser"){
            string nome;
            ss >> nome;
            twitter.addUser_Twi(nome);
        }
        else if(cmd == "follow"){
            string nome, other;
            ss >> nome >> other;
            twitter.follow_Twi(nome, other);
        }
        else if(cmd == "addTer"){
            string nome, insalubre;
            int hora;
            ss >> nome >> hora >> insalubre;
            //empresa.addFuncionario_Ter(nome, hora, insalubre);
        }
        else if(cmd == "rm"){
            string nome;
            ss >> nome;
            //empresa.remove_funcionario(nome);
        }
        else if(cmd == "addDiaria"){
            string nome;
            ss >> nome;
            //empresa.addDiara_emp(nome);
        }
        else if(cmd == "setBonus"){
            double bonus;
            ss >> bonus;
            //empresa.calBonus(bonus);
        }
        else if(cmd == "show"){
            string id;
            ss >> id;
            twitter.show_Twi();
        }
        else{
            cout << "fail: comando invalido";
        }
    }

    return 0;
}