//
//  aws.cpp
//  ee450
//
//  Created by Xin Huang on 2018/3/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include "aws.h"
#include <vector>
using namespace std;

/*
 * Encoding a word so that we sent the full buffer
 * str: string to be encoded.
 */
void encode(char* str){
    int len = strlen(str);
    for(int i = len; i < BUFF_SIZE; i++){
        str[i] = fill;//fill here is @
    }
}

/*
 * Encoding a word so that we sent the full buffer
 * str: string to be decoded.
 */
void decode(char* str){
    int start = 0;
    //finding the first fill character
    while(str[start]!=fill){
        start++;
        if(start == BUFF_SIZE)
            break;
    }
    //remove all the filled character
    for(int i = start; i < BUFF_SIZE; i++){
        str[i]='\0';
    }
}

/*
 * Send the synchronize message to Server A using udp
 * Doing so in order to avoid the conflict.
 */
void startA(){
    
    int socket_info;
    struct sockaddr_in serverA;
    int port = APORT;
    int SendSocket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (SendSocket == -1){
        close(SendSocket);
        perror("Socket failed");
        exit(-1);
    }
    //create a UDP client socket
    
    memset(&serverA, 0, sizeof(serverA));    
    serverA.sin_family = PF_INET;
    serverA.sin_port = APORT;
    serverA.sin_addr.s_addr = inet_addr(localhost);
    socklen_t serverA_addr_size = sizeof(serverA);
    //setting the address of the server
    string query = "";
    sendto(SendSocket, query.c_str(), sizeof(query), 0, (struct sockaddr*) &serverA, serverA_addr_size);
    //send the query and function
    
    close(SendSocket);
    //destroy the socket
    
}

/*
 * Send the synchronize message to Server B using udp
 * Doing so in order to avoid the conflict.
 */
void startB(){
    
    int socket_info;
    struct sockaddr_in serverA;
    int port = APORT;
    int SendSocket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (SendSocket == -1){
        close(SendSocket);
        perror("Socket failed");
        exit(-1);
    }
    //create a UDP client socket
    
    memset(&serverA, 0, sizeof(serverA ));    
    serverA.sin_family = PF_INET;
    serverA.sin_port = BPORT;
    serverA.sin_addr.s_addr = inet_addr(localhost);
    socklen_t serverA_addr_size = sizeof(serverA);
    //setting the address of the server
    string query = "";
    sendto(SendSocket, query.c_str(), sizeof(query), 0, (struct sockaddr*) &serverA, serverA_addr_size);
    //send the query and function
    
    close(SendSocket);
    //destroy the socket
    
}
/*
 * Send the synchronize message to Server A using udp
 * Doing so in order to avoid the conflict.
 */
void startC(){
    
    int socket_info;
    struct sockaddr_in serverA;
    int port = APORT;
    int SendSocket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (SendSocket == -1){
        close(SendSocket);
        perror("Socket failed");
        exit(-1);
    }
    //create a UDP client socket
    
    memset(&serverA, 0, sizeof(serverA ));    
    serverA.sin_family = PF_INET;
    serverA.sin_port = CPORT;
    serverA.sin_addr.s_addr = inet_addr(localhost);
    socklen_t serverA_addr_size = sizeof(serverA);
    //setting the address of the server
    string query ="";
    sendto(SendSocket, query.c_str(), sizeof(query), 0, (struct sockaddr*) &serverA, serverA_addr_size);
    //send the query and function
    
    close(SendSocket);
    //destroy the socket
    
}


/*
 * Send the query and function to Server A using udp
 * query: query
 * fct: function
 */
void udpToA(string  query, string fct){
    
    int socket_info;
    struct sockaddr_in serverA;
    int port = APORT;
    int SendSocket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (SendSocket == -1){
        close(SendSocket);
        perror("Socket failed");
        exit(-1);
    }
    //create a UDP client socket
    
    memset(&serverA, 0, sizeof(serverA));    
    serverA.sin_family = PF_INET;
    serverA.sin_port = APORT;
    serverA.sin_addr.s_addr = inet_addr(localhost);
    socklen_t serverA_addr_size = sizeof(serverA);
    //setting the address of the server
    
    sendto(SendSocket, query.c_str(), sizeof(query), 0, (struct sockaddr*) &serverA, serverA_addr_size);
    sendto(SendSocket, fct.c_str(), sizeof(fct), 0, (struct sockaddr*) &serverA, serverA_addr_size);
    //send the query and function
    cout<<"The AWS sent < "<<query<<" > and < "<<fct<<"> to Backend-Server A"<<endl;
    close(SendSocket);
    //destroy the socket
    
}

