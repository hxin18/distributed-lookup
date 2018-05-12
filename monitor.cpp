//
//  client.cpp
//  ee450
//
//  Created by Xin Huang on 2018/3/18.
//  Copyright © 2018年 Xin Huang. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <iostream>
using namespace std;

#define APORT 21164
#define AWSPORT 24164
#define TCPPORT_CLIENT 26164
#define MAX_LENGTH 100
#define QUEUE_LIMIT 10
const char* localhost = "127.0.0.1";
#define fill '@'
#define BUF_SIZE 1000
#define LONG_BUF 3*sizeof(long int)*sizeof(long int)

/*
 * Encoding a word so that we sent the full buffer
 * str: string to be encoded.
 */
void encode(char* str){
    int len = strlen(str);
    for(int i = len; i < BUF_SIZE; i++){
        *(str+i) = fill;
    }
}
/*
 * Encoding a word so that we sent the full buffer
 * str: string to be decoded.
 */
void decode(char* str){
    int start = 0;
    while(str[start]!=fill){
        start++;
        if(start == BUF_SIZE)
            break;
    }
    for(int i = start; i < BUF_SIZE; i++){
        *(str+i)='\0';
    }
}

int main(int argc, char const *argv[]){
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(localhost);
    serv_addr.sin_port = TCPPORT_CLIENT;
    
    char bufSendToServ[BUF_SIZE] ;
    char fctBuffer[BUF_SIZE];
    char bufRecvFromServ[BUF_SIZE] ;
    char query[BUF_SIZE]={'\0'};
    cout<<"The monitor is up and running."<<endl;
    
    while(1){
        int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        bool flag = true;
        while(flag){
            int s = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
            if(s!=-1)
                break;
        }
        memset(fctBuffer,'\0',sizeof(fctBuffer));
        
        //observe the query and function
        int len = recv(sock, fctBuffer, sizeof(fctBuffer), 0);
        decode(fctBuffer);
        
        len = recv(sock, query, sizeof(query), 0);
        decode(query);
        
        
        if(!strcmp(fctBuffer,"search")){
            
            int found;
            memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
            int len = recv(sock,bufRecvFromServ, sizeof(bufRecvFromServ), 0);
            decode(bufRecvFromServ);
            found = atoi(bufRecvFromServ);
            //receive number of result
            
            if(found == 0){//no result
                cout<<"Found no matches for < "<<query <<" >:"<<endl;
            }
            else if(found==1){//one result
                memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
                int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                cout<<"Found a match for < "<<query <<" >:"<<endl;
                decode(bufRecvFromServ);
                cout<<"< "<<bufRecvFromServ<<" >"<<endl;
                //receive and print the word and meaning.
            }
            else{
                cout<<"Found < "<<found<<" > match for < "<<query <<" >:"<<endl;
                for(int i = 0; i < found; i++){
                    memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
                    int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                    decode(bufRecvFromServ);
                    cout<<"< "<<bufRecvFromServ<<" >"<<endl;
                }
            }
            
            //for search it will also display one edit distant result
            int foundSim;
            memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
            len = recv(sock,bufRecvFromServ, sizeof(bufRecvFromServ), 0);
            decode(bufRecvFromServ);
            foundSim = atoi(bufRecvFromServ);
            //receive number of result
            
            if(foundSim==1){
                memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
                int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                decode(bufRecvFromServ);
                cout<<"One edit distance match is< "<<bufRecvFromServ<<" >"<<endl;
                recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                decode(bufRecvFromServ);
                cout<<"< "<<bufRecvFromServ<<" >"<<endl;
                //receive and print the one distant word and meaning.
                
            }
            if(foundSim>1){//for this project won't execute
                for(int i = 0; i < foundSim; i++){
                    memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
                    int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                    decode(bufRecvFromServ);
                    cout<<"One edit distance match is < "<<bufRecvFromServ<<" >"<<endl;
                    recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                    decode(bufRecvFromServ);
                    cout<<"< "<<bufRecvFromServ<<" >"<<endl;
                }
            }
        }
        
        if(!strcmp(fctBuffer,"prefix")){
            
            int found;
            memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
            int len = recv(sock,bufRecvFromServ, sizeof(bufRecvFromServ), 0);
            decode(bufRecvFromServ);
            found = atoi(bufRecvFromServ);
            //receive number of matches
            if(found == 0){//no match
                cout<<"Found no matches for < "<<query <<" >:"<<endl;
            }
            else if(found==1){//one match
                memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
                int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                decode(bufRecvFromServ);
                cout<<"Found a match for < "<<query <<" >:"<<endl;
                cout<<"< "<<bufRecvFromServ<<" >"<<endl;
            }
            else{
                cout<<"Found < "<<found<<" > match for < "<<query <<" >:"<<endl;
                
                for(int i = 0; i < found; i++){//multiple matches
                    memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
                    int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                    decode(bufRecvFromServ);
                    cout<<"< "<<bufRecvFromServ<<" >"<<endl;
                }
                //receive all words.
            }
        }
        if(!strcmp(fctBuffer,"suffix")){
            
            int found;
            memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
            int len = recv(sock,bufRecvFromServ, sizeof(bufRecvFromServ), 0);
            decode(bufRecvFromServ);
            found = atoi(bufRecvFromServ);
            
            //receive number of matches
            if(found == 0){//no match
                cout<<"Found no matches for < "<<query <<" >:"<<endl;       
            }
            else if(found==1){// one match
                memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
                int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                decode(bufRecvFromServ);
                cout<<"Found a match for < "<<query <<" >:"<<endl;
                cout<<"< "<<bufRecvFromServ<<" >"<<endl;
                
            }
            else{//multiple matches
                cout<<"Found < "<<found<<" > match for < "<<query <<" >:"<<endl;
                for(int i = 0; i < found; i++){
                    memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
                    int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
                    decode(bufRecvFromServ);
                    cout<<"< "<<bufRecvFromServ<<" >"<<endl;
                    //receive all words.
                }
            }
        }
        
        close(sock);
    }
    
    
    return 0;
}
