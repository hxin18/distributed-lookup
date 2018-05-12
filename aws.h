//
//  aws.hpp
//  ee450
//
//  Created by Xin Huang on 2018/3/18.
//  Copyright © 2018年 Xin Huang. All rights reserved.
//

#ifndef aws_h
#define aws_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include<vector>
#define APORT 21164
#define BPORT 22164
#define CPORT 23164
#define AWSPORT 24164
#define TCPPORT_CLIENT 25164
#define TCPPORT_MONITOR 26164
#define QUEUE_LIMIT 10
#define MAX_LENGTH 100
const char* localhost = "127.0.0.1";
#define fill '@'
#define BUFF_SIZE 1000


void encode(char* str);
void decode(char* str);

void udpToA(std::string query, std::string fct);
void udpToB(std::string query, std::string fct);
void udpToC(std::string query, std::string fct);
void startA();
void startB();
void startC();
void recv(int sockUdp,std::vector<std::string> &res,std::vector<std::string>&resSim,std::string fct, char server, int port);

#endif /* aws_hpp */
