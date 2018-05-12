//
//  servera.hpp
//  ee450
//
//  Created by Xin Huang on 2018/3/18.
//  Copyright © 2018年 Xin Huang. All rights reserved.
//

#ifndef servera_h
#define servera_h

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
#include <map>
#include <fstream>
#include <vector>

#define CPORT 23164
#define AWSPORT 24164
#define MAX_LENGTH 100

const char* localhost = "127.0.0.1";
typedef std::map<std::string,std::string> dict;

class kvParser{
private:
    std::string key;
    std::string value;
public:
    
    kvParser(std::string str, std::string seperator);
    std::string getKey();
    std::string getValue();
};

class Dict{
private:
    dict Dictionary;
public:
    const std::string seperator = " :: ";
    Dict();
    void buildDict(std::string databaseFile);
    bool findKey(std::string key);
    std::vector<std::string> retriveKey(std::string key);
    void retriveSimilar(std::string key, std::vector<std::string>& simM, std::vector<std::string>&simW);
    std::vector<std::string> retrivePrefix(std::string key);
    std::vector<std::string> retriveSuffix(std::string key);

    ~Dict();
};



#endif /* servera_hpp */
