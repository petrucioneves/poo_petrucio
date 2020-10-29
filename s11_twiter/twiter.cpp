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
};

ostream& operator<<(ostream& ost, const Tweet& tweet){
    ost << std::to_string(tweet.idTw_Twe) << ":" << tweet.userName_Twe << "( " << tweet.msg_Twe <<" )";
    if(tweet.likes_Twe.size()>0){
        ost << "[ ";
        for(string aux: tweet.likes_Twe)
            ost << aux << " ";
        ost << "]\n";
    }
    return ost;
}

class User{
public:    
    string userName_User;
    int naoLidos_User;

    list<Tweet> timeline_User;
    list<Tweet> myTweets_User;

    list<User*> seguidores_User;
    list<User*> seguidos_User;
  
    User(string userName): userName_User(userName){
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
        myTweets_User.push_front(*msg);
        for(auto aux: seguidores_User){
            naoLidos_User++;
            aux->timeline_User.push_front(*msg);
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
    Tweet_Generator(list<Tweet*> r_tw): repors_tw_Ge(r_tw){}
    Tweet * create_Tw_Generator(string userName, string msg){
        Tweet *aux= new Tweet(nextId, userName, msg);
        repors_tw_Ge.push_back(aux);
        nextId++;
        return aux;
    }
};

class Twiter{
public:    
    list<User*> usuarios;
    list<Tweet*> repositorio;
    void addUser_Twi(string userName){
        for(auto it: usuarios){
            if(it->userName_User==userName){
                cout << "fail: usuario já existe\n";
                return;
            }
        }
        usuarios.push_back(new User(userName));
    }
    void follow_Twi(string user, string other){
        for(auto aux: usuarios){
            if(aux->userName_User == user){
                for(auto it : usuarios)
                    if(it->userName_User == other){
                        aux->follow_User(it);
                        return;
                    }
            }
        }
        cout << "fail: usuario "<< user << " não existe\n";
    }
    void Twitar_Twi(string user, string msg){
        Tweet_Generator aux {repositorio};
        for(auto au: usuarios){
            if(au->userName_User==user){
                
                au->twittar_User(aux.create_Tw_Generator(user, msg));
            }
        }
    }
    void timeline(string nome){
        list<Tweet*> auu;
        for (auto aux: usuarios){
            if(aux->userName_User==nome){
                for (auto i ; )
                {
                    /* code */
                }
                
            }
        }
        
    }
};

ostream& operator<<(ostream& ost, const Twiter& twiter){
    for(auto aux : twiter.usuarios)
        ost << *aux;
    return ost;
}    


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
        else if(cmd == "show"){
            cout << twitter;
        }
        else{
            cout << "fail: comando invalido";
        }
    }

    return 0;
}