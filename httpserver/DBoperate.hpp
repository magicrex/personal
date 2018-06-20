#include <mysql++.h>
#include<vector>
#include<iostream>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
using namespace mysqlpp;
//insert into cc(id, name, status) values(22, "laoyang", "ok");
const char* str_insertmessage = "insert into message value(\"%s\", \"%s\");";
const char* str_createtable="create table %s(id varchar(30) primary key,addr varchar(20) not null);";
const char* str_insertaddr="insert into %s value(\"%s\", \"%s\")";
const char* str_deleteaddr = "delete from %s where id = \"%s\";";
const char* str_updatemessage = "update message set password = \"%s\" where username = \"%s\";";
const char* str_selectmessage = "select * from message where username=\"%s\";";
const char* str_selecttable  = "select * from %s;";

#define DATEBASE_NAME "cpp"
#define DATEBASE_IP "127.0.0.1"
#define DATEBASE_USERNAME "root"
#define DATEBASE_PWD "fuxingde"

#define DATA_BUF_SIZE 1024
//创建表
bool createtable(const char* tablename)
{
    Connection conn(false);
    conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,str_createtable,tablename);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//增用户
bool insertmessage(const char* value1,const char* value2)
{
    Connection conn(false);
    conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,str_insertmessage,value1,value2);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//增内容
bool insertaddr(const char* tablename,const char* value1,const char* value2)
{
    Connection conn(false);
    conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,str_insertaddr,tablename,value1,value2);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//删
bool deleteaddr(const char* tablename,const char* value1)
{
    Connection conn(false);
    conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,str_deleteaddr,tablename,value1);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//改
bool updatemessage(const char* username,const char* password)
{
    Connection conn(false);
    conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,str_updatemessage,password,username);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//查
bool selectmessage(const char* username)
{
    Connection conn(false);
    conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,str_selectmessage,username);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::stringstream ss;
    for (it = res.begin(); it != res.end(); ++it) 
    {
            mysqlpp::Row row = *it;
            ss << row[1];
    }
    std::string s=ss.str();
    if(s.empty()){
        return false;
    }else{
        return true;
    }

}

//查密码
bool selectpassword(const char* username,const char* password)
{
    Connection conn(false);
    conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,str_selectmessage,username);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::string pass(password);
    std::stringstream ss;
    for (it = res.begin(); it != res.end(); ++it) 
    {
            mysqlpp::Row row = *it;
            ss << row[1];
    }
    std::string s;
    s=ss.str();
    if(s.empty()){
        return false;
    }else{
        if(s==password){
            return true;
        }else{
            return false;
        }
    }
}