/*
 * Send the query and function to Server B using udp
 * query: query
 * fct: function
 */
void udpToB(string  query, string fct){
    
    int socket_info;
    struct sockaddr_in serverB;
    int port = BPORT;
    int SendSocket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    
    if (SendSocket == -1){
        close(SendSocket);
        perror("Socket failed");
        exit(-1);
    }
    //create a UDP client socket
    
    memset(&serverB, 0, sizeof(serverB));
    serverB.sin_family = PF_INET;
    serverB.sin_port = BPORT;
    serverB.sin_addr.s_addr = inet_addr(localhost);
    socklen_t serverB_addr_size = sizeof(serverB);
    //setting the address of the server
    
    sendto(SendSocket, query.c_str(), sizeof(query), 0, (struct sockaddr*) &serverB, serverB_addr_size);
    sendto(SendSocket, fct.c_str(), sizeof(fct), 0, (struct sockaddr*) &serverB, serverB_addr_size);
    //send the query and function
    cout<<"The AWS sent < "<<query<<" > and < "<<fct<<"> to Backend-Server B"<<endl;
    close(SendSocket);
    //destroy the socket
    
}

/*
 * Send the query and function to Server C using udp
 * query: query
 * fct: function
 */
void udpToC(string  query, string fct){
    
    int socket_info;
    struct sockaddr_in serverC;
    int port = CPORT;
    int SendSocket=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    
    if (SendSocket == -1){
        close(SendSocket);
        perror("Socket failed");
        exit(-1);
    }
    //create a UDP client socket
    
    memset(&serverC, 0, sizeof(serverC));
    serverC.sin_family = PF_INET;
    serverC.sin_port = CPORT;
    serverC.sin_addr.s_addr = inet_addr(localhost);
    socklen_t serverC_addr_size = sizeof(serverC);
    //setting the address of the server
    
    sendto(SendSocket, query.c_str(), sizeof(query), 0, (struct sockaddr*) &serverC, serverC_addr_size);
    sendto(SendSocket, fct.c_str(), sizeof(fct), 0, (struct sockaddr*) &serverC, serverC_addr_size);
    //send the query and function
    cout<<"The AWS sent < "<<query<<" > and < "<<fct<<"> to Backend-Server C"<<endl;
    close(SendSocket);
    //destroy the socket    
}

/*
 * Receive the result given a query
 * sockUdp: Id of udp socket
 * res: the vector to store the result
 * resSimW: similar word
 * resSimM: similar word's meaning
 * fct: function
 * server: which server
 * reveiving via which port
 */
