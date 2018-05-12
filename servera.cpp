//
//  servera.cpp
//  ee450
//
//  Created by Xin Huang on 2018/3/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include "servera.h"
using namespace std;

/*
 parser for dictionary.
 */
kvParser::kvParser(string str, string seperator){
    int n = str.length();
    int sepPos = str.find(seperator,0);
    key = str.substr(0, sepPos);
    value = str.substr(sepPos+seperator.length(), n - sepPos);
}


string kvParser::getKey(){
    return key;
}

string kvParser::getValue(){
    return value;
}

Dict::Dict(){
    
    Dictionary = {};
}

Dict::~Dict(){
    
    Dictionary.clear();
    
}

void Dict::buildDict(string databaseFile){
    ifstream fin;
    fin.open(databaseFile.c_str());
    if (!fin){
        cout<<"open database failed"<<endl;
    }
    string ReadLine;
    char key[100];
    char value[100];
    //read each line and put the kv pair into the dictionary
    while(getline(fin,ReadLine))
    {
        kvParser* parser = new kvParser(ReadLine,seperator);
        strcpy(key, parser->getKey().c_str());
        dict::iterator iter = Dictionary.find(key);
        // A new key
        if(iter == Dictionary.end()){
            strcpy(value, parser->getValue().c_str());
            Dictionary[key] = value;
        }
    }
}
//see if key exists in the dictionary
bool Dict::findKey(string key){
    dict::iterator iter = Dictionary.find(key);
    return !(iter == Dictionary.end());
}


vector<string> Dict::retriveKey(string key){
    vector<string> res;
    if(findKey(key)){
        res.push_back(Dictionary.find(key)->second);
    }
    return res;
}

//to see two string has one edit distence
bool oneDifference(string keySrc, string keyDest){
    if(keySrc.length()!=keyDest.length()){
        return false;
    }
    int diff = 0;
    for(int i = 0; i < keySrc.length(); i++){
        diff+= keySrc[i]==keyDest[i]?0:1;
    }
    return diff == 1;
}

//to see one word is the prefix of another
bool isPrefix(string keySrc, string keyDest){
    if(keySrc.length()>=keyDest.length()){
        return false;
    }
    for(int i = 0; i < keySrc.length(); i++){
        if(keySrc[i]!=keyDest[i]){
            return false;
        }
    }
    return true;
}

//to see one word is the suffix of another
bool isSuffix(string keySrc, string keyDest){
    if(keySrc.length()>=keyDest.length()){
        return false;
    }
    int diff = keyDest.length() - keySrc.length();
    for(int i = 0; i < keySrc.length(); i++){
        if(keySrc[i]!=keyDest[i+diff]){
            return false;
        }
    }
    return true;
}

//get all words with the prefix "key"
vector<string> Dict::retrivePrefix(string key){
    vector<string> res;
    dict::iterator iter = Dictionary.begin();
    //iterate over the dict
    while(iter != Dictionary.end()) {
        if(isPrefix(key, iter->first)){
            res.push_back(iter->first);
        }
        iter++;
    }
    return res;
}

//get all words with the suffix "key"
vector<string> Dict::retriveSuffix(string key){
    vector<string> res;
    dict::iterator iter = Dictionary.begin();
    //iterate over the dict
    while(iter != Dictionary.end()) {
        if(isSuffix(key, iter->first)){
            res.push_back(iter->first);
        }
        iter++;
    }
    return res;
}

//get all words with one edit distant "key"
void Dict::retriveSimilar(string key, vector<string>& simW,vector<string>&simM){
    
    dict::iterator iter = Dictionary.begin(); 
    //iterate over dictionary
    while(iter != Dictionary.end()) {
        if(oneDifference(key, iter->first)){
            simM.push_back(iter->second);
            simW.push_back(iter->first);
        }
        iter++;
    }
}



