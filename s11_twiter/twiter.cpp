#include <iostream>
#include <list>
#include <sstream>
#include <algorithm>
#include <list>
using namespace std;

class Tweet{
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
    }
};
class User{
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
        for(User aux: seguidos_User){
            if(aux.userName_User==other_User.userName_User){
                cout << "fail: " << aux.userName_User << " ja segue "<< other_User.userName_User << "\n";
                return;
            }
        }
        seguidos_User.push_front(other_User);
        other_User.seguidores_User.push_front(this);
    }
};
class Tweet_Generator{
    list<Tweet*> tweet_Ge;
};


int main(){
    return 0;
}