void recv(int sockUdp, vector<string> &res,vector<string>&resSimW, vector<string>&resSimM, string fct,char server, int port){
    
    if(!strcmp(fct.c_str(),"prefix")){
        
        struct sockaddr_in serverA;
        memset(&serverA, 0, sizeof(serverA));
        socklen_t serverA_addr_size = sizeof(serverA);
        char recvBuffer[MAX_LENGTH]={'\0'};
        
        int strLen = recvfrom(sockUdp, recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);
        int found = atoi(recvBuffer);
        memset(recvBuffer,'\0',MAX_LENGTH);
        //receive the size of result
        
        for(int i = 0; i < found; i++){
            memset(recvBuffer,'\0',MAX_LENGTH);
            strLen = recvfrom(sockUdp, &recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);
            recvBuffer[strLen]='\0';
            res.push_back((string)recvBuffer);
        }
        // One by one receive the result
        
        cout<<"The AWS receives <"<<found<<"> matches from Backend-Server <";
        cout<<server<<"> using UDP over port "<<port<<endl;
        
    }
    else if(!strcmp(fct.c_str(),"suffix")){
        
        struct sockaddr_in serverA;
        memset(&serverA, 0, sizeof(serverA));
        socklen_t serverA_addr_size = sizeof(serverA);
        char recvBuffer[MAX_LENGTH]={'\0'};
        
        int strLen = recvfrom(sockUdp, recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);	
        int found = atoi(recvBuffer);
        //receive the size of result
        
        memset(recvBuffer,'\0',MAX_LENGTH);
        for(int i = 0; i < found; i++){
            memset(recvBuffer,'\0',MAX_LENGTH);
            strLen = recvfrom(sockUdp, &recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);
            recvBuffer[strLen]='\0';
            res.push_back((string)recvBuffer);
        }
        // One by one receive the result
        
        cout<<"The AWS receives <"<<found<<"> matches from Backend-Server <";
        cout<<server<<"> using UDP over port "<<port<<endl;
    }
    
    else{
        
        struct sockaddr_in serverA;
        memset(&serverA, 0, sizeof(serverA));
        socklen_t serverA_addr_size = sizeof(serverA);
        char recvBuffer[MAX_LENGTH]={'\0'};
        
        int strLen = recvfrom(sockUdp, recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);
        int found = atoi(recvBuffer);
        memset(recvBuffer,'\0',MAX_LENGTH);
        //receive the size of result        
        
        for(int i = 0; i < found; i++){
            memset(recvBuffer,'\0',MAX_LENGTH);
            strLen = recvfrom(sockUdp, &recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);
            recvBuffer[strLen]='\0';
            res.push_back((string)recvBuffer);
        }
        // One by one receive the result
        
        strLen = recvfrom(sockUdp, recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);
        
        int foundSim = atoi(recvBuffer);
        memset(recvBuffer,'\0',MAX_LENGTH);
        //receive the size of similar result
        for(int i = 0; i < foundSim; i++){
            memset(recvBuffer,'\0',MAX_LENGTH);
            strLen = recvfrom(sockUdp, &recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);
            recvBuffer[strLen]='\0';
            resSimW.push_back((string)recvBuffer);
            memset(recvBuffer,'\0',MAX_LENGTH);
            strLen = recvfrom(sockUdp, &recvBuffer, (size_t)MAX_LENGTH, 0, (struct sockaddr*)&serverA, &serverA_addr_size);
            recvBuffer[strLen]='\0';
            resSimM.push_back((string)recvBuffer);
        }
        // One by one receive the result
        cout<<"The AWS receives <"<<foundSim<<"> similar words from Backend-Server <";
        cout<<server<<"> using UDP over port "<<port<<endl;
        
    }
    
    
}
int main(){
    
    //UDP socket
    int sockUdp = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    struct sockaddr_in serverAWSUdp_addr;
    memset(&serverAWSUdp_addr, 0, sizeof(serverAWSUdp_addr));
    serverAWSUdp_addr.sin_family = PF_INET;
    serverAWSUdp_addr.sin_addr.s_addr = inet_addr(localhost);
    serverAWSUdp_addr.sin_port = AWSPORT;
    bind(sockUdp, (struct sockaddr*)&serverAWSUdp_addr, sizeof(serverAWSUdp_addr));
    
    //TCP client
    int tcpClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serverAWSTcpClient_addr;
    memset(&serverAWSTcpClient_addr, 0, sizeof(serverAWSTcpClient_addr));
    serverAWSTcpClient_addr.sin_family = PF_INET;
    serverAWSTcpClient_addr.sin_addr.s_addr = inet_addr(localhost);
    serverAWSTcpClient_addr.sin_port = TCPPORT_CLIENT;
    bind(tcpClient, (struct sockaddr*)&serverAWSTcpClient_addr, sizeof(serverAWSTcpClient_addr));
    
    //TCP Monitor
    int tcpMonitor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serverAWSTcpMonitor_addr;
    memset(&serverAWSTcpMonitor_addr, 0, sizeof(serverAWSTcpMonitor_addr));
    serverAWSTcpMonitor_addr.sin_family = PF_INET;
    serverAWSTcpMonitor_addr.sin_addr.s_addr = inet_addr(localhost);
    serverAWSTcpMonitor_addr.sin_port = TCPPORT_MONITOR;
    bind(tcpMonitor, (struct sockaddr*)&serverAWSTcpMonitor_addr, sizeof(serverAWSTcpMonitor_addr));
    
    cout<<"The AWS is up and running"<<endl;
    while(1){
        
        listen(tcpMonitor, QUEUE_LIMIT);
        struct sockaddr_in monitor_addr;
        socklen_t len_mon = sizeof(struct sockaddr_in);
        int childTcpMonitor = accept(tcpMonitor , (struct sockaddr *)&monitor_addr, &len_mon);
        //connection with monitor   
        
        if (childTcpMonitor == -1){
            
            perror("Accept failed");
            exit(-1);
        }
        
        
        listen(tcpClient, QUEUE_LIMIT);
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(struct sockaddr_in);
        int childTcpClient = accept(tcpClient , (struct sockaddr *)&client_addr, &len);
        //connection with client   
        
        
        if (childTcpClient == -1){
            
            perror("Accept failed");
            exit(-1);
        }
        
        
        
        char recvBuffer[BUFF_SIZE];
        char fctBuffer[BUFF_SIZE];
        int fctl = recv(childTcpClient, fctBuffer, sizeof(fctBuffer), 0);
        char fct[BUFF_SIZE] ={'\0'};
        decode(fctBuffer);
        strcpy(fct,fctBuffer);
        //receive the function from client    
        
        encode(fctBuffer);
        send(childTcpMonitor,fctBuffer, sizeof(fctBuffer), 0);
        decode(fctBuffer);
        
        int first = recv(childTcpClient, recvBuffer, sizeof(recvBuffer), 0); 
        
        char query[BUFF_SIZE] ={'\0'};
        decode(recvBuffer);
        strcpy(query,recvBuffer);
        encode(query);
        send(childTcpMonitor,query, sizeof(query), 0);
        decode(query);
        
        cout<<"The AWS received input=<"<<query<<"> and function=<"<<fct<<"> from the client using TCP ";
        cout<<"over port "<<serverAWSTcpClient_addr.sin_port<<endl;
        //receive the query from client    
        //end of phase 1A
        
        vector<string> res;
        vector<string> resSimW;
        vector<string> resSimM;
        
        udpToA(query, fct);
        udpToB(query, fct);
        udpToC(query, fct);
        startA();
        recv(sockUdp,res,resSimW,resSimM,fct,'B',serverAWSUdp_addr.sin_port);
        startB();
        recv(sockUdp,res,resSimW,resSimM,fct,'A',serverAWSUdp_addr.sin_port);
        startC();
        recv(sockUdp,res,resSimW,resSimM,fct,'C',serverAWSUdp_addr.sin_port);
        //send and receive of with the back end
        // end of the phase 1B
        
        
        
        char bufSend[BUFF_SIZE] ={'\0'};
        
        int size = res.size();
        if(!strcmp(fct,"search")){
            size=size>0?1:0;
        }
        //send the size of output result to both the monitor and client.
        sprintf(bufSend,"%d",size);
        send(childTcpMonitor, bufSend , sizeof(bufSend), 0); 
        send(childTcpClient, bufSend , sizeof(bufSend), 0);
        // sent the result to display.
        for(int i = 0; i < size; i++){
            memset(bufSend,'\0',100);
            strcpy(bufSend,res[i].c_str());
            encode(bufSend);
            send(childTcpClient, bufSend, sizeof(bufSend), 0);
            send(childTcpMonitor, bufSend, sizeof(bufSend), 0);
        }
        
        cout<<"The aws sent < "<<size<<" > matches to client"<<endl;
        if(!strcmp(fct,"search")){
            //for the search, we need also a similar word.
            cout<<"The aws sent < "<<query<<" > ";
            
            int sizeSim = resSimW.size()>0?1:0;
            //we only need the first one
            sprintf(bufSend,"%d",sizeSim);
            send(childTcpMonitor, bufSend , sizeof(bufSend), 0);  
            //send word and meaning to the monitor
            for(int i = 0; i < sizeSim; i++){
                memset(bufSend,'\0',BUFF_SIZE);
                strcpy(bufSend,resSimW[i].c_str());
                encode(bufSend);
                cout<<"and < "<<resSimW[i]<<" > ";
                send(childTcpMonitor, bufSend, sizeof(bufSend), 0);
                strcpy(bufSend,resSimM[i].c_str());
                encode(bufSend);
                send(childTcpMonitor, bufSend, sizeof(bufSend), 0); 
            }
        }
        else{
            cout<<"The aws sent < "<<size<<" > matches ";
        }
        cout<<"to the monitor via TCP port "<<serverAWSTcpMonitor_addr.sin_port<<endl;
        res= vector<string>(); 
        resSimW= vector<string>();
        resSimM= vector<string>();
        //empty the result array.
        
        shutdown(childTcpClient,0);
        close(childTcpClient);
        shutdown(childTcpMonitor,0);
        close(childTcpMonitor);
    }
    return 0;
}