int main(){
    
    Dict* database = new Dict();
    string fileLoc = "backendA.txt";
    database->buildDict(fileLoc);
    //create the database.
    
    int sockatA = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if (sockatA == -1){
        close(sockatA);
        perror("Socket failed");
        exit(-1);
    }
    
    struct sockaddr_in serveratA_addr;
    memset(&serveratA_addr, 0, sizeof(serveratA_addr));
    serveratA_addr.sin_family = PF_INET;
    serveratA_addr.sin_addr.s_addr = inet_addr(localhost);
    serveratA_addr.sin_port = APORT;
    
    bind(sockatA, (struct sockaddr*)&serveratA_addr, sizeof(serveratA_addr));
    cout << "The Server A is up and running using UDP on port " << APORT << endl;
    //create and bind the socket at the server side.
    
    
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    char recvBuffer[MAX_LENGTH];
    char query[MAX_LENGTH];
    char fct[MAX_LENGTH];
    char bufSend[100] = {'\0'};
    socklen_t client_addr_size = sizeof(client_addr);
    //define the buffer
    
    
    while (1){
        
        int strLen = recvfrom(sockatA, &recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&client_addr, &client_addr_size);
        
        if(strlen > 0){
            strcpy(query, recvBuffer);
            query[strLen]='\0';
            
            int fctLen = recvfrom(sockatA, &recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&client_addr, &client_addr_size);
            strcpy(fct, recvBuffer);
            fct[fctLen] = '\0';
            memset(recvBuffer, 0, MAX_LENGTH);
            cout<<"The Server A received input <"<<query<<"> and operation <"<<fct<<">"<<endl;
            //receive the query and the function
            
            vector<string> res;
            vector<string> resSimM ;
            vector<string> resSimW ;
            
            if(!strcmp(fct,"prefix")){
                res = database->retrivePrefix(query);
                cout<<"The Server A has found < "<<res.size()<<" > matches"<<endl;
            }
            else if(!strcmp(fct,"suffix")){
                res = database->retriveSuffix(query);	
                cout<<"The Server A has found < "<<res.size()<<" > matches"<<endl;
            }
            else{
                res = database->retriveKey(query);
                database->retriveSimilar(query,resSimW,resSimM);
                cout<<"The Server A has found < "<<res.size()<<" > matches and < "<<resSimW.size()<<" > similar words"<<endl;
            }
            //retrieve the result from the databases
            //Only start sending after receiving the synchronize message
            recvfrom(sockatA, &recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&client_addr, &client_addr_size);
            int socktoAWS = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
            //create another udp socket to sent result back to AWS
            if (socktoAWS== -1){
                close(socktoAWS); 
                perror("Socket failed");
                exit(-1);
            }
            
            
            memset(bufSend, 0, MAX_LENGTH);
            sprintf(bufSend, "%ld", res.size());
            
            
            struct sockaddr_in serverAWS_addr;
            serverAWS_addr.sin_family = PF_INET;
            serverAWS_addr.sin_addr.s_addr = inet_addr(localhost);
            serverAWS_addr.sin_port = AWSPORT;
            socklen_t serverAWS_addr_size = sizeof(serverAWS_addr);
            //set the port and address of server of aws
            
            sendto(socktoAWS, bufSend, strlen(bufSend), 0, (struct sockaddr*)&serverAWS_addr, serverAWS_addr_size);
            memset(bufSend, 0, MAX_LENGTH);
            //send the size of result
            
            for(int i = 0; i <  res.size(); i++){
                sprintf(bufSend, res[i].c_str());
                sendto(socktoAWS, bufSend, strlen(bufSend), 0,(struct sockaddr*)&serverAWS_addr, serverAWS_addr_size);
                sleep(0.2);
                memset(bufSend, 0, MAX_LENGTH);
            }
            //send the word or definition one by one.
            
            if(!strcmp(fct,"search")){
                //for the search we also need to send the similar result.
                memset(bufSend, 0, MAX_LENGTH);
                sprintf(bufSend, "%ld", resSimW.size());
                
                //send the size of result
                sendto(socktoAWS, bufSend, strlen(bufSend), 0, (struct sockaddr*)&serverAWS_addr, serverAWS_addr_size);
                memset(bufSend, 0, MAX_LENGTH);
                
                
                for(int i = 0; i <  resSimW.size(); i++){
                    sprintf(bufSend, resSimW[i].c_str());
                    sendto(socktoAWS, bufSend, strlen(bufSend), 0,(struct sockaddr*)&serverAWS_addr, serverAWS_addr_size);
                    memset(bufSend, 0, MAX_LENGTH);
                    sprintf(bufSend, resSimM[i].c_str());
                    sendto(socktoAWS, bufSend, strlen(bufSend), 0,(struct sockaddr*)&serverAWS_addr, serverAWS_addr_size);
                    memset(bufSend, 0, MAX_LENGTH);
                }
            }
            cout<<"The Server A finished sending the output to AWS"<<endl;
            //destroy the client side socket.
            close(socktoAWS);
            res= vector<string>();
            resSimW= vector<string>();
            resSimM= vector<string>();
            
        }
    }
    
    
    return 0;
}



