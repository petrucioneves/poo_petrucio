#include <iostream>
#include <list>
#include <sstream>
#include <algorithm>
#include <list>
#include <map>
using namespace std;

class Tweet{
public:    
    int idTw_Twe;
    string userName_Twe;
    string msg_Twe;
    list<string> likes_Twe;
    Tweet(int idTw=0, string userName="", string msg=""):
        idTw_Twe(idTw), userName_Twe(userName), msg_Twe(msg){
    }
    void darLike(string userName){
        for(auto aux: likes_Twe){
            if(aux==userName) return;
        }
        likes_Twe.push_back(userName);
    }
};

ostream& operator<<(ostream& ost, const Tweet& tweet){
    ost << to_string(tweet.idTw_Twe) << ":" << tweet.userName_Twe << "( " << tweet.msg_Twe <<" )";
    if(tweet.likes_Twe.size()>0){
        ost << "[ ";
        for(string aux: tweet.likes_Twe)
            ost << aux << " ";
        ost << "]";
    }
    ost << "\n";
    return ost;
}

class User{
public:    
    string userName_User;
    int naoLidos_User;

    list<Tweet*> timeline_User;
    list<Tweet*> myTweets_User;

    list<User*> seguidores_User;
    list<User*> seguidos_User;
    
    

    User(string userName=""): userName_User(userName){
        naoLidos_User=0;
    }
    void follow_User(User* other_User){
        for(auto aux: seguidos_User){
            if(aux->userName_User == other_User->userName_User){
                cout << "fail: " << this->userName_User << " ja segue "<< other_User->userName_User << "\n";
                return;
            }
        }

        this->seguidos_User.push_back(other_User);
        other_User->seguidores_User.push_back(this);
    }

    void twittar_User(Tweet * msg){
        myTweets_User.push_back(msg);
        for(auto aux: seguidores_User){
            aux->timeline_User.push_back(msg);
            naoLidos_User++;
        }
    }
    void darLike_User(int idTw){
        for(auto aux: timeline_User){
            if(aux->idTw_Twe==idTw){
                aux->darLike(this->userName_User);
            }
        }
    }
    list<Tweet*> get_unread_User(){
        list<Tweet*> naoLidos_tweets;
        for(auto it = timeline_User.begin(); naoLidos_User>0; it++){
            naoLidos_tweets.push_front(*it);
            naoLidos_User--;
        }
        return naoLidos_tweets;
    }
    list<Tweet*> get_timeline_User(){
        list<Tweet*> timeline_tweets;
        for(auto it : timeline_User){
            timeline_tweets.push_front(it);
        }
        return timeline_tweets;
    }
};

ostream& operator<<(ostream& ost, const User& user){
    ost << user.userName_User << "\n";
    ost << "  seguidos   [ ";
    for(auto aux : user.seguidos_User){
        ost << aux->userName_User << " ";
    }
    ost << "]\n";

    ost << "  seguidores [ ";
    for(auto aux : user.seguidores_User){
        ost << aux->userName_User << " ";
    }
    ost << "]\n";
    return ost;
}

class Tweet_Generator{
public:    
    list<Tweet*> repors_tw_Ge;
    int nextId;
    Tweet_Generator(list<Tweet*> r_tw): repors_tw_Ge(r_tw){
        this->nextId=0;
    }
    Tweet * create_Tw_Generator(string userName, string msg){
        Tweet *aux= new Tweet(nextId, userName, msg);
        repors_tw_Ge.push_back(aux);
        this->nextId++;
        return aux;
    }
};

class Twiter{   
public:
    list<User*> usuarios;
    list<Tweet*> repositorio_User;
    Tweet_Generator repor {repositorio_User};
    
    void addUser_Twi(string userName=""){
        if(getUsuario_Twi(userName)!=nullptr){
            cout << "fail: usuario já existe\n";
            return;
        }
        usuarios.push_back(new User(userName));
    }
    void follow_Twi(string user, string other){
        User * aux = getUsuario_Twi(user);
        User * it = getUsuario_Twi(other);
        if(aux!=nullptr){
            if(it != nullptr){
                aux->follow_User(it);
            }
        }
        else if(aux==nullptr || it==nullptr) cout << "fail: usuario não encontrado\n";
    }
    bool validarTweet_Twi( int id){
        for(auto it: repositorio_User){
            if( it->idTw_Twe==id) return true;
        }
        return false;
    }
    void Twitar_Twi(string user, string msg){
        Tweet * tweet_aux;
        User *au = getUsuario_Twi(user);
        if(au->userName_User==user){
            tweet_aux= repor.create_Tw_Generator(user,msg);
            au->twittar_User(tweet_aux);
            repositorio_User.push_back(tweet_aux);
        }
    }
    void darLike_Twi(string nome, int post){
        User * aux = getUsuario_Twi(nome);
        if(aux!=nullptr) aux->darLike_User(post);
    }
    User * getUsuario_Twi(string nome){
        for(auto aux: usuarios){
            if(aux->userName_User==nome) return aux;
        }
        return nullptr;
    }
    map<int, Tweet*> get_timeline(string nome){ 
        map<int, Tweet*> timeline_aux;
        User * aux = getUsuario_Twi(nome);       
        if(aux->userName_User==nome){
            for(auto it: aux->myTweets_User){
                timeline_aux[it->idTw_Twe]=it;
            }
            for(auto it2: aux->timeline_User){
                timeline_aux[it2->idTw_Twe]=it2;
            }
        }
        return timeline_aux;
    }
    friend ostream& operator<<(ostream& ost, const Twiter& twiter){
    for(auto aux : twiter.usuarios)
        ost << *aux;
    return ost;
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
        else if(cmd == "twittar"){
            string nome, msg;
            ss >> nome;  
            getline(ss, msg);
            twitter.Twitar_Twi(nome, msg);
        }
        else if(cmd == "timeline"){
            string nome;
            ss >> nome;
            if(twitter.getUsuario_Twi(nome)!=nullptr){
                for(auto it: twitter.get_timeline(nome)){
                    cout << *it.second;
                }
            }
            else if (twitter.getUsuario_Twi(nome)==nullptr)cout << "fail: usuario nao encontrado\n";
            else if (twitter.get_timeline(nome).size()==0) cout << "fail: Sem timeline\n";
            
        }
        else if(cmd == "like"){
            string nome;
            int post;
            ss >> nome >> post;
            if(twitter.validarTweet_Twi(post)==true)twitter.darLike_Twi(nome, post);
            else if (twitter.validarTweet_Twi(post)==false)cout << "fail: tweet nao existe\n";
        }
        else if(cmd == "show"){
            cout << twitter;
        }
        else{
            cout << "fail: comando invalido";
        }
    }

    return 0;
}