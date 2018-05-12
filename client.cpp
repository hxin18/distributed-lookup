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
#define TCPPORT_CLIENT 25164
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
    
    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //create a tcp client side socket.
    cout<<"The client is up and running."<<endl;
    bool flag = true;
    while(flag){
    int s = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(s!=-1)
	break;
    }
    

    memset(fctBuffer,'\0',sizeof(bufSendToServ));
    strcpy(fctBuffer, argv[1]);
    encode(fctBuffer);
    send(sock, fctBuffer, sizeof(fctBuffer), 0);
    string query = "";
    for(int i = 2; i < argc-1; i++){
       string str(argv[i]);
       query+=str+' ';
    }
    query+=argv[argc-1];
    //build up query
    memset(bufSendToServ,0,sizeof(bufSendToServ));
    strcpy(bufRecvFromServ, query.c_str());
    encode(bufRecvFromServ);
    bufSendToServ[strlen(bufSendToServ)]='\0';
    send(sock, bufRecvFromServ,sizeof(bufRecvFromServ), 0);
    //send the query to the server.
    cout<< "The client sent < "<<query<<" > and < "<<argv[1]<<" > to AWS"<<endl;
    //end of phase 1
    
    int found;
    memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
    int len = recv(sock,bufRecvFromServ, sizeof(bufRecvFromServ), 0);
    decode(bufRecvFromServ);
    found = atoi(bufRecvFromServ);
    //receive number of result
    if(found == 0){
        cout<<"Found no matches for < "<<query <<" >:"<<endl;       
    }
    else if(found==1){
        memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
        int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
        cout<<"Found a match for < "<<query <<" >:"<<endl;       
        decode(bufRecvFromServ);
	cout<<"< "<<bufRecvFromServ<<" >"<<endl;
        
   }
    else{//no need for this proj, but left to further use.
	cout<<"Found < "<<found<<" > matches for < "<<query <<" >:"<<endl;      
	for(int i = 0; i < found; i++){
        memset(bufRecvFromServ,'\0',sizeof(bufRecvFromServ));
        int len = recv(sock, bufRecvFromServ, sizeof(bufRecvFromServ), 0);
        decode(bufRecvFromServ);  
	cout<<"< "<<bufRecvFromServ<<" >"<<endl;
        
	}
    }
    
    close(sock);
    
    return 0;
}